#include "EventTimelineWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    EventTimelineWidget::EventTimelineWidget()
    {
        corePtr = Ers::Engine::ERS_EventTimelineWidget_Create();
    }

    EventTimelineWidget::~EventTimelineWidget()
    {
        Ers::Engine::ERS_EventTimeLineWidget_Destroy(corePtr);
    }

    bool EventTimelineWidget::GetShowLocalEvents() const
    {
        return Ers::Engine::ERS_EventTimelineWidget_Get_ShowLocalEvents(corePtr);
    }

    void EventTimelineWidget::SetShowLocalEvents(bool value)
    {
        Ers::Engine::ERS_EventTimelineWidget_Set_ShowLocalEvents(corePtr, value);
    }

    bool EventTimelineWidget::GetShowSyncEvents() const
    {
        return Ers::Engine::ERS_EventTimelineWidget_Get_ShowSyncEvents(corePtr);
    }

    void EventTimelineWidget::SetShowSyncEvents(bool value)
    {
        Ers::Engine::ERS_EventTimelineWidget_Set_ShowSyncEvents(corePtr, value);
    }

    bool EventTimelineWidget::GetAutoScroll() const
    {
        return Ers::Engine::ERS_LogWidget_Get_AutoScroll(corePtr);
    }

    void EventTimelineWidget::SetAutoScroll(bool value)
    {
        Ers::Engine::ERS_EventTimelineWidget_Set_AutoScroll(corePtr, value);
    }

    size_t EventTimelineWidget::GetMaxEvents() const
    {
        return Ers::Engine::ERS_EventTimelineWidget_Get_MaxEvents(corePtr);
    }

    void EventTimelineWidget::SetMaxEvents(size_t value)
    {
        Ers::Engine::ERS_EventTimelineWidget_Set_MaxEvents(corePtr, value);
    }

    bool EventTimelineWidget::Window(ModelContainer& modelContainer, bool isRunning, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        return Ers::Engine::ERS_EventTimelineWidget_Window(corePtr, modelContainer.CorePtr(), nullptr, isRunning, name, open, flags);
    }

    bool EventTimelineWidget::Window(
        ModelContainer& modelContainer,
        PersistentEvent& persistentEvent,
        bool isRunning,
        const char* name,
        bool* open,
        ImGuiWindowFlags flags)
    {
        return Ers::Engine::ERS_EventTimelineWidget_Window(
            corePtr, modelContainer.CorePtr(), persistentEvent.CorePtr(), isRunning, name, open, flags);
    }

    bool EventTimelineWidget::Widget(ModelContainer& modelContainer, bool isRunning)
    {
        return Ers::Engine::ERS_EventTimelineWidget_Widget(corePtr, modelContainer.CorePtr(), nullptr, isRunning);
    }

    bool EventTimelineWidget::Widget(ModelContainer& modelContainer, PersistentEvent& persistentEvent, bool isRunning)
    {
        return Ers::Engine::ERS_EventTimelineWidget_Widget(corePtr, modelContainer.CorePtr(), persistentEvent.CorePtr(), isRunning);
    }
} // namespace Ers
