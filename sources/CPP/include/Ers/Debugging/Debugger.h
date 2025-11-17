#pragma once

#include <functional>

#include "Ers/Debugging/Platform.h"
#include "Ers/Model/ModelContainer.h"
#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    /// @brief Debugger tool for ERS models. Opens a debugger window.
    class Debugger
    {
      public:
        /// @brief Construct a the Debugger, attached to the given ModelContainer.
        /// @param modelContainer The model to debug.
        Debugger(Ers::ModelContainer& modelContainer);
        Debugger(const Debugger&)            = delete;
        Debugger(Debugger&&)                 = delete;
        Debugger& operator=(const Debugger&) = delete;
        Debugger& operator=(Debugger&&)      = delete;
        ~Debugger();

        Ers::Visualization::RenderContext GetRenderContext();

        bool Is3DMode() const;
        bool ShowBackgroundGrid() const;

        /// @brief Update loop for the debugger. Be sure to call this in a loop for the debugger to work.
        void Update();

        /// @brief Open the debugger window. This should be called before loading textures and 3D models.
        static void Open();

        /// @brief Open the debugger to inspect, debug, and run the model. This function should be used instead of ModelManager::Update or
        /// ModelContainer::Update.
        /// @param modelContainer The model container to debug.
        /// @param render2D Optional 2D render function. Uses basic render system when no custom function is given.
        /// @param render3D Optional 3D render function. Uses basic render system when no custom function is given.
        static void
        Run(ModelContainer& modelContainer,
            const std::function<void(Ers::Visualization::RenderContext&)>& render2D = nullptr,
            const std::function<void(Ers::Visualization::RenderContext&)>& render3D = nullptr);

      private:
        void* coreInstance;
        static Platform* platform;
    };
} // namespace Ers
