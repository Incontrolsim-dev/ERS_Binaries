#include "Ers/Api.h"

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{

    Simulator::Simulator(void* instance) :
        corePtr(instance)
    {
    }

    void Simulator::EnterSubModel()
    {
        Ers::Engine::ERS_ThreadLocal_EnterSubModel(Ers::Engine::ERS_Simulator_GetSubModel(corePtr));
    }

    void Simulator::ExitSubModel()
    {
        assert(Ers::Engine::ERS_Simulator_GetSubModel(corePtr) == Ers::Engine::ERS_ThreadLocal_GetSubModel());

        Ers::Engine::ERS_ThreadLocal_ExitSubModel();
    }

    /// @return Returns a reference to the simulator libraries associated with this container.
    LibraryCollection Simulator::GetLibraryCollection()
    {
        assert(Valid());
        return LibraryCollection(Ers::Engine::ERS_Simulator_GetLibraryCollection(corePtr));
    }

    /// @return Returns the type of the simulator.
    Ers::SimulatorType Simulator::GetSimulatorType() const
    {
        return static_cast<Ers::SimulatorType>(Ers::Engine::ERS_Simulator_GetSimulatorType(corePtr));
    }

    /// @return The ID of this simulator. '-1' indicates an invalid ID.
    std::int32_t Simulator::GetID() const
    {
        return Ers::Engine::ERS_Simulator_GetID(corePtr);
    }

    /// @return The name/tag of this simulator as null terminated string.
    std::string Simulator::GetName() const
    {
        char* name = Ers::Engine::ERS_Simulator_GetName(corePtr);
        std::string output(name);
        Ers::Engine::ERS_String_Destroy(name);
        return output;
    }

    /// @brief Returns the names of the dependent simulators of this simulator in no particular order.
    /// @return The vector of the names of the dependent simulators.
    std::vector<std::string> Simulator::GetDependencyNames() const
    {
        size_t totalDependencies = Ers::Engine::ERS_Simulator_GetDependenciesAmount(corePtr);
        std::vector<std::string> dependencyNames;
        dependencyNames.reserve(totalDependencies);

        for (size_t i = 0; i < totalDependencies; i++)
        {
            char* dependencyName = Ers::Engine::ERS_Simulator_GetDependencyName(corePtr, i);
            std::string localString(dependencyName);
            Ers::Engine::ERS_String_Destroy(dependencyName);
            dependencyNames.emplace_back(localString);
        }

        return dependencyNames;
    }

    SimulationTime Simulator::CurrentTime() const
    {
        return Ers::Engine::ERS_Simulator_GetCurrentTime(corePtr);
    }

    ModelContainer Simulator::GetAttachedModelContainer()
    {
        return ModelContainer(Ers::Engine::ERS_Simulator_GetAttachedModelContainer(corePtr));
    }

    /// @brief Based on the given tag/name, find the dependent simulator among the dependencies of this simulator.
    /// @param tag The tag/name of the dependent simulator to find.
    /// @return The shared pointer to the dependent simulator with the given ID if any, otherwise return nullptr.
    Simulator Simulator::FindDependency(const std::string_view& tag)
    {
        void* foundDependencyPtr = Ers::Engine::ERS_Simulator_FindDependencyByName(corePtr, tag.data(), tag.length());
        return Simulator(foundDependencyPtr);
    }

    /// @brief Based on the given ID, find the dependent simulator among the dependencies of this simulator.
    /// @param simulatorId The ID of the dependent simulator to find.
    /// @return The shared pointer to the dependent simulator with the given tag/name if any, otherwise return nullptr.
    Simulator Simulator::FindDependency(uint32_t id)
    {
        void* foundDependencyPtr = Ers::Engine::ERS_Simulator_FindDependencyById(corePtr, id);
        return Simulator(foundDependencyPtr);
    }

    Simulator Simulator::FindOutgoingDependency(uint32_t id)
    {
        void* foundDependencyPtr = Ers::Engine::ERS_Simulator_FindOutgoingDependencyById(corePtr, id);
        return Simulator(foundDependencyPtr);
    }

    bool Simulator::IsRunTogether(int32_t otherSimulatorId) const
    {
        return Ers::Engine::ERS_Simulator_IsRunTogether(corePtr, otherSimulatorId);
    }

    bool Simulator::IsBiDirectional(int32_t otherSimulatorId) const
    {
        return Ers::Engine::ERS_Simulator_IsBiDirectional(corePtr, otherSimulatorId);
    }

    SimulationTime Simulator::GetTimeStep()
    {
        return Ers::Engine::ERS_Simulator_GetTimeStep(corePtr);
    }

    void Simulator::SetTimeStep(SimulationTime newTimeStep)
    {
        return Ers::Engine::ERS_Simulator_SetTimeStep(corePtr, newTimeStep);
    }

    size_t Simulator::GetSeed() const
    {
        void* subModel = Ers::Engine::ERS_Simulator_GetSubModel(corePtr);
        return Ers::Engine::ERS_SubModelRandomProperties_GetOriginalSeed(subModel);
    }

    Simulator Simulator::FindOutgoingDependency(const std::string_view& name)
    {
        void* foundDependencyPtr = Ers::Engine::ERS_Simulator_FindOutgoingDependencyByName(corePtr, name.data(), name.size());
        return Simulator(foundDependencyPtr);
    }

    void* Simulator::CorePtr()
    {
        return corePtr;
    }

    const void* const Simulator::CorePtr() const
    {
        return corePtr;
    }

    bool Simulator::Valid()
    {
        // A simulator is invalid if the reference is set incorrectly
        if (corePtr == nullptr)
            return false;

        return true;
    }

    Simulator::~Simulator()
    {
    }

} // namespace Ers
