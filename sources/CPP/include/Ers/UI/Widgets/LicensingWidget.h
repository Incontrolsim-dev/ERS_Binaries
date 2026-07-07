#pragma once

#include "Ers/External/ImGuiCpp.hpp"

namespace Ers
{
    /// @brief Widget for license activation and management.
    class LicensingWidget
    {
      public:
        LicensingWidget();
        ~LicensingWidget();

        /// @brief Show the window.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void Window(const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the widget.
        void Widget();

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
