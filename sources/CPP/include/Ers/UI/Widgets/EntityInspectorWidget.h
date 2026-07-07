#pragma once

#include "Ers/External/ImGuiCpp.hpp"

#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/Entity.h"

namespace Ers
{
    /// @brief Widget to inspect and edit an Entity and its attached components.
    class EntityInspectorWidget
    {
        EntityInspectorWidget()  = delete;
        ~EntityInspectorWidget() = delete;

        /// @brief The full entity inspector widget in dedicated window.
        /// @param simulator The Simulator in which the inspected entity lives.
        /// @param entity The entity to inspect.
        /// @param name The name for the window.
        /// @param open Whether the window is open.
        /// @param flags Any ImGuiWindowFlags for the window.
        static void Window(
            Simulator& simulator, EntityID entity, const char* name, bool* open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
        /// @brief The full entity inspector widget.
        /// @param simulator The Simulator in which the inspected entity lives.
        /// @param entity The entity to inspect.
        static void Widget(Simulator& simulator, EntityID entity);

        /// @brief A table with editable entity information.
        /// @param simulator The Simulator in which the inspected entity lives.
        /// @param entity The entity to inspect.
        static void EntityData(Simulator& simulator, EntityID entity);
        /// @brief Inspect and edit a list of components attached to a given entity.
        /// @param simulator The Simulator in which the inspected entity lives.
        /// @param entity The entity to inspect.
        static void ComponentData(Simulator& simulator, EntityID entity);
    };
} // namespace Ers
