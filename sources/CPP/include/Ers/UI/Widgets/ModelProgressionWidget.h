#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"

namespace Ers
{
    /// @brief Widget to show the simulation progression of the simulators in a model.
    class ModelProgressionWidget
    {
      public:
        ModelProgressionWidget();
        ~ModelProgressionWidget();

        /// @brief Show the window.
        /// @param modelContainer The ModelContainer whose progression to show.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        /// @return The selected Simulator when the user clicks on a timeline bar, otherwise nullptr.
        Simulator*
        Window(ModelContainer& modelContainer, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer whose progression to show.
        /// @param name The name for the window.
        /// @return The selected Simulator when the user clicks on a timeline bar, otherwise nullptr.
        Simulator* Widget(ModelContainer& modelContainer);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
