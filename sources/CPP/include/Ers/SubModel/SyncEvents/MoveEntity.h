#pragma once
#include "Ers/SubModel/ErsEvent.h"
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
            EntityInFlight = Ers::SubModel::Get().SendEntity(SyncEvent::GetSyncEventTarget(), EntityInFlight).id;
        }

        void OnTargetSide()
        {
            // Copy from intermediate to target
            EntityInFlight = Ers::SubModel::Get().ReceiveEntity(SyncEvent::GetSyncEventSender(), SentEntity(EntityInFlight));
        }

        ERS_EVENT(EntityInFlight)
    };
} // namespace Ers
