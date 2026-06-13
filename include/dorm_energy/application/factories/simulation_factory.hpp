#pragma once

#include "dorm_energy/application/config/app_config.hpp"

#include <memory>

namespace dorm_energy::simulation
{
    class IDataGenerator;
}

namespace dorm_energy::storage
{
    class IMeasurementRepository;
}

namespace dorm_energy::application::factories
{
    class SimulationFactory
    {
    public:
        explicit SimulationFactory(const AppConfig &config);

        std::unique_ptr<simulation::IDataGenerator>
        createGenerator(std::shared_ptr<storage::IMeasurementRepository> repository) const;

    private:
        const AppConfig &config_;
    };
} // namespace dorm_energy::application::factories
