#include "dorm_energy/infrastructure/detection/anomaly_tracker.hpp"

namespace dorm_energy::detection
{

    std::string AnomalyTracker::makeKey(
        const core::RoomState &state,
        const AnomalyInfo &anomaly) const
    {
        return state.roomId +
               ":" +
               anomaly.anomalyType;
    }

    bool AnomalyTracker::shouldReport(
        const core::RoomState &state,
        const AnomalyInfo &anomaly)
    {
        auto key =
            makeKey(state, anomaly);

        if (active_.contains(key))
        {
            return false;
        }

        active_.insert(key);

        return true;
    }

    void AnomalyTracker::resolveRoom(
        const std::string &roomId)
    {
        std::vector<std::string> remove;

        for (const auto &key : active_)
        {
            if (key.starts_with(roomId + ":"))
            {
                remove.push_back(key);
            }
        }

        for (const auto &key : remove)
        {
            active_.erase(key);
        }
    }

}