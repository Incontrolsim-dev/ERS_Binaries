using System;
using System.Numerics;
using Ers;

namespace SourceQueueServerSink
{
    internal struct SourceGenerateProductEvent : ILocalEvent<SourceGenerateProductEvent>
    {
        public Entity SourceEntity;

        public void OnEvent()
        {
            SubModel subModel = SubModel.Get();
            SourceBehavior source = SourceEntity.GetComponent<SourceBehavior>();

            // Only create a product when it can be moved to the next entity
            if (source.CurrentProduced == CEntity.InvalidEntity())
            {
                // Create the product
                Entity entity = subModel.CreateEntity(SourceEntity, $"Product{source.Produced + 1}");
                entity.AddComponent<Product>();
                source.Produced++;
                source.CurrentProduced = entity;

                // Move the product to the next simulation object
                Entity output = SourceEntity.GetComponent<ResourceComponent>().Value.GetOutputChannel(0);
                ChannelComponent.Open(output);
            }

            // Re-schedule this function, creating a loop
            ulong delay = subModel.ApplyModelPrecision(source.GenerationTime);
            EventScheduler.ScheduleLocalEvent(0, delay, new SourceGenerateProductEvent()
            {
                SourceEntity = SourceEntity
            });
        }
    }

    /// <summary>
    /// A bundle of data relevant to a source simulation object.
    /// </summary>
    /// <param name="source">The source's <see cref="SourceBehavior"/>.</param>
    /// <param name="outputEntity">The output channel entity of the source.</param>
    public readonly struct SourceBundle(SourceBehavior source, Entity outputEntity)
    {
        /// <summary>
        /// The source's <see cref="SourceBehavior"/>.
        /// </summary>
        public readonly SourceBehavior Source = source;
        /// <summary>
        /// The output channel entity of the source.
        /// </summary>
        public readonly Entity OutputEntity = outputEntity;
    }

    public class SourceBehavior : ScriptBehaviorComponent
    {
        public ulong GenerationTime = 5;
        public ulong Produced = 0;
        public Entity CurrentProduced = CEntity.InvalidEntity();

        /// <summary>
        /// Helper function to easily create a source simulation object.
        /// </summary>
        /// <param name="name">The name for the source entity.</param>
        /// <param name="pos">The position for the source.</param>
        /// <returns></returns>
        public static SourceBundle Create(string name, Vector3 pos)
        {
            SubModel subModel = SubModel.Get();
            Entity sourceEntity = subModel.CreateEntity(name);

            sourceEntity.AddComponent<ResourceComponent>();
            Entity sourceOutputEntity = subModel.CreateEntity(sourceEntity, "SourceOutput");
            ChannelComponent.AddChannelComponent(sourceOutputEntity, ChannelType.Output, sourceEntity);

            var transform = sourceEntity.AddComponent<TransformComponent>();
            transform.Value.Position = pos;
            transform.Value.Scale = new Vector3(4, 2, 1);

            SourceBehavior source = sourceEntity.AddComponent<SourceBehavior>();
            return new SourceBundle(source, sourceOutputEntity);
        }

        public override void OnStart()
        {
            // Start infinite product generating event loop
            ulong delay = SubModel.Get().ApplyModelPrecision(GenerationTime);
            EventScheduler.ScheduleLocalEvent(0, delay, new SourceGenerateProductEvent()
            {
                SourceEntity = ConnectedEntity
            });
        }

        public override void OnOutputChannelReady(Entity outputChannel)
        {
            if (CurrentProduced == CEntity.InvalidEntity())
                return;

            /*
             * Store toSend locally first, because CurrentProduced needs to be invalid before Send is called.
             * Otherwise, the receiving side of the channel may trigger this callback again
             * and CurrentProduced will still be valid, thus it would try to send the same entity again.
             */
            Entity toSend = CurrentProduced;
            CurrentProduced = CEntity.InvalidEntity();
            ChannelComponent.Send(outputChannel, toSend);
            ChannelComponent.Close(outputChannel);
        }
    }
}
