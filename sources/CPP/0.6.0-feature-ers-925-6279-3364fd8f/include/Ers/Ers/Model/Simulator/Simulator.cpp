#include "Ers/Api.h"

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{

    Simulator::Simulator(void* instance) :
        coreSimulatorInstance(instance)
    {
    }

    void Simulator::EnterSubModel()
    {
        ersAPIFunctionPointers.ERS_ThreadLocal_EnterSubModel(ersAPIFunctionPointers.ERS_Simulator_GetSubModel(coreSimulatorInstance));
    }

    void Simulator::ExitSubModel()
    {
        assert(
            ersAPIFunctionPointers.ERS_Simulator_GetSubModel(coreSimulatorInstance) ==
            ersAPIFunctionPointers.ERS_ThreadLocal_GetSubModel());

        ersAPIFunctionPointers.ERS_ThreadLocal_ExitSubModel();
    }

    /// @return Returns a reference to the simulator libraries associated with this container.
    LibraryCollection Simulator::GetLibraryCollection()
    {
        assert(Valid());
        return LibraryCollection(ersAPIFunctionPointers.ERS_Simulator_GetLibraryCollection(coreSimulatorInstance));
    }

    /// @return Returns the type of the simulator.
    Ers::SimulatorType Simulator::GetSimulatorType() const
    {
        return static_cast<Ers::SimulatorType>(ersAPIFunctionPointers.ERS_Simulator_GetSimulatorType(coreSimulatorInstance));
    }

    /// @return The ID of this simulator. '-1' indicates an invalid ID.
    std::int32_t Simulator::GetID() const
    {
        return ersAPIFunctionPointers.ERS_Simulator_GetID(coreSimulatorInstance);
    }

    /// @return The name/tag of this simulator as null terminated string.
    std::string Simulator::GetName() const
    {
        char* name = ersAPIFunctionPointers.ERS_Simulator_GetName(coreSimulatorInstance);
        std::string output(name);
        ersAPIFunctionPointers.ERS_STRING_DISPOSE(name);
        return output;
    }

    /// @brief Returns the names of the dependent simulators of this simulator in no particular order.
    /// @return The vector of the names of the depenedent simulators.
    std::vector<std::string> Simulator::GetDependencyNames() const
    {
        size_t totalDependencies = ersAPIFunctionPointers.ERS_Simulator_GetDependenciesAmount(coreSimulatorInstance);
        std::vector<std::string> dependencyNames;
        dependencyNames.reserve(totalDependencies);

        for (size_t i = 0; i < totalDependencies; i++)
        {
            char* dependencyName = ersAPIFunctionPointers.ERS_Simulator_GetDependencyName(coreSimulatorInstance, i);
            std::string localString(dependencyName);
            ersAPIFunctionPointers.ERS_STRING_DISPOSE(dependencyName);
            dependencyNames.emplace_back(localString);
        }

        return dependencyNames;
    }

    SimulationTime Simulator::CurrentTime() const
    {
        return ersAPIFunctionPointers.ERS_Simulator_GetCurrentTime(coreSimulatorInstance);
    }

    /// @brief Based on the given tag/name, find the dependent simulator among the dependencies of this simulator.
    /// @param tag The tag/name of the dependent simulator to find.
    /// @return The shared pointer to the dependent simulator with the given ID if any, otherwise return nullptr.
    Simulator Simulator::FindDependency(const std::string_view& tag)
    {
        void* foundDependencyPtr =
            ersAPIFunctionPointers.ERS_Simulator_FindDependencyByName(coreSimulatorInstance, tag.data(), tag.length());
        return Simulator(foundDependencyPtr);
    }

    /// @brief Based on the given ID, find the dependent simulator among the dependencies of this simulator.
    /// @param simulatorId The ID of the dependent simulator to find.
    /// @return The shared pointer to the dependent simulator with the given tag/name if any, otherwise return nullptr.
    Simulator Simulator::FindDependency(uint32_t id)
    {
        void* foundDependencyPtr = ersAPIFunctionPointers.ERS_Simulator_FindDependencyById(coreSimulatorInstance, id);
        return Simulator(foundDependencyPtr);
    }

    Simulator Simulator::FindOutgoingDependency(uint32_t id)
    {
        void* foundDependencyPtr = ersAPIFunctionPointers.ERS_Simulator_FindOutgoingDependencyById(coreSimulatorInstance, id);
        return Simulator(foundDependencyPtr);
    }

    bool Simulator::IsRunTogether(int32_t otherSimulatorId) const
    {
        return ersAPIFunctionPointers.ERS_Simulator_IsRunTogether(coreSimulatorInstance, otherSimulatorId);
    }

    bool Simulator::IsBiDirectional(int32_t otherSimulatorId) const
    {
        return ersAPIFunctionPointers.ERS_Simulator_IsBiDirectional(coreSimulatorInstance, otherSimulatorId);
    }

    SimulationTime Simulator::GetTimeStep()
    {
        return ersAPIFunctionPointers.ERS_Simulator_GetTimeStep(coreSimulatorInstance);
    }

    void Simulator::SetTimeStep(SimulationTime newTimeStep)
    {
        return ersAPIFunctionPointers.ERS_Simulator_SetTimeStep(coreSimulatorInstance, newTimeStep);
    }

    Simulator Simulator::FindOutgoingDependency(const std::string_view& name)
    {
        void* foundDependencyPtr =
            ersAPIFunctionPointers.ERS_Simulator_FindOutgoingDependencyByName(coreSimulatorInstance, name.data(), name.size());
        return Simulator(foundDependencyPtr);
    }

    void* Simulator::Data()
    {
        return coreSimulatorInstance;
    }

    const void* const Simulator::Data() const
    {
        return coreSimulatorInstance;
    }

    bool Simulator::Valid()
    {
        // A simulator is invalid if the reference is set incorrectly
        if (coreSimulatorInstance == nullptr)
            return false;

        return true;
    }

    Simulator::~Simulator()
    {
    }

} // namespace Ers
