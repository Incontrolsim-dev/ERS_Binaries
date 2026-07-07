#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/ModelContainer.h"

namespace Ers
{
    /// @brief Widget to show the structure of a model (simulator dependencies).
    class ModelStructureWidget
    {
      public:
        /// @brief The mode of the heat map.
        enum class HeatMapMode : int
        {
            /// @brief No heatmap, just show the simulators.
            Off = 0,
            /// @brief Heat map of the scheduled local-events per simulator.
            LocalEvents = 1,
            /// @brief Heat map of the incoming sync-events per simulator.
            IncomingSyncEvents = 2,
        };

        /// @brief The style for the simulator groups rendering.
        enum class GroupStyle : int
        {
            MetaBalls     = 0,
            BoundingBoxes = 1,
        };

        ModelStructureWidget();
        ~ModelStructureWidget();

        /// @brief Whether to show the background grid.
        /// @return
        bool GetShowGrid() const;
        /// @brief Set whether to show the background grid.
        /// @param value True to show the grid, false to hide it.
        void SetShowGrid(bool value);

        /// @brief Get the selected heat map mode.
        /// @return
        HeatMapMode GetSelectedHeatMapMode() const;
        /// @brief Set the selected heat map mode.
        /// @param mode
        void SetSelectedHeatMapMode(HeatMapMode mode);

        /// @brief Get whether the simulator groups are shown.
        /// @return
        bool GetShowSimulatorGroups() const;
        /// @brief Set whether the simulator groups are shown.
        /// @param value True to show the simulator groups, false to hide them.
        void SetShowSimulatorGroups(bool value);

        /// @brief Get whether the simulator super groups are shown.
        /// @return
        bool GetShowSimulatorSuperGroups() const;
        /// @brief Set whether the simulator super groups are shown.
        /// @param value True to show the super groups, false to hide them.
        void SetShowSimulatorSuperGroups(bool value);

        /// @brief Get the selected group rendering style.
        /// @return
        GroupStyle GetSelectedGroupStyle() const;
        /// @brief Set the selected group rendering style.
        /// @param style
        void SetSelectedGroupStyle(GroupStyle style);

        /// @brief Show the window.
        /// @param modelContainer The ModelContainer to show the structure of.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        void
        Window(ModelContainer& modelContainer, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar);
        /// @brief Show the widget.
        /// @param modelContainer The ModelContainer to show the structure of.
        /// @param heatMapMode The heat map mode to show.
        void Widget(ModelContainer& modelContainer, HeatMapMode heatMapMode = HeatMapMode::Off);

        void* CorePtr() { return corePtr; }
        const void* CorePtr() const { return corePtr; }

      private:
        /// Core instance pointer
        void* corePtr = nullptr;
    };
} // namespace Ers
