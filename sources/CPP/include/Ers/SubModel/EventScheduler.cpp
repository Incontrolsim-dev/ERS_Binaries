#include "EventScheduler.h"

#include "Ers/Api.h"
#include "Ers/Model/Simulator/Simulator.h"
#include <cassert>
#include <mutex>
#include <unordered_map>

void* Ers::EventScheduler::GetLastScheduledSyncEvent()
{
    return Ers::Engine::ERS_EventScheduler_LastScheduledSyncEvent();
}

uint32_t Ers::EventScheduler::GetEventCodeFromSyncEvent(void* syncEvent)
{
    return Ers::Engine::ERS_EventScheduler_ExchangeSyncEventForEventID(syncEvent);
}

uint32_t Ers::EventScheduler::GetEventCodeFromSyncEvent()
{
    return Ers::Engine::ERS_EventScheduler_ExchangeSyncEventForEventID(GetLastScheduledSyncEvent());
    ;
}

void Ers::EventScheduler::CancelEvent(Ers::LocalEventKey eventKey)
{
    Ers::Engine::ERS_EventScheduler_CancelEvent(eventKey);
}

void Ers::EventScheduler::DelayEvent(LocalEventKey key, SimulationTime updatedDelayTime)
{
    Ers::Engine::ERS_EventScheduler_DelayEvent(key, updatedDelayTime);
}

void Ers::EventScheduler::SetPromise(int32_t outgoingSimulatorID, SimulationTime delayTime)
{
    Ers::Engine::ERS_EventScheduler_SetPromise(delayTime, outgoingSimulatorID);
}
SimulationTime Ers::EventScheduler::GetPromise(int32_t outgoingSimulatorID)
{
    return Ers::Engine::ERS_EventScheduler_GetPromise(outgoingSimulatorID);
}