#pragma once
#include "Ers/SubModel/SubModel.h"
#include "Ers/SubModel/SyncEvent.h"
#include "Ers/Utility/Util.h"

namespace Ers
{
    struct MoveEntitySyncEvent : Ers::ISyncEvent<MoveEntitySyncEvent>
    {

        EntityID EntityInFlight;

        static const char* GetName() { return "MoveEntity"; }

        void OnSenderSide()
        {
            // Copy from source to intermediate
            EntityInFlight = Ers::GetSubModel().SendEntity(SyncEvent::GetSyncEventTarget(), EntityInFlight).id;
        }

        void OnTargetSide()
        {
            // Copy from intermediate to target
            EntityInFlight = Ers::GetSubModel().ReceiveEntity(SyncEvent::GetSyncEventSender(), SentEntity(EntityInFlight));
        }
    };
} // namespace Ers