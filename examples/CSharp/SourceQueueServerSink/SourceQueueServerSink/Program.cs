using Ers;
using System.Numerics;

namespace SourceQueueServerSink
{
    /// <summary>
    /// A Source, Queue, Server, Sink model that:
    /// <list type="number">
    ///     <item>Spawn an empty tote at the source.</item>
    ///     <item>Queues the tote before the server.</item>
    ///     <item>Fills one tote at a time at the server.</item>
    ///     <item>Exits totes via te sink.</item>
    /// </list>
    /// </summary>
    public class Model
    {
        public static ModelContainer Create()
        {
            // Add component types
            ComponentRegistry<SourceBehavior>.Register();
            ComponentRegistry<QueueBehavior>.Register();
            ComponentRegistry<ServerBehavior>.Register();
            ComponentRegistry<SinkBehavior>.Register();
            ComponentRegistry<Product>.Register();

            // Add event types
            LocalEventRegistry<SourceGenerateProductEvent>.Register();
            LocalEventRegistry<ServerProcessEvent>.Register();

            ModelContainer modelContainer = ModelContainer.Create();
            Simulator simulator = modelContainer.AddSimulator("Sim1", SimulatorType.DiscreteEvent);
            simulator.EnterSubModel();

            // Create the simulation objects
            SourceBundle source1 = SourceBehavior.Create("Source1", new Vector3(0, 0, 0));
            QueueBundle queue1 = QueueBehavior.Create("Queue1", new Vector3(5, 0, 0), 10);
            ServerBundle server1 = ServerBehavior.Create("Server1" , new Vector3(10, 0, 0));
            SinkBundle sink1 = SinkBehavior.Create("Sink1", new Vector3(15, 0, 0));

            // Connect the simulation objects
            ChannelComponent.Connect(source1.OutputEntity, queue1.InputEntity);
            ChannelComponent.Connect(queue1.OutputEntity, server1.InputEntity);
            ChannelComponent.Connect(server1.OutputEntity, sink1.InputEntity);

            simulator.ExitSubModel();
            return modelContainer;
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            ERS.Initialize();
            Logger.SetLogLevel(LogLevel.Trace);

            ModelContainer model = Model.Create();

            // Run for a total of 86400 seconds (1 day)
            ulong endTime = 86400 * model.Precision;
            while (model.CurrentTime < endTime)
            {
                // Run 1 second on each update step
                model.Update(1 * model.Precision);
            }
            ERS.Uninitialize();
        }
    }
}
