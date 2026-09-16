using System;
using System.Numerics;
using Ers;

namespace SourceQueueServerSink
{
    /// <summary>
    /// A bundle of data relevant to a sink simulation object.
    /// </summary>
    /// <param name="sink">The sink's <see cref="SinkBehavior"/>.</param>
    /// <param name="inputEntity">The input channel entity of the sink.</param>
    public readonly struct SinkBundle(SinkBehavior sink, Entity inputEntity)
    {
        /// <summary>
        /// The sink's <see cref="SinkBehavior"/>.
        /// </summary>
        public readonly SinkBehavior Sink = sink;
        /// <summary>
        /// The input channel entity of the sink.
        /// </summary>
        public readonly Entity InputEntity = inputEntity;
    }

    public class SinkBehavior : ScriptBehaviorComponent
    {
        public ulong Received = 0;

        /// <summary>
        /// Helper function to easily create a sink simulation object.
        /// </summary>
        /// <param name="name">The name for the sink entity.</param>
        /// <param name="pos">The position for the sink.</param>
        /// <returns></returns>
        public static SinkBundle Create(string name, Vector3 pos)
        {
            SubModel subModel = SubModel.Get();
            Entity sinkEntity = subModel.CreateEntity(name);
            
            sinkEntity.AddComponent<ResourceComponent>();
            Entity sinkInputEntity = subModel.CreateEntity(sinkEntity, "SinkInput");
            ChannelComponent.AddChannelComponent(sinkInputEntity, ChannelType.Input, sinkEntity);

            var transform = sinkEntity.AddComponent<TransformComponent>();
            transform.Value.Position = pos;
            transform.Value.Scale = new Vector3(4, 2, 1);

            SinkBehavior sink = sinkEntity.AddComponent<SinkBehavior>();
            return new SinkBundle(sink, sinkInputEntity);
        }

        public override void OnStart()
        {
            Ref<ResourceComponent> resource = ConnectedEntity.GetComponent<ResourceComponent>();
            Entity input = resource.Value.GetInputChannel(0);
            ChannelComponent.Open(input);
        }

        public override void OnReceive(Entity inputChannel, Entity child)
        {
            Received++;
            SubModel.Get().DestroyEntity(child);
        }
    }
}
