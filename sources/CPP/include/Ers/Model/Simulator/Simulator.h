#pragma once

#include "Ers/Utility/Util.h"

#include "Ers/Model/Simulator/SimulatorType.h"

#include "Ers/Utility/SharedLibrary.h"

#include "LibraryCollection.h"

#include <string>
#include <vector>

namespace Ers
{
    class ModelContainer;
    class EditingSubModel;

    class Simulator
    {
      public:
        // @Note: an instance of this class can be created via Ers::ModelContainer::AddSimulator method.
        Simulator(void* instance);

        Simulator()                            = delete;
        Simulator(const Simulator&)            = default;
        Simulator(Simulator&&)                 = default;
        Simulator& operator=(Simulator&&)      = delete;
        Simulator& operator=(const Simulator&) = default;
        ~Simulator();

        void EnterSubModel();
        void ExitSubModel();

        LibraryCollection GetLibraryCollection();
        Ers::SimulatorType GetSimulatorType() const;

        int32_t GetID() const;
        std::string GetName() const;

        [[nodiscard]] std::vector<std::string> GetDependencyNames() const;

        SimulationTime CurrentTime() const;

        Simulator FindDependency(const std::string_view& name);
        Simulator FindDependency(uint32_t id);
        Simulator FindOutgoingDependency(const std::string_view& name);
        Simulator FindOutgoingDependency(uint32_t id);

        bool IsRunTogether(int32_t otherSimulatorId) const;
        bool IsBiDirectional(int32_t otherSimulatorId) const;

        /// @brief Get the Timestep of the given Simulator
        /// <param name="instance [in]">Pointer to the given instance of the Simulator in the core.</param>
        /// @return the timestep set on the simulator
        SimulationTime GetTimeStep();

        /// @brief Set the Timestep of the given Simulator
        /// <param name="instance [in]">Pointer to the given instance of the Simulator in the core.</param>
        /// <param name="newTimeStep [in]">New timestep.</param>
        void SetTimeStep(SimulationTime newTimeStep);

        void* Data();
        const void* const Data() const;

        bool Valid();

      private:
        void* coreSimulatorInstance; // pointer to the simulator instance in ers-core
    };
} // namespace Ers
