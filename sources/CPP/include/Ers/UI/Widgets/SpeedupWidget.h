#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// @brief Widget that shows the speedup over realtime of a ModelContainer.
    class SpeedupWidget
    {
      public:
        SpeedupWidget();
        ~SpeedupWidget();

        /// @brief Show the window.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void Window(const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the widget.
        void Widget();

        /// @brief Update the speedup widget. This is where the widget collects data from the ModelContainer.
        ///
        /// This function should always be called in the main update loop of the program,
        /// even when the widget itself is not shown.
        /// Otherwise there will be gaps in the speedup widget's data.
        /// @param modelContainer The model to read the speedup from.
        void Update(const ModelContainer& modelContainer);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
