#pragma once

#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// @brief Widget to control the execution of a ModelContainer.
    /// Includes play, pause, step and speed control.
    class RunControlsWidget
    {
      public:
        RunControlsWidget();
        ~RunControlsWidget();

        /// @brief Show the window.
        /// @param modelContainer The model to control.
        /// @param isRunning Whether the model is currently running.
        /// @param name The name for the window.
        void Window(ModelContainer& modelContainer, bool& isRunning, const char* name);
        /// @brief Show the widget.
        /// @param modelContainer The model to control.
        /// @param isRunning Whether the model is currently running.
        void Widget(ModelContainer& modelContainer, bool& isRunning);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
