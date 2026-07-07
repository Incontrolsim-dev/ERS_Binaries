#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/SubModel/PersistentEvent.h"

namespace Ers
{
    class EventInspectorWidget
    {
        /// @brief Show the window.
        /// @param persistentEvent The event to inspect.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        static void
        Window(PersistentEvent persistentEvent, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the widget.
        /// @param persistentEvent The event to inspect.
        static void Widget(PersistentEvent persistentEvent);

        /// @brief Show a table containing generic SimEvent data that applies to both local- and sync-events.
        /// @param persistentEvent The event to inspect.
        static void EventDetails(PersistentEvent persistentEvent);
        /// @brief Show a table containing sync-event specific data.
        /// @param persistentEvent The event to inspect.
        static void SyncEventDetails(PersistentEvent persistentEvent);
        /// @brief Show a table containing local-event specific data.
        /// @param persistentEvent The event to inspect.
        static void LocalEventDetails(PersistentEvent persistentEvent);
    };
} // namespace Ers
