#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    /// @brief Widget to show the visualization of a model.
    class VisualizationWidget
    {
      public:
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
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void
        Window(RenderContext& renderContext, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);
        /// @brief Show the widget.
        /// @param renderContext The render context to show the visualization of.
        void Widget(RenderContext& renderContext);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
