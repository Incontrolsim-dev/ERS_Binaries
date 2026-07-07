#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/Entity.h"
#include "Ers/UI/Widgets/WidgetTypes.h"

namespace Ers
{
    /// @brief Widget that shows the hierarchy of a ModelContainer with all Simulators and entities.
    class ModelHierarchyWidget
    {
      public:
        ModelHierarchyWidget();
        ~ModelHierarchyWidget();

        /// @brief Show the window.
        /// @param modelContainer The ModelContainer to show the hierarchy of.
        /// @param selectedSimulator The currently selected Simulator. Will be overwritten when another one is selected.
        /// @param selectedEntitySimulator The Simulator in which the selected entity lives. Will be overwritten when another one is
        /// selected.
        /// @param selectedEntity The currently selected entity. Will be overwritten when another one is selected.
        /// @param selectedType Indicator for the type that is currently selected.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        /// @return True when something is selected, otherwise false.
        bool Window(
            ModelContainer& modelContainer,
            Simulator*& selectedSimulator,
            Simulator*& selectedEntitySimulator,
            EntityID& selectedEntity,
            SelectedType& selectedType,
            const char* name,
            bool* open             = nullptr,
            ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);
        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer to show the hierarchy of.
        /// @param selectedSimulator The currently selected Simulator. Will be overwritten when another one is selected.
        /// @param selectedEntitySimulator The Simulator in which the selected entity lives. Will be overwritten when another one is
        /// selected.
        /// @param selectedEntity The currently selected entity. Will be overwritten when another one is selected.
        /// @param selectedType Indicator for the type that is currently selected.
        /// @return True when something is selected, otherwise false.
        static bool Widget(
            ModelContainer& modelContainer,
            ImGuiTreeNodeFlags treeNodeFlags,
            Simulator*& selectedSimulator,
            Simulator*& selectedEntitySimulator,
            EntityID& selectedEntity,
            SelectedType& selectedType);
        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer to show the hierarchy of.
        /// @param treeNodeFlags Any ImGuiTreeNodeFlags to apply to all nodes of the hierarchy.
        static void Widget(ModelContainer& modelContainer, ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_None);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
