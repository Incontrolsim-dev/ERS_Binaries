#pragma once
#include "Ers/Utility/Util.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Ers/Model/ModelManager.h"
#include "Ers/Model/Simulator/SimulatorType.h"

namespace Ers
{
    class SubModel;
}

namespace Ers
{
    class Simulator;

    /// @brief ModelContainer is a wrapper class to provide access to the functionality of the ModelContainer class in ers-core.
    /// This class is responsible for the creation and the management of Simulator-s.
    class ModelContainer
    {
      public:
        ModelContainer(void* coreInstance); // Shallow copy

        ~ModelContainer();

        ModelContainer()                      = delete;
        ModelContainer(const ModelContainer&) = delete;
        ModelContainer(ModelContainer&&) noexcept;
        ModelContainer& operator=(const ModelContainer&) = delete;
        ModelContainer& operator=(ModelContainer&&) noexcept;

        Simulator AddSimulator(const std::string_view& tag, Ers::SimulatorType type);

        void RemoveSimulator(Ers::Simulator simulator);

        Ers::Simulator FindSimulator(const std::string_view& simulatorTag);
        Ers::Simulator FindSimulator(const std::int32_t& simulatorId);

        void Start();
        [[nodiscard]] SimulationTime CurrentTime() const;

        [[nodiscard]] bool IsStarted() const;

        void Update(SimulationTime timeStep) const;

        std::size_t SimulatorCount();

        [[nodiscard]] Ers::SubModel& GetSharedSubModel() const;

        void AddSimulatorDependency(Ers::Simulator from, Ers::Simulator to);
        void RemoveSimulatorDependency(Ers::Simulator from, Ers::Simulator to);

        [[nodiscard]] std::vector<Ers::Simulator> GetSimulators();
        [[nodiscard]] Ers::Simulator GetSimulator(const int32_t simulatorId);
        [[nodiscard]] Ers::Simulator GetSimulatorByIndex(int index);

        void* Data();
        const void* const Data() const;

        size_t GetSeed() const;
        void SetSeed(size_t newSeed);

        /// @brief set an arbitrary value as the model precision, this precision will be used in ERS for monitoring & displayed graphics
        void SetPrecision(SimulationTime precision);
        SimulationTime GetPrecision() const;

        bool Valid() const;

        static ModelContainer CreateModelContainer();

      private:
        void* coreModelContainerInstance{nullptr};
    };
} // namespace Ers
