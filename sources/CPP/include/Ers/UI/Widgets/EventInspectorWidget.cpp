#include "EventInspectorWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    void EventInspectorWidget::Window(PersistentEvent persistentEvent, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_EventInspectorWidget_Window(persistentEvent.CorePtr(), name, open, flags);
    }

    void EventInspectorWidget::Widget(PersistentEvent persistentEvent)
    {
        Ers::Engine::ERS_EventInspectorWidget_Widget(persistentEvent.CorePtr());
    }

    void EventInspectorWidget::EventDetails(PersistentEvent persistentEvent)
    {
        Ers::Engine::ERS_EventInspectorWidget_EventDetails(persistentEvent.CorePtr());
    }

    void EventInspectorWidget::SyncEventDetails(PersistentEvent persistentEvent)
    {
        Ers::Engine::ERS_EventInspectorWidget_SyncEventDetails(persistentEvent.CorePtr());
    }

    void EventInspectorWidget::LocalEventDetails(PersistentEvent persistentEvent)
    {
        Ers::Engine::ERS_EventInspectorWidget_LocalEventDetails(persistentEvent.CorePtr());
    }
} // namespace Ers
