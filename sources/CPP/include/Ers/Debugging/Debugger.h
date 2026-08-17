#pragma once

#include <functional>

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/UI/Window.h"
#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    /// @brief Debugger tool for ERS models. Opens a debugger window.
    class Debugger
    {
      public:
        /// @brief Construct a new Debugger instance attached to the given ModelContainer.
        /// @param modelContainer The model container to debug.
        Debugger(Ers::ModelContainer& modelContainer);
        /// @brief Construct a new Debugger instance attached to the given ModelContainer, with a previously created Window.
        /// Normally, the platform is created automatically when the debugger is created.
        /// @param modelContainer The model container to debug.
        /// @param platform The platform the debugger should use.
        Debugger(Ers::ModelContainer& modelContainer, Window& platform);
        Debugger(const Debugger&)            = delete;
        Debugger(Debugger&&)                 = delete;
        Debugger& operator=(const Debugger&) = delete;
        Debugger& operator=(Debugger&&)      = delete;
        ~Debugger();

        /// @brief Get the Window used by this Debugger.
        /// @return
        Window GetWindow();
        Ers::RenderContext GetRenderContext();

        /// @brief Whether the debugger is currently running (updating the model).
        /// @return
        bool IsRunning() const;
        /// @brief Set whether the debugger is currently running (updating the model).
        /// @param value
        void IsRunning(bool value);

        bool Is3DMode() const;

        /// @brief Begin the update loop of the debugger. Be sure to call this in a loop for the debugger to work.
        ///
        /// Any rendering and ImGui code should go in between BeginUpdate and EndUpdate.
        void BeginUpdate();
        /// @brief End the update loop of the debugger. Be sure to call this in a loop for the debugger to work.
        void EndUpdate();

        /// @brief Open the debugger window. This should be called before loading textures and 3D models.
        static void Open();

        /// @brief Open the debugger to inspect, debug, and run the model. This function should be used instead of ModelManager::Update or
        /// ModelContainer::Update.
        /// @param modelContainer The model container to debug.
        /// @param render2D Optional 2D render function. Uses basic render system when no custom function is given. Is called for every
        /// simulator on each frame.
        /// @param render3D Optional 3D render function. Uses basic render system when no custom function is given. Is called for every
        /// simulator on each frame.
        /// @param renderUI Optional UI render function. Called every frame, regardless of 2D/3D render mode.
        static void
        Run(ModelContainer& modelContainer,
            const std::function<void(Ers::Debugger&, Ers::Simulator&)>& render2D = nullptr,
            const std::function<void(Ers::Debugger&, Ers::Simulator&)>& render3D = nullptr,
            const std::function<void(Ers::Debugger&)>& renderUI                  = nullptr);

      protected:
        /// @brief The name for the debugger's window.
        inline static constexpr const char* windowTitle = "ERS Debugger";
        /// @brief The Window used when a window needs to be created ahead of the debugger (see Debugger::Open).
        inline static Window* runWindow = nullptr;

      private:
        void* corePtr = nullptr;
    };
} // namespace Ers
