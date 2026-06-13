#pragma once

#include <memory>

namespace dorm_energy::detection
{
    class RoomStateAggregator;
}

namespace dorm_energy::application::factories
{
    class StateFactory
    {
    public:
        std::shared_ptr<detection::RoomStateAggregator> createAggregator();

    private:
        std::shared_ptr<detection::RoomStateAggregator> aggregator_{};
    };
} // namespace dorm_energy::application::factories
