using System;
using System.Numerics;
using Ers;

namespace SourceQueueServerSink
{
    internal struct ServerProcessEvent : ILocalEvent<ServerProcessEvent>
    {
        public Entity ServerEntity;

        public void OnEvent()
        {
            ServerBehavior server = ServerEntity.GetComponent<ServerBehavior>();

            Entity output = ServerEntity.GetComponent<ResourceComponent>().Value.GetOutputChannel(0);
            if (ChannelComponent.IsReady(output))
            {
                // Product can be moved, process it and move it
                Entity toSend = server.CurrentlyProcessing;
                server.CurrentlyProcessing = CEntity.InvalidEntity();

                toSend.GetComponent<Product>().Value.Filled = true;
                ChannelComponent.Send(output, toSend);

                Entity input = ServerEntity.GetComponent<ResourceComponent>().Value.GetInputChannel(0);
                ChannelComponent.Open(input);
            }
            else
            {
                // Could not move the product, retry
                server.Process();
            }
        }
    }

    /// <summary>
    /// A bundle of data relevant to a server simulation object.
    /// </summary>
    /// <param name="server">The server's <see cref="ServerBehavior"/>.</param>
    /// <param name="inputEntity">The input channel entity of the server.</param>
    /// <param name="outputEntity">The output channel entity of the server.</param>
    public readonly struct ServerBundle(ServerBehavior server, Entity inputEntity, Entity outputEntity)
    {
        /// <summary>
        /// The server's <see cref="ServerBehavior"/>.
        /// </summary>
        public readonly ServerBehavior Server = server;
        /// <summary>
        /// The input channel entity of the server.
        /// </summary>
        public readonly Entity InputEntity = inputEntity;
        /// <summary>
        /// The output channel entity of the server.
        /// </summary>
        public readonly Entity OutputEntity = outputEntity;
    }

    public class ServerBehavior : ScriptBehaviorComponent
    {
        public double BaseProcessTime = 10.0;
        public Entity CurrentlyProcessing = CEntity.InvalidEntity();

        /// <summary>
        /// Helper function to easily create a server simulation object.
        /// </summary>
        /// <param name="name">The name for the server entity.</param>
        /// <param name="pos">The position for the server.</param>
        /// <returns></returns>
        public static ServerBundle Create(string name, Vector3 pos)
        {
            SubModel subModel = SubModel.Get();
            Entity serverEntity = subModel.CreateEntity(name);

            serverEntity.AddComponent<ResourceComponent>();
            Entity serverInputEntity = subModel.CreateEntity(serverEntity, "ServerInput");
            Entity serverOutputEntity = subModel.CreateEntity(serverEntity, "ServerOutput");
            ChannelComponent.AddChannelComponent(serverInputEntity, ChannelType.Input, serverEntity);
            ChannelComponent.AddChannelComponent(serverOutputEntity, ChannelType.Output, serverEntity);

            var transform = serverEntity.AddComponent<TransformComponent>();
            transform.Value.Position = pos;
            transform.Value.Scale = new Vector3(4, 2, 1);

            ServerBehavior server = serverEntity.AddComponent<ServerBehavior>();
            return new ServerBundle(server, serverInputEntity, serverOutputEntity);
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
            Logger.Debug("Server received {0}", child.GetName());

            CurrentlyProcessing = child;
            Entity input = ConnectedEntity.GetComponent<ResourceComponent>().Value.GetInputChannel(0);
            ChannelComponent.Close(input);
            Process();
        }

        public void Process()
        {
            SubModel subModel = SubModel.Get();

            // Create random process time values
            double processTime = subModel.SampleRandomGenerator() * 2.0 - 1.0 + BaseProcessTime;
            ulong unitProcessTime = (ulong)(processTime * subModel.ModelPrecision);

            Logger.Debug("Server process delay: {0:F2}s", processTime);
            EventScheduler.ScheduleLocalEvent(0, unitProcessTime, new ServerProcessEvent()
            {
                ServerEntity = ConnectedEntity
            });
        }
    }
}
