#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/UI/Widgets/WidgetTypes.h"
#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    /// @brief Widget to show the visualization of a model.
    class VisualizationWidget
    {
      public:
        /// @brief Arguments used for entity selection.
        struct EntitySelectionArgs
        {
            /// @brief The ModelContainer that is visualized, in which all entities live.
            ModelContainer& Model;
            /// @brief The currently selected type.
            SelectedType& Type;
            /// @brief The currently selected entity.
            EntityID& SelectedEntity;
            /// @brief The Simulator in which the currently selected entity lives.
            Simulator*& SelectedEntitySimulator;

            EntitySelectionArgs() = delete;
            /// @brief Construct a new EntitySelectionArgs object.
            /// @param modelContainer The ModelContainer that is visualized, in which all entities live.
            /// @param selectedType The currently selected type.
            /// @param selectedEntity The currently selected entity.
            /// @param selectedEntitySimulator The Simulator in which the currently selected entity lives.
            EntitySelectionArgs(
                ModelContainer& modelContainer, SelectedType& selectedType, EntityID& selectedEntity, Simulator*& selectedEntitySimulator);
        };

        VisualizationWidget();
        ~VisualizationWidget();

        /// @brief Get whether the visualization is in 3D mode.
        /// @return True when 3D rendering is enabled, false when 2D rendering is enabled.
        bool GetIs3DMode() const;
        /// @brief Set whether the visualization is in 3D mode.
        /// @param value True to enable 3D rendering, false to enable 2D rendering.
        void SetIs3DMode(bool value);

        /// @brief Show the window.
        /// @param renderContext The render context to show the visualization of.
        /// @param entitySelectionArgs Arguments used to handle entity selection.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void Window(
            RenderContext& renderContext,
            EntitySelectionArgs* entitySelectionArgs,
            const char* name,
            bool* open             = nullptr,
            ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);

        /// @brief Begin the widget's default window. Call Widget() and EndWindow() after this.
        /// Additional ImGui code can be added in between the extend the default window's functionality.
        /// @param renderContext The render context to show the visualization of.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void BeginWindow(
            RenderContext& renderContext, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);
        /// @brief End the widget's default window. Call BeginWindow() and Widget() before this.
        /// Additional ImGui code can be added in between the extend the default window's functionality.
        void EndWindow();

        /// @brief Show the widget.
        /// @param renderContext The render context to show the visualization of.
        /// @param entitySelectionArgs Arguments used to handle entity selection.
        void Widget(RenderContext& renderContext, EntitySelectionArgs* entitySelectionArgs = nullptr);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
