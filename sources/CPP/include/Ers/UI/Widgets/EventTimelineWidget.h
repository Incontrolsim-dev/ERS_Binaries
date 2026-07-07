#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"
#include "Ers/SubModel/PersistentEvent.h"

namespace Ers
{
    /// @brief Widget showing a timeline of events.
    class EventTimelineWidget
    {
      public:
        EventTimelineWidget();
        ~EventTimelineWidget();

        /// @brief Get whether local-events are shown on the timeline.
        /// @return
        bool GetShowLocalEvents() const;
        /// @brief Set whether local events are shown on the timeline.
        /// @param value True to show local-events, false to hide them.
        void SetShowLocalEvents(bool value);

        /// @brief Get whether sync-event are shown on the timeline.
        /// @return
        bool GetShowSyncEvents() const;
        /// @brief Set whether sync-events are shown on the timeline.
        /// @param value True to show sync-events, false to hide them.
        void SetShowSyncEvents(bool value);

        /// @brief Get whether the timeline automatically scrolls along with the simulation time.
        /// @return
        bool GetAutoScroll() const;
        /// @brief Set whether the timeline automatically scrolls along with the simulation time.
        /// @param value True to enable auto-scroll, false to disable it.
        void SetAutoScroll(bool value);

        /// @brief Get the maximum number of events to show on the timeline.
        /// @return
        size_t GetMaxEvents() const;
        /// @brief Set the maximum number of events to show on the timeline.
        /// @param value
        void SetMaxEvents(size_t value);

        /// @brief Show the window.
        /// @param modelContainer The ModelContainer whose event timeline to show.
        /// @param isRunning Whether the model is currently running.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        /// @return True when an event is selected, false when not.
        bool Window(
            ModelContainer& modelContainer,
            bool isRunning,
            const char* name,
            bool* open             = nullptr,
            ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);
        /// @brief Show the window.
        /// @param modelContainer The ModelContainer whose event timeline to show.
        /// @param persistentEvent The currently selected PersistentEvent. Will be modified when an event is selected.
        /// @param isRunning Whether the model is currently running.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        /// @return True when an event is selected, false when not.
        bool Window(
            ModelContainer& modelContainer,
            PersistentEvent& persistentEvent,
            bool isRunning,
            const char* name,
            bool* open             = nullptr,
            ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);

        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer whose event timeline to show.
        /// @param isRunning Whether the model is currently running.
        /// @return True when an event is selected, false when not.
        bool Widget(ModelContainer& modelContainer, bool isRunning);
        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer whose event timeline to show.
        /// @param persistentEvent The currently selected PersistentEvent. Will be modified when an event is selected.
        /// @param isRunning Whether the model is currently running.
        /// @return True when an event is selected, false when not.
        bool Widget(ModelContainer& modelContainer, PersistentEvent& persistentEvent, bool isRunning);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
