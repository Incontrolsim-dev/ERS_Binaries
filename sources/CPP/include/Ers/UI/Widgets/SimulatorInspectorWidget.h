#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/Simulator/Simulator.h"

namespace Ers
{
    /// @brief Widget to inspect and modify a Simulator's data.
    class SimulatorInspectorWidget
    {
      public:
        SimulatorInspectorWidget();
        ~SimulatorInspectorWidget();

        /// @brief Show the window.
        /// @param simulator The simulator to inspect.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void Window(Simulator& simulator, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the widget.
        /// @param simulator The simulator to inspect.
        void Widget(Simulator& simulator);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
