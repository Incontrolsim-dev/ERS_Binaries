#include "EntityInspectorWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    void EntityInspectorWidget::Window(Simulator& simulator, EntityID entity, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_EntityInspectorWidget_Window(simulator.CorePtr(), entity, name, open, flags);
    }

    void EntityInspectorWidget::Widget(Simulator& simulator, EntityID entity)
    {
        Ers::Engine::ERS_EntityInspectorWidget_Widget(simulator.CorePtr(), entity);
    }

    void EntityInspectorWidget::EntityData(Simulator& simulator, EntityID entity)
    {
        Ers::Engine::ERS_EntityInspectorWidget_EntityData(simulator.CorePtr(), entity);
    }

    void EntityInspectorWidget::ComponentData(Simulator& simulator, EntityID entity)
    {
        Ers::Engine::ERS_EntityInspectorWidget_ComponentData(simulator.CorePtr(), entity);
    }
} // namespace Ers
