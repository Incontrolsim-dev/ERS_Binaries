#include "Ers/Model/ModelManager.h"
#include "Ers/Api.h"
#include "Ers/Logger.h"
#include "Ers/Model/ModelContainer.h"

#include <cassert>
#include <functional>
#include <stdexcept>

namespace Ers
{
    /// @brief Add the given ModelContainer to this ModelManager.
    /// The ModelManager will update the ModelContainer until it reaches the ReleaseTime
    /// @param modelContainer The given ModelContainer to add.
    /// @param releaseTime When this time is reached the ModelContainer is removed from the ModelManager.
    void ModelManager::AddModelContainer(ModelContainer& modelContainer, SimulationTime releaseTime)
    {
        assert(modelContainer.Valid());
        assert(!HasModelContainer(modelContainer));
        Ers::Engine::ERS_ModelManager_AddModelContainer(this, modelContainer.CorePtr(), releaseTime);
    }

    /// @brief Remove the given ModelContainer from this ModelManager.
    /// NOTE: This will invalidate of the given ModelContainer.
    /// @param modelContainer The given ModelContainer to remove.
    void ModelManager::RemoveModelContainer(ModelContainer& modelContainer)
    {
        assert(modelContainer.Valid());
        if (!HasModelContainer(modelContainer))
        {
            Ers::Logger::Error("ModelContainer is not inside this ModelContainer");
            return;
        }

        Ers::Engine::ERS_ModelManager_RemoveModelContainer(this, modelContainer.CorePtr());
    }

    size_t ModelManager::Count()
    {
        return Ers::Engine::ERS_ModelManager_CountModelContainers(this);
    }

    /// @brief Returns a shared pointer to the ModelContainer at the given position in the vector of ModelContainers.
    /// @param index The index of the ModelContainer to get.
    /// @return Returns a shared pointer to the ModelContainer at the given position.
    /// @throws If no ModelContainer is found at given index, e.g. if index is out of bound.
    ModelContainer ModelManager::GetModelContainerAt(const std::size_t& index)
    {
        void* coreModelContainerPtr = Ers::Engine::ERS_ModelManager_GetModelContainerAt(this, index);
        return ModelContainer(coreModelContainerPtr);
    }

    /// @brief Checks whether the given ModelContainer is present in the collection of the ModelContainers of this ModelManager.
    /// @param modelContainer The given ModelContainer to check.
    /// @return Returns true if the given ModelContainer is present in the vector of ModelContainers associated with this ModelManager,
    /// otherwise returns false
    bool ModelManager::HasModelContainer(const ModelContainer& modelContainer) const
    {
        return Ers::Engine::ERS_ModelManager_HasModelContainer(this, modelContainer.CorePtr());
    }

    //============== Protected functions ====================

    /// @brief Performs Update for the ModelContainers of this ModelManager by invoking the corresponding function of the core.
    void ModelManager::Update()
    {
        Ers::Engine::ERS_ModelManager_Update(this);
    }

    void ModelManager::RunWithProgressBar()
    {
        Ers::Engine::ERS_RunWithProgressBar();
    }

    ModelManager& ModelManager::Get()
    {
        return *static_cast<ModelManager*>(Ers::Engine::ERS_ModelManager_GetModelManager());
    }

} // namespace Ers
