#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// @brief Widget to inspect and modify a ModelContainer's data.
    class ModelContainerInspectorWidget
    {
      public:
        /// @brief Show the window.
        /// @param modelContainer The ModelContainer to inspect.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        static void
        Window(ModelContainer& modelContainer, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer to inspect.
        static void Widget(ModelContainer& modelContainer);
    };
} // namespace Ers
