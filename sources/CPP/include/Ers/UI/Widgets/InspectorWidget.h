#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/Entity.h"
#include "Ers/SubModel/PersistentEvent.h"
#include "Ers/UI/Widgets/WidgetTypes.h"

namespace Ers
{
    /// @brief Widget that wraps around the other inspector widgets to have a single window or widget where any of the SelectedType types
    /// can be inspected.
    class InspectorWidget
    {
      public:
        InspectorWidget();
        ~InspectorWidget();

        /// @brief Show the window.
        /// @param selectedType Indicator for the type that is currently selected / shown.
        /// @param modelContainer The ModelContainer that may be inspected.
        /// @param simulator The Simulator that may be inspector.
        /// @param entitySimulator The Simulator in which the inspected entity lives.
        /// @param entity The Entity that may be inspected.
        /// @param persistentEvent The event that may be inspected.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void Window(
            SelectedType selectedType,
            ModelContainer& modelContainer,
            Simulator* simulator,
            Simulator* entitySimulator,
            EntityID entity,
            PersistentEvent& persistentEvent,
            const char* name,
            bool* open             = nullptr,
            ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief Show the window.
        /// @param selectedType Indicator for the type that is currently selected / shown.
        /// @param modelContainer The ModelContainer that may be inspected.
        /// @param simulator The Simulator that may be inspector.
        /// @param entitySimulator The Simulator in which the inspected entity lives.
        /// @param entity The Entity that may be inspected.
        /// @param persistentEvent The event that may be inspected.
        void Widget(
            SelectedType selectedType,
            ModelContainer& modelContainer,
            Simulator* simulator,
            Simulator* entitySimulator,
            EntityID entity,
            PersistentEvent& persistentEvent);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
