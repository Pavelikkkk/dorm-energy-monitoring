#include "dorm_energy/infrastructure/notifier/telegram_config.hpp"

namespace dorm_energy::notifier
{
    TelegramConfig TelegramConfig::fromAppConfig(const application::AppConfig& config)
    {
        TelegramConfig cfg;
        cfg.enabled = config.isTelegramEnabled();
        cfg.botToken = config.getTelegramBotToken();
        cfg.chatId = config.getTelegramChatId();
        return cfg;
    }
}