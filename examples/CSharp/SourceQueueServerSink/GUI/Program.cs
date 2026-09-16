using System.Numerics;
using Ers;
using SourceQueueServerSink;

namespace GUI
{
    internal static class Program
    {
        static ModelContainer? modelContainer;
        static Texture? productTexture;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
            ERS.Initialize();
            Ers.Debugger.Open();
            Logger.SetLogLevel(LogLevel.Trace);

            modelContainer = SourceQueueServerSink.Model.Create();

            Simulator sim = modelContainer.GetSimulatorByIndex(0);
            sim.EnterSubModel();
            productTexture = new Texture("Tote_Top_White.png");
            sim.ExitSubModel();

            Ers.Debugger.Run(modelContainer, Render2D);

            ERS.Uninitialize();
        }

        static void Render2D(Debugger debugger, Simulator simulator)
        {
            RenderContext context = debugger.RenderContext;

            simulator.EnterSubModel();
            SubModel subModel = SubModel.Get();

            // Visualize sources
            var sourceView = subModel.GetView<SourceBehavior, TransformComponent>([]);
            while (sourceView.Next())
            {
                var transform = sourceView.GetComponent<TransformComponent>();
                context.DrawRect2D(transform.Value.Position.XY(), transform.Value.Scale.XY(), 0, Ers.Color.FromFloats(0.01f, 0.39f, 0.43f, 1));

                // Draw the name inside the rectangle, horizontally centered
                string nameText = sourceView.GetEntity().GetName();
                Vector2 nameTextSize = context.CalculateTextSize(nameText, 1);
                Vector2 nameTextPos = transform.Value.Position.XY() + new Vector2(-nameTextSize.X * 0.5f, 0.1f);
                context.DrawText2D(nameText, nameTextPos, 1);
            }
            sourceView.Dispose();

            // Visualize queues
            var queueView = subModel.GetView<QueueBehavior, TransformComponent>([]);
            while (queueView.Next())
            {
                var transform = queueView.GetComponent<TransformComponent>();
                context.DrawRect2D(transform.Value.Position.XY(), transform.Value.Scale.XY(), 0, Ers.Color.FromFloats(0.0f, 0.5f, 0.75f, 1));

                // Draw the name inside the rectangle, horizontally centered
                string nameText = queueView.GetEntity().GetName();
                Vector2 nameTextSize = context.CalculateTextSize(nameText, 1);
                Vector2 nameTextPos = transform.Value.Position.XY() + new Vector2(-nameTextSize.X * 0.5f, 0.1f);
                context.DrawText2D(nameText, nameTextPos, 1);

                // Draw the number of products in the queue and the capacity of the queue as text below the rectangle
                QueueBehavior queue = queueView.GetComponent<QueueBehavior>();
                ulong numInQueue = (ulong)queue.NumInQueue;
                ulong capacity = queueView.GetComponent<QueueBehavior>().Capacity;
                // Draw capacity text in red when the queue is full
                Ers.Color capacityColor = default;
                if (numInQueue >= capacity)
                    capacityColor = Ers.Color.FromFloats(1.0f, 0.18f, 0.18f);
                string capacityText = $"{numInQueue}/{capacity}";
                Vector2 capacityTextSize = context.CalculateTextSize(capacityText, 1);
                Vector2 capacityTextPos = transform.Value.Position.XY() + new Vector2(-capacityTextSize.X * 0.5f, -1);
                context.DrawText2D(capacityText, capacityTextPos, 1, capacityColor);
            }
            queueView.Dispose();

            // Visualize servers
            var serverView = subModel.GetView<ServerBehavior, TransformComponent>([]);
            while (serverView.Next())
            {
                var transform = serverView.GetComponent<TransformComponent>();
                context.DrawRect2D(transform.Value.Position.XY(), transform.Value.Scale.XY(), 0, Ers.Color.FromFloats(0.86f, 0.46f, 0.02f, 1));

                // Draw the name inside the rectangle, horizontally centered
                string nameText = serverView.GetEntity().GetName();
                Vector2 nameTextSize = context.CalculateTextSize(nameText, 1);
                Vector2 nameTextPos = transform.Value.Position.XY() + new Vector2(-nameTextSize.X * 0.5f, 0.1f);
                context.DrawText2D(nameText, nameTextPos, 1);

                // When the server has a product, draw a product icon below the rectangle
                ServerBehavior server = serverView.GetComponent<ServerBehavior>();
                if (server.CurrentlyProcessing != CEntity.InvalidEntity())
                {
                    var product = server.CurrentlyProcessing.GetComponent<Product>();
                    Vector2 productPos = transform.Value.Position.XY() - new Vector2(0, 2);
                    // Draw the product red or green depending on its state
                    Color productColor;
                    if (product.Value.Filled)
                        productColor = Ers.Color.FromFloats(0.0f, 0.89f, 0.47f);
                    else
                        productColor = Ers.Color.FromFloats(1.0f, 0.18f, 0.18f);
                    context.DrawTexture2D(productTexture!, productPos, Vector2.One, 0, productColor);
                }
            }
            serverView.Dispose();

            // Visualize sinks
            var sinkView = subModel.GetView<SinkBehavior, TransformComponent>([]);
            while (sinkView.Next())
            {
                var transform = sinkView.GetComponent<TransformComponent>();
                context.DrawRect2D(transform.Value.Position.XY(), transform.Value.Scale.XY(), 0, Ers.Color.FromFloats(0.01f, 0.39f, 0.43f, 1));
                
                // Draw the name inside the rectangle, horizontally centered
                string nameText = sinkView.GetEntity().GetName();
                Vector2 nameTextSize = context.CalculateTextSize(nameText, 1);
                Vector2 nameTextPos = transform.Value.Position.XY() + new Vector2(-nameTextSize.X * 0.5f, 0.1f);
                context.DrawText2D(nameText, nameTextPos, 1);

                // Draw the number of received products as text below the rectangle
                SinkBehavior sink = sinkView.GetComponent<SinkBehavior>();
                string receivedText = $"{sink.Received}";
                Vector2 receivedTextSize = context.CalculateTextSize(receivedText, 1);
                Vector2 receivedTextPos = transform.Value.Position.XY() - new Vector2(receivedTextSize.X * 0.5f, 1);
                context.DrawText2D(receivedText, receivedTextPos, 1);
            }
            sinkView.Dispose();

            RenderSystem.Render2D(subModel, context);
            simulator.ExitSubModel();
        }
    }
}
