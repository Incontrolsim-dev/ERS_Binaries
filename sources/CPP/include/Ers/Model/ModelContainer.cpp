#include "ModelContainer.h"

#include <cassert>
#include <stdexcept>

#include "Ers/Api.h"
#include "Ers/Logger.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{

    /// @brief Add a simulator to this ModelContainer with given tag and type.
    /// @param tag The tag/name of the simulator to add.
    /// @param type The type of the simulator to add.
    Simulator ModelContainer::AddSimulator(const std::string_view& tag, Ers::SimulatorType type)
    {
        assert(Valid());

        Simulator previousSimulator = FindSimulator(tag);
        if (previousSimulator.Valid())
        {
            Ers::Logger::Critical("Tag is already used, unique tag for this Container is required");
            std::abort();
        }

        void* coreSimulator = Ers::Engine::ERS_ModelContainer_AddSimulator(corePtr, tag.data(), static_cast<uint8_t>(type));

        return Ers::Simulator(coreSimulator);
    }

    /// @brief Remove the given simulator from this ModelContainer.
    /// @param simulator Pointer to the simulator to remove.
    /// @throws If the given simulator is a nullptr.
    void ModelContainer::RemoveSimulator(Ers::Simulator simulator)
    {
        assert(simulator.Valid());
        assert(FindSimulator(simulator.GetID()).Valid());
        Ers::Engine::ERS_ModelContainer_RemoveSimulator(corePtr, simulator.CorePtr());
    }

    /// @brief Find the simulator with the given tag/name.
    /// @param simulatorTag The tag/name of the simulator to find.
    /// @return Shared pointer to the simulator with given tag or nullptr if no such simulator is found.
    Ers::Simulator ModelContainer::FindSimulator(const std::string_view& simulatorTag)
    {
        void* foundCoreSimulator = Ers::Engine::ERS_ModelContainer_FindSimulatorByTag(corePtr, simulatorTag.data());

        return Ers::Simulator(foundCoreSimulator);
    }

    /// @brief Find the simulator with the given ID.
    /// @param simulatorId The ID of the simulator to find.
    /// @return Shared pointer to the simulator with given ID or nullptr if no such simulator is found.
    Ers::Simulator ModelContainer::FindSimulator(const std::int32_t& simulatorId)
    {
        void* foundCoreSimulator = Ers::Engine::ERS_ModelContainer_FindSimulatorById(corePtr, simulatorId);

        return Ers::Simulator(foundCoreSimulator);
    }

    /// @brief Return the number of simulators in the ModelContainer.
    std::size_t ModelContainer::SimulatorCount()
    {
        return Ers::Engine::ERS_ModelContainer_GetSimulatorsCount(corePtr);
    }

    /// @brief Add a dependency between simulators.
    /// @param from The simulator which can be scheduled.
    /// @param to The simulator to which can be scheduled.
    void ModelContainer::AddSimulatorDependency(Ers::Simulator from, Ers::Simulator to)
    {
        assert(from.Valid());
        assert(to.Valid());
        Ers::Engine::ERS_ModelContainer_AddSimulatorDependency(corePtr, from.CorePtr(), to.CorePtr());
    }

    void ModelContainer::RemoveSimulatorDependency(Ers::Simulator from, Ers::Simulator to)
    {
        assert(from.Valid());
        assert(to.Valid());
        Ers::Engine::ERS_ModelContainer_RemoveSimulatorDependency(corePtr, from.CorePtr(), to.CorePtr());
    }

    SimulationTime ModelContainer::CurrentTime() const
    {
        return Ers::Engine::ERS_ModelContainer_CurrentTime(corePtr);
    }

    void ModelContainer::Update(SimulationTime timeStep) const
    {
        return Ers::Engine::ERS_ModelContainer_Update_Blocking(corePtr, timeStep);
    }

    void ModelContainer::Start()
    {
        Ers::Engine::ERS_ModelContainer_Start(corePtr);
    }

    // TODO
    bool ModelContainer::IsStarted() const
    {
        return Ers::Engine::ERS_ModelContainer_IsStarted(corePtr);
    }

    /// @brief Return the collection of the simulators in the ModelContainer.
    /// NOTE: If a simulator is removed from this ModelContainer,
    /// the vector returned by this method before removing the simulator is not updated, see issue ERS-595.
    /// @return Returns the vector of shared pointers pointing to the simulators of this ModelContainer.
    std::vector<Ers::Simulator> ModelContainer::GetSimulators()
    {
        std::vector<Ers::Simulator> vecSimulators;
        vecSimulators.reserve(SimulatorCount());
        for (int i = 0; i < vecSimulators.capacity(); i++)
        {
            vecSimulators.emplace_back(Ers::Simulator(Ers::Engine::ERS_ModelContainer_GetSimulator(corePtr, i)));
        }
        return vecSimulators;
    }

    /// @brief Returns the simulator with the given ID.
    /// @param simulatorId The simulator ID to get.
    /// @return Returns a shared pointer to a simulator with the given ID.
    /// @throws If the simulator with the given ID was not found.
    Ers::Simulator ModelContainer::GetSimulator(const std::int32_t simulatorId)
    {
        void* coreSimulator = Ers::Engine::ERS_ModelContainer_GetSimulatorById(corePtr, simulatorId);
        return Ers::Simulator(coreSimulator);
    }

    Ers::Simulator ModelContainer::GetSimulatorByIndex(int index)
    {
        return Ers::Simulator(Ers::Engine::ERS_ModelContainer_GetSimulator(corePtr, index));
    }

    void* ModelContainer::CorePtr()
    {
        return corePtr;
    }

    const void* const ModelContainer::CorePtr() const
    {
        return corePtr;
    }

    void ModelContainer::SetPrecision(SimulationTime precision)
    {
        Ers::Engine::ERS_ModelContainer_SetModelPrecision(corePtr, precision);
    }

    SimulationTime ModelContainer::GetPrecision() const
    {
        return Ers::Engine::ERS_ModelContainer_GetModelPrecision(corePtr);
    }

    double ModelContainer::GetSpeedUp() const
    {
        return Ers::Engine::ERS_ModelContainer_SimulationSpeedOverRealtime(corePtr);
    }

    std::string ModelContainer::GetWorkingDir() const
    {
        return Ers::Engine::ERS_ModelContainer_GetWorkingDir(corePtr);
    }

    void ModelContainer::SetWorkingDir(const std::string_view& path)
    {
        Ers::Engine::ERS_ModelContainer_SetWorkingDir(corePtr, path.data());
    }

    bool ModelContainer::Valid() const
    {
        return corePtr != nullptr;
    }

    size_t Ers::ModelContainer::GetSeed() const
    {
        return Ers::Engine::ERS_ModelContainer_Seed(corePtr);
    }

    void ModelContainer::SetSeed(size_t newSeed)
    {
        return Ers::Engine::ERS_ModelContainer_SetSeed(corePtr, newSeed);
    }

    void ModelContainer::GenerateRandomSeed()
    {
        return Ers::Engine::ERS_ModelContainer_GenerateRandomSeed(corePtr);
    }

    /// @brief Creates a model container
    ModelContainer ModelContainer::Create()
    {
        void* modelContainerInstancePtr = Ers::Engine::ERS_ModelContainer_Create();
        ModelContainer output(modelContainerInstancePtr);
        Ers::Engine::ERS_ModelContainer_Release(modelContainerInstancePtr);
        return output;
    }

    /// @brief Creates a model container with the given pointer to the ModelContainer in the core.
    /// @param corePtr The pointer to the instance of an existing ModelContainer in the core.
    /// @param type The type of the ownership of this instance of ModelContainer with regard to the instance in the core.
    /// I.e. if the API ModelContainer is responsible for the creation and deletion: type = ObjectType::OWNER,
    ///		 if the API ModelContainer acts as an accessor for the ModelContainer in the core: type = ObjectType::ACCESSOR.
    ModelContainer::ModelContainer(void* corePtr) :
        corePtr(corePtr)
    {
        if (corePtr != nullptr)
        {
            Ers::Engine::ERS_ModelContainer_Increase(corePtr); // Increase reference count
        }
    }

    ModelContainer::ModelContainer(ModelContainer&& other) noexcept :
        corePtr(other.corePtr)
    {
        other.corePtr = nullptr;
    }

    ModelContainer::~ModelContainer()
    {
        if (corePtr == nullptr)
        {
            return;
        }

        // Decrease reference count
        Ers::Engine::ERS_ModelContainer_Release(corePtr);
        corePtr = nullptr;
    }

    ModelContainer& ModelContainer::operator=(ModelContainer&& other) noexcept
    {
        corePtr       = other.corePtr;
        other.corePtr = nullptr;

        return *this;
    }

} // namespace Ers
