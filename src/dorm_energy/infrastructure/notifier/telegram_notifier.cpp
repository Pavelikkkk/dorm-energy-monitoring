#include "dorm_energy/infrastructure/notifier/telegram_notifier.hpp"
#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/core/alert_severity.hpp"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <iomanip>

namespace dorm_energy::notifier
{

    TelegramNotifier::TelegramNotifier(const application::AppConfig &config)
        : TelegramNotifier(TelegramConfig::fromAppConfig(config))
    {
    }

    TelegramNotifier::TelegramNotifier(TelegramConfig cfg)
        : config_(std::move(cfg)), poller_(config_)
    {
        if (config_.enabled && !config_.botToken.empty() && !config_.chatId.empty())
        {
            apiUrl_ = "https://api.telegram.org/bot" + config_.botToken + "/sendMessage";
            std::cout << "[TelegramNotifier] Initialized (chat_id: " << config_.chatId << ")\n";

            startQueueWorker();
            // poller_.start();
        }
    }

    TelegramNotifier::~TelegramNotifier()
    {
        stopQueueWorker();
        // poller_.stop();
    }

    // ====================== PUBLIC INTERFACE ======================

    bool TelegramNotifier::sendAlert(const core::SensorReading &reading,
                                     core::AlertSeverity severity,
                                     const std::string &reason)
    {
        if (!config_.enabled || apiUrl_.empty())
            return false;

        std::string text = buildAlertMessage(reading, severity, reason);

        if (sendMessage(text))
            return true;

        queue_.push(reading, severity, reason);
        std::cout << "[TelegramNotifier] Message queued (size: " << queue_.size() << ")\n";
        return false;
    }

    std::size_t TelegramNotifier::sendAlerts(const std::vector<core::SensorReading> &readings,
                                             core::AlertSeverity severity,
                                             const std::string &reason)
    {
        if (readings.empty())
            return 0;

        std::size_t sent = 0;
        for (const auto &r : readings)
        {
            if (sendAlert(r, severity, reason))
                ++sent;
        }
        return sent;
    }

    // ====================== PRIVATE ======================

    bool TelegramNotifier::sendMessage(const std::string &text)
    {
        if (text.empty())
            return false;

        CURL *curl = curl_easy_init();
        if (!curl)
            return false;

        std::string replyMarkup = R"({"inline_keyboard":[[{"text":"✅ Принято","callback_data":"ack"}]]})";

        std::string postData = "chat_id=" + config_.chatId +
                               "&text=" + curl_easy_escape(curl, text.c_str(), static_cast<int>(text.length())) +
                               "&parse_mode=MarkdownV2" +
                               "&reply_markup=" + curl_easy_escape(curl, replyMarkup.c_str(), static_cast<int>(replyMarkup.length()));

        curl_easy_setopt(curl, CURLOPT_URL, apiUrl_.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return res == CURLE_OK;
    }

    std::string TelegramNotifier::buildAlertMessage(const core::SensorReading &reading,
                                                    core::AlertSeverity severity,
                                                    const std::string &reason) const
    {
        std::ostringstream oss;

        std::string emoji = (severity == core::AlertSeverity::Critical) ? "🚨" : (severity == core::AlertSeverity::Warning) ? "⚠️"
                                                                                                                            : "ℹ️";

        oss << emoji << " *" << core::toString(severity) << " АНОМАЛИЯ*\n\n";
        oss << "📍 *Устройство:* `" << reading.deviceId << "`\n";
        oss << "🔧 *Тип:* `" << reading.sensorType << "`\n";
        oss << "⚡ *Значение:* `" << reading.value << "`";
        if (!reading.unit.empty())
            oss << " " << reading.unit;
        oss << "\n";
        oss << "⏰ *Время:* `" << std::chrono::system_clock::to_time_t(reading.timestamp) << "`\n";

        if (!reason.empty())
            oss << "\n🔍 *Причина:* " << reason << "\n";

        oss << "\n_Нажми кнопку ниже после принятия_";

        std::string msg = oss.str();

        const std::string special = "_*[]()~`>#+-=|{}.!";
        for (char c : special)
        {
            size_t pos = 0;
            while ((pos = msg.find(c, pos)) != std::string::npos)
            {
                msg.insert(pos, "\\");
                pos += 2;
            }
        }

        return msg;
    }

    // ====================== QUEUE ======================

    void TelegramNotifier::startQueueWorker()
    {
        if (running_)
            return;
        running_ = true;
        workerThread_ = std::thread(&TelegramNotifier::queueWorker, this);
    }

    void TelegramNotifier::stopQueueWorker()
    {
        if (!running_)
            return;
        running_ = false;
        if (workerThread_.joinable())
            workerThread_.join();
    }

    void TelegramNotifier::queueWorker()
    {
        std::cout << "[TelegramNotifier] Queue worker started\n";

        while (running_)
        {
            bool hasInternet = false;

            if (!queue_.empty())
            {
                hasInternet = flushQueue();

                if (hasInternet)
                {
                    currentBackoff_ = std::chrono::seconds{5};
                }
                else
                {
                    auto current = currentBackoff_.load();
                    long long seconds = current.count() * 2;
                    if (seconds > 900)
                        seconds = 900; 
                    currentBackoff_ = std::chrono::seconds{seconds};
                }
            }

            if (queue_.size() > 0)
            {
                std::cout << "[TelegramNotifier] 📭 Queue: " << queue_.size()
                          << " | Backoff: " << currentBackoff_.load().count() << "s\n";
            }

            std::this_thread::sleep_for(currentBackoff_.load());
        }
    }
    bool TelegramNotifier::flushQueue()
    {
        auto alerts = queue_.getAllAndClear();
        if (alerts.empty())
            return true;

        std::size_t sent = 0;
        for (const auto &a : alerts)
        {
            std::string text = buildAlertMessage(a.reading, a.severity, a.reason);
            if (sendMessage(text))
                ++sent;
        }
        return sent > 0;
    }

    void TelegramNotifier::logQueueStatus()
    {
        std::size_t sz = queue_.size();
        if (sz > 0)
        {
            std::cout << "[TelegramNotifier] Queue: " << sz
                      << " alerts | Backoff: " << currentBackoff_.load().count() << "s\n";
        }
    }

} // namespace dorm_energy::notifier