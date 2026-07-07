#include "PersistentEvent.h"

#include "Ers/Api.h"

namespace Ers
{
    PersistentEvent::PersistentEvent()
    {
        corePtr = Ers::Engine::ERS_PersistentEvent_Create();
    }

    PersistentEvent::~PersistentEvent()
    {
        Ers::Engine::ERS_PersistentEvent_Release(corePtr);
        corePtr = nullptr;
    }

    bool PersistentEvent::IsEmpty() const
    {
        return Ers::Engine::ERS_PersistentEvent_IsEmpty(corePtr);
    }

    Simulator PersistentEvent::GetSimulator()
    {
        return Simulator(Ers::Engine::ERS_PersistentEvent_GetSimulator(corePtr));
    }

    SimEvent PersistentEvent::GetSimEvent()
    {
        return SimEvent(Ers::Engine::ERS_PersistentEvent_GetSimEvent(corePtr));
    }
} // namespace Ers
