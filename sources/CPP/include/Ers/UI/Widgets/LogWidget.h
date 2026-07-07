#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Logger.h"

namespace Ers
{
    /// @brief Widget showing the ERS log.
    class LogWidget
    {
      public:
        LogWidget();
        ~LogWidget();

        /// @brief Get the minimum log level that is shown.
        /// @return
        Logger::LogLevel GetSelectedLogLevel() const;
        /// @brief Set the minimum log level that is shown.
        /// @param level The new log level.
        void SetSelectedLogLevel(Logger::LogLevel level);

        /// @brief Get whether the log automatically scrolls to the latest log entry.
        /// @return
        bool GetAutoScroll() const;
        /// @brief Set whether the log automatically scrolls to the latest log entry.
        /// @param value True to enable auto-scroll, false to disable.
        void SetAutoScroll(bool value);

        /// @brief Show the window.
        /// @param name The name for the window.
        /// @param open Whether the window is currently open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void Window(const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);
        /// @brief Show the widget.
        void Widget();

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
