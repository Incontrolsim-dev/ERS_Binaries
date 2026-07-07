#include "SimEvent.h"

#include "Ers/Api.h"

namespace Ers
{
    SimEvent::SimEvent(void* corePtr) :
        corePtr(corePtr)
    {
    }

    SimulationTime SimEvent::GetTime() const
    {
        return static_cast<SimulationTime>(Ers::Engine::ERS_SimEvent_Get_Time(corePtr));
    }

    uint32_t SimEvent::GetPriority() const
    {
        return Ers::Engine::ERS_SimEvent_Get_Priority(corePtr);
    }

    bool SimEvent::IsSyncEvent() const
    {
        return Ers::Engine::ERS_SimEvent_IsSyncEvent(corePtr);
    }
} // namespace Ers
