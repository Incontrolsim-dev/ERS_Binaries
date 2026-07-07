#pragma once

#include <memory>

#include "Ers/Utility/Util.h"

namespace Ers
{
    class ModelContainer; // Forward declaration

    /// @brief ModelManager is a wrapper class to provide access to the functionality of the ModelManager class in ers-core.
    /// This class is responsible for the creation and the management of ModelContainers.
    struct ModelManager
    {
      public:
        ModelManager()                               = delete;
        ModelManager(const ModelManager&)            = delete;
        ModelManager(ModelManager&&)                 = delete;
        ModelManager& operator=(const ModelManager&) = delete;
        ModelManager& operator=(ModelManager&&)      = delete;
        ~ModelManager()                              = delete;

        void AddModelContainer(ModelContainer& modelContainer, SimulationTime releaseTime);
        void RemoveModelContainer(ModelContainer& modelContainer);
        bool HasModelContainer(const ModelContainer& modelContainer) const;
        ModelContainer GetModelContainerAt(const std::size_t& index);

        /// @brief The number of ModelContainers in this ModelManager.
        /// @return
        std::size_t Count();
        void Update();

        /// @brief Run all models that are currently in the ModelManager until completion and print a combined progress bar while running.
        void RunWithProgressBar();

        static ModelManager& Get();
    };

} // namespace Ers
