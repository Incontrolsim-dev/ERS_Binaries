#include "EventScheduler.h"

#include "Ers/Api.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/APILocalEvent.h"
#include <cassert>

Ers::LocalEventKey Ers::EventScheduler::ScheduleLocalEvent(int priority, SimulationTime delayTime, std::function<void()> eventCallback)
{
    // TODO make use of a fast allocator within ERS
    auto* apiLocalEvent = new APILocalEvent{std::move(eventCallback)};

    auto destructLocalEvent = [](void* localEvent)
    {
        APILocalEvent* localEventData = static_cast<APILocalEvent*>(localEvent);
        delete localEventData;
    };

    return ersAPIFunctionPointers.ERS_EventScheduler_ScheduleLocalEvent(
        priority, delayTime, apiLocalEvent, LocalEventCallback, destructLocalEvent);
}

void* Ers::EventScheduler::GetLastScheduledSyncEvent()
{
    return ersAPIFunctionPointers.ERS_EventScheduler_LastScheduledSyncEvent();
}

uint32_t Ers::EventScheduler::GetEventCodeFromSyncEvent(void* syncEvent)
{
    return ersAPIFunctionPointers.ERS_EventScheduler_ExchangeSyncEventForEventID(syncEvent);
}

uint32_t Ers::EventScheduler::GetEventCodeFromSyncEvent()
{
    return ersAPIFunctionPointers.ERS_EventScheduler_ExchangeSyncEventForEventID(GetLastScheduledSyncEvent());
    ;
}

void Ers::EventScheduler::CancelEvent(Ers::LocalEventKey eventKey)
{
    ersAPIFunctionPointers.ERS_EventScheduler_CancelEvent(eventKey);
}

void Ers::EventScheduler::DelayEvent(LocalEventKey key, SimulationTime updatedDelayTime)
{
    ersAPIFunctionPointers.ERS_EventScheduler_DelayEvent(key, updatedDelayTime);
}

void* Ers::EventScheduler::ScheduleSyncEvent(
    const char* eventName,
    uint64_t eventTypeIdentifier,
    SimulationTime delay,
    int32_t targetSimulatorId,
    void (*senderSide)(),
    void (*targetSide)())
{

    void* syncEventHandle =
        ersAPIFunctionPointers.ERS_EventScheduler_ScheduleSyncEvent(delay, targetSimulatorId, eventTypeIdentifier, senderSide, targetSide);

    //  Set name on the identifier
    ersAPIFunctionPointers.ERS_SyncEvent_SetSyncEventName(syncEventHandle, eventName);

    return syncEventHandle;
}

void Ers::EventScheduler::SetPromise(int32_t outgoingSimulatorID, SimulationTime delayTime)
{
    ersAPIFunctionPointers.ERS_EventScheduler_SetPromise(delayTime, outgoingSimulatorID);
}
SimulationTime Ers::EventScheduler::GetPromise(int32_t outgoingSimulatorID)
{
    return ersAPIFunctionPointers.ERS_EventScheduler_GetPromise(outgoingSimulatorID);
}