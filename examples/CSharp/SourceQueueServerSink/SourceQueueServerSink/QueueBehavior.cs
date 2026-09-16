using System;
using System.Numerics;
using Ers;

namespace SourceQueueServerSink
{
    /// <summary>
    /// A bundle of data relevant to a queue simulation object.
    /// </summary>
    /// <param name="queue">The queue's <see cref="QueueBehavior"/>.</param>
    /// <param name="inputEntity">The input channel entity of the queue.</param>
    /// <param name="outputEntity">The output channel entity of the queue.</param>
    public readonly struct QueueBundle(QueueBehavior queue, Entity inputEntity, Entity outputEntity)
    {
        /// <summary>
        /// The queue's <see cref="QueueBehavior"/>.
        /// </summary>
        public readonly QueueBehavior Queue = queue;
        /// <summary>
        /// The input channel entity of the queue.
        /// </summary>
        public readonly Entity InputEntity = inputEntity;
        /// <summary>
        /// The output channel entity of the queue.
        /// </summary>
        public readonly Entity OutputEntity = outputEntity;
    }

    public class QueueBehavior : ScriptBehaviorComponent
    {
        public ulong Capacity = 5;
        private readonly Queue<Entity> queue = new();

        /// <summary>
        /// Get the number of products currently in the queue.
        /// </summary>
        public int NumInQueue { get => queue.Count; }

        /// <summary>
        /// Helper function to easily create a queue simulation object.
        /// </summary>
        /// <param name="name">The name for the queue entity.</param>
        /// <param name="pos">The position for the queue.</param>
        /// <param name="capacity">The maximum capacity for the queue.</param>
        /// <returns></returns>
        public static QueueBundle Create(string name, Vector3 pos, ulong capacity)
        {
            SubModel subModel = SubModel.Get();
            Entity queueEntity = subModel.CreateEntity(name);

            queueEntity.AddComponent<ResourceComponent>();
            Entity queueInputEntity = subModel.CreateEntity(queueEntity, "QueueInput");
            Entity queueOutputEntity = subModel.CreateEntity(queueEntity, "QueueOutput");
            ChannelComponent.AddChannelComponent(queueInputEntity, ChannelType.Input, queueEntity);
            ChannelComponent.AddChannelComponent(queueOutputEntity, ChannelType.Output, queueEntity);

            var transform = queueEntity.AddComponent<TransformComponent>();
            transform.Value.Position = pos;
            transform.Value.Scale = new Vector3(4, 2, 1);

            QueueBehavior queue = queueEntity.AddComponent<QueueBehavior>();
            queue.Capacity = capacity;
            return new QueueBundle(queue, queueInputEntity, queueOutputEntity);
        }

        public override void OnStart()
        {
            Ref<ResourceComponent> resource = ConnectedEntity.GetComponent<ResourceComponent>();
            Entity input = resource.Value.GetInputChannel(0);
            Entity output = resource.Value.GetOutputChannel(0);

            ChannelComponent.Open(input);
            ChannelComponent.Open(output);
        }

        public override void OnReceive(Entity inputChannel, Entity child)
        {
            Logger.Debug("Queue received {0}", child.GetName());

            queue.Enqueue(child);
            TrySend();

            if ((ulong)queue.Count >= Capacity)
            {
                Entity input = ConnectedEntity.GetComponent<ResourceComponent>().Value.GetInputChannel(0);
                ChannelComponent.Close(input);
            }
        }

        public override void OnOutputChannelReady(Entity outputChannel)
        {
            // If the queue is empty, do nothing and return
            if (queue.Count == 0)
                return;

            ChannelComponent.Send(outputChannel, queue.Dequeue());

            Entity input = ConnectedEntity.GetComponent<ResourceComponent>().Value.GetInputChannel(0);
            ChannelComponent.Open(input);
        }

        public void TrySend()
        {
            Entity output = ConnectedEntity.GetComponent<ResourceComponent>().Value.GetOutputChannel(0);
            if (ChannelComponent.IsReady(output) && queue.Count > 0)
            {
                ChannelComponent.Send(output, queue.Dequeue());

                Entity input = ConnectedEntity.GetComponent<ResourceComponent>().Value.GetInputChannel(0);
                ChannelComponent.Open(input);
            }
        }
    }
}
