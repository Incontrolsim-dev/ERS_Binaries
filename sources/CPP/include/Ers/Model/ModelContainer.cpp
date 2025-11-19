#include <stdexcept>

#include "Ers/Api.h"
#include "ModelContainer.h"

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

        void* coreSimulator =
            ersAPIFunctionPointers.ERS_ModelContainer_AddSimulator(coreModelContainerInstance, tag.data(), static_cast<uint8_t>(type));

        return Ers::Simulator(coreSimulator);
    }

    /// @brief Remove the given simulator from this ModelContainer.
    /// @param simulator Pointer to the simulator to remove.
    /// @throws If the given simulator is a nullptr.
    void ModelContainer::RemoveSimulator(Ers::Simulator simulator)
    {
        assert(simulator.Valid());
        assert(FindSimulator(simulator.GetID()).Valid());
        ersAPIFunctionPointers.ERS_ModelContainer_RemoveSimulator(coreModelContainerInstance, simulator.Data());
    }

    /// @brief Find the simulator with the given tag/name.
    /// @param simulatorTag The tag/name of the simulator to find.
    /// @return Shared pointer to the simulator with given tag or nullptr if no such simulator is found.
    Ers::Simulator ModelContainer::FindSimulator(const std::string_view& simulatorTag)
    {
        void* foundCoreSimulator =
            ersAPIFunctionPointers.ERS_ModelContainer_FindSimulatorByTag(coreModelContainerInstance, simulatorTag.data());

        return Ers::Simulator(foundCoreSimulator);
    }

    /// @brief Find the simulator with the given ID.
    /// @param simulatorId The ID of the simulator to find.
    /// @return Shared pointer to the simulator with given ID or nullptr if no such simulator is found.
    Ers::Simulator ModelContainer::FindSimulator(const std::int32_t& simulatorId)
    {
        void* foundCoreSimulator = ersAPIFunctionPointers.ERS_ModelContainer_FindSimulatorById(coreModelContainerInstance, simulatorId);

        return Ers::Simulator(foundCoreSimulator);
    }

    /// @brief Return the number of simulators in the ModelContainer.
    std::size_t ModelContainer::SimulatorCount()
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_GetSimulatorsCount(coreModelContainerInstance);
    }

    /// @brief Add a dependency between simulators.
    /// @param from The simulator which can be scheduled.
    /// @param to The simulator to which can be scheduled.
    void ModelContainer::AddSimulatorDependency(Ers::Simulator from, Ers::Simulator to)
    {
        assert(from.Valid());
        assert(to.Valid());
        ersAPIFunctionPointers.ERS_ModelContainer_AddSimulatorDependency(coreModelContainerInstance, from.Data(), to.Data());
    }

    void ModelContainer::RemoveSimulatorDependency(Ers::Simulator from, Ers::Simulator to)
    {
        assert(from.Valid());
        assert(to.Valid());
        ersAPIFunctionPointers.ERS_ModelContainer_RemoveSimulatorDependency(coreModelContainerInstance, from.Data(), to.Data());
    }

    SimulationTime ModelContainer::CurrentTime() const
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_CurrentTime(coreModelContainerInstance);
    }

    void ModelContainer::Update(SimulationTime timeStep) const
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_Update_Blocking(coreModelContainerInstance, timeStep);
    }

    void ModelContainer::Start()
    {
        ersAPIFunctionPointers.ERS_ModelContainer_Start(coreModelContainerInstance);
    }

    // TODO
    bool ModelContainer::IsStarted() const
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_IsStarted(coreModelContainerInstance);
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
            vecSimulators.emplace_back(
                Ers::Simulator(ersAPIFunctionPointers.ERS_ModelContainer_GetSimulator(coreModelContainerInstance, i)));
        }
        return vecSimulators;
    }

    /// @brief Returns the simulator with the given ID.
    /// @param simulatorId The simulator ID to get.
    /// @return Returns a shared pointer to a simulator with the given ID.
    /// @throws If the simulator with the given ID was not found.
    Ers::Simulator ModelContainer::GetSimulator(const std::int32_t simulatorId)
    {
        void* coreSimulator = ersAPIFunctionPointers.ERS_ModelContainer_GetSimulatorById(coreModelContainerInstance, simulatorId);
        return Ers::Simulator(coreSimulator);
    }

    Ers::Simulator ModelContainer::GetSimulatorByIndex(int index)
    {
        return Ers::Simulator(ersAPIFunctionPointers.ERS_ModelContainer_GetSimulator(coreModelContainerInstance, index));
    }

    void* ModelContainer::Data()
    {
        return coreModelContainerInstance;
    }

    const void* const ModelContainer::Data() const
    {
        return coreModelContainerInstance;
    }

    void ModelContainer::SetPrecision(SimulationTime precision)
    {
        ersAPIFunctionPointers.ERS_ModelContainer_SetModelPrecision(coreModelContainerInstance, precision);
    }

    SimulationTime ModelContainer::GetPrecision() const
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_GetModelPrecision(coreModelContainerInstance);
    }

    double ModelContainer::GetSpeedUp() const
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_SimulationSpeedOverRealtime(coreModelContainerInstance);
    }

    bool ModelContainer::Valid() const
    {
        return coreModelContainerInstance != nullptr;
    }

    size_t Ers::ModelContainer::GetSeed() const
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_Seed(coreModelContainerInstance);
    }

    void ModelContainer::SetSeed(size_t newSeed)
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_SetSeed(coreModelContainerInstance, newSeed);
    }

    void ModelContainer::GenerateRandomSeed()
    {
        return ersAPIFunctionPointers.ERS_ModelContainer_GenerateRandomSeed(coreModelContainerInstance);
    }

    /// @brief Creates a model container
    ModelContainer ModelContainer::CreateModelContainer()
    {
        void* modelContainerInstancePtr = ersAPIFunctionPointers.ERS_ModelContainer_CreateModelContainer();
        ModelContainer output(modelContainerInstancePtr);
        ersAPIFunctionPointers.ERS_ModelContainer_Release(modelContainerInstancePtr);
        return output;
    }

    /// @brief Creates a model container with the given pointer to the ModelContainer in the core.
    /// @param coreInstance The pointer to the instance of an existing ModelContainer in the core.
    /// @param type The type of the ownership of this instance of ModelContainer with regard to the instance in the core.
    /// I.e. if the API ModelContainer is responsible for the creation and deletion: type = ObjectType::OWNER,
    ///		 if the API ModelContainer acts as an accessor for the ModelContainer in the core: type = ObjectType::ACCESSOR.
    ModelContainer::ModelContainer(void* coreInstance) :
        coreModelContainerInstance(coreInstance)
    {
        if (coreInstance != nullptr)
        {
            ersAPIFunctionPointers.ERS_ModelContainer_Increase(coreInstance); // Increase reference count
        }
    }

    ModelContainer::ModelContainer(ModelContainer&& other) noexcept :
        coreModelContainerInstance(other.coreModelContainerInstance)
    {
        other.coreModelContainerInstance = nullptr;
    }

    ModelContainer::~ModelContainer()
    {
        if (coreModelContainerInstance == nullptr)
        {
            return;
        }

        // Decrease reference count
        ersAPIFunctionPointers.ERS_ModelContainer_Release(coreModelContainerInstance);
        coreModelContainerInstance = nullptr;
    }

    ModelContainer& ModelContainer::operator=(ModelContainer&& other) noexcept
    {
        coreModelContainerInstance       = other.coreModelContainerInstance;
        other.coreModelContainerInstance = nullptr;

        return *this;
    }

} // namespace Ers
