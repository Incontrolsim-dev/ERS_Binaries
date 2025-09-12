using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ers;

namespace Ers
{
    /// <summary>
    /// Helper to copy an entity to a new submodel, this helper is both a sync event in and off itself, and can be used as part of
    /// another sync event
    /// </summary>
    public partial struct MoveEntitySyncEvent : ISyncEvent<MoveEntitySyncEvent>
    {
        /// <summary>
        /// The entity "to be moved", "being moved" and "received"
        /// </summary>
        public Entity EntityInFlight;

        public static string Name => "Move Entity";

        public void OnSenderSide()
        {
            // Copy from source to intermediate
            EntityInFlight = SubModel.GetSubModel().SendEntity(SyncEvent.GetTargetSimulatorId(), EntityInFlight).id;
        }

        public void OnTargetSide()
        {
            // Copy from intermediate to target
            EntityInFlight = SubModel.GetSubModel().ReceiveEntity(SyncEvent.GetSenderSimulatorId(), new SentEntity(EntityInFlight));
        }
    }
}
