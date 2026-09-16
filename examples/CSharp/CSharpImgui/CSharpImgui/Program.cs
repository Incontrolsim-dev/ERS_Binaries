using System.Numerics;
using Ers;
using ImGuiNET;
using ImPlotNET;

namespace CSharpImgui
{
    internal class CustomDebugger
    {
        public Window Window;

        private ModelContainer modelContainer;
        private RenderContext renderContext;

        bool isRunning = false;
        SelectedType selectedType;
        Simulator selectedSimulator = new();
        Entity selectedEntity = CEntity.InvalidEntity();
        PersistentEvent selectedEvent = new();

        RunControlsWidget runControls = new();
        LogWidget logWidget = new();
        EventTimelineWidget eventTimeline = new();
        ModelHierarchyWidget modelHierarchy = new();
        InspectorWidget inspector = new();
        VisualizationWidget visualization = new();
        ModelStructureWidget modelStructure = new();
        ModelProgressionWidget modelProgression = new();
        LicensingWidget licensing = new();

        bool switchValue = false;
        Vector3 vectorValue = new(1, 2, 3);

        internal CustomDebugger(ModelContainer modelContainer)
        {
            this.Window = new Window("Custom Debugger");
            this.renderContext = new(640, 480);
            this.modelContainer = modelContainer;

            ErsImGui.StyleColorsErsLight();
        }

        private void BeginDockSpace()
        {
            if (Window.BeginRootDockSpace())
            {
                ImGuiViewportPtr viewport = ImGui.GetMainViewport();
                uint rootDockSpaceID = Window.RootDockSpaceID;

                // Optional named IDs so the nodes can be retrieved by name later
                uint topBarDockID = ImGui.GetID("CustomDebugger_TopBarDock");
                uint mainDockID = ImGui.GetID("CustomDebugger_MainDock");
                uint leftSideBarDockID = ImGui.GetID("CustomDebugger_LeftSideBarDock");
                uint centerDockID = ImGui.GetID("CustomDebugger_CenterDock");
                uint rightSideBarDockID = ImGui.GetID("CustomDebugger_RightSideBarDock");
                uint centerMainDockID = ImGui.GetID("CustomDebugger_CenterMainDock");
                uint centerBottomDockID = ImGui.GetID("CustomDebugger_CenterBottomDock");

                // Create a full-width top bar for the Run Controls, and the rest below
                ImGuiStylePtr style = ImGui.GetStyle();
                float topHeightPx = ImGui.GetFrameHeight() + style.ItemSpacing.Y + 4.0f;
                float vpHeight = viewport.Size.Y;
                float topRatio = topHeightPx / (vpHeight > 1.0f ? vpHeight : 800.0f);
                ImGui.DockBuilderSplitNode(rootDockSpaceID, ImGuiDir.Up, topRatio, out topBarDockID, out mainDockID);

                // Lock top bar (no tab bar, no split/resize/undock)
                ImGuiDockNodePtr topNode = ImGui.DockBuilderGetNode(topBarDockID);
                if (topNode.ID > 0)
                {
                    topNode.LocalFlags |= (ImGuiDockNodeFlags)ImGuiDockNodeFlagsPrivate.ImGuiDockNodeFlags_NoTabBar;
                    topNode.LocalFlags |= ImGuiDockNodeFlags.NoDockingSplit;
                    topNode.LocalFlags |= ImGuiDockNodeFlags.NoResize;
                    topNode.LocalFlags |= ImGuiDockNodeFlags.NoDockingOverCentralNode;
                    topNode.LocalFlags |= ImGuiDockNodeFlags.NoUndocking;
                }

                // Below: left sidebar, center, right sidebar
                ImGui.DockBuilderSplitNode(mainDockID, ImGuiDir.Left, 0.10f, out leftSideBarDockID, out centerDockID);
                ImGui.DockBuilderSplitNode(centerDockID, ImGuiDir.Right, 0.10f / 0.90f, out rightSideBarDockID, out centerDockID);

                // Main
                ImGui.DockBuilderSplitNode(centerDockID, ImGuiDir.Up, 0.75f, out centerMainDockID, out centerBottomDockID);

                // Top bar
                ImGui.DockBuilderDockWindow("Run Controls", topBarDockID);
                // Left sidebar
                ImGui.DockBuilderDockWindow("Model Hierarchy", leftSideBarDockID);
                // Right sidebar
                ImGui.DockBuilderDockWindow("Inspector", rightSideBarDockID);
                // Main
                ImGui.DockBuilderDockWindow("Visualization", centerMainDockID);
                ImGui.DockBuilderDockWindow("Model Structure", centerMainDockID);
                ImGui.DockBuilderDockWindow("License Manager", centerMainDockID);
                // Main-Bottom
                ImGui.DockBuilderDockWindow("Log", centerBottomDockID);
                ImGui.DockBuilderDockWindow("Event Timeline", centerBottomDockID);
                ImGui.DockBuilderDockWindow("Model Progression", centerBottomDockID);

                ImGui.DockBuilderFinish(rootDockSpaceID);
            }
        }

        private void EndDockSpace() { Window.EndRootDockSpace(); }

        private void CustomWidget()
        {
            ImGui.SetNextWindowSize(new Vector2(800, 600));
            ImGui.Begin("Test window");

            ImGui.SeparatorText("ImGui");
            ImGui.Text("Hello World!");

            ImGui.SeparatorText("ImPlot");
            int[] bars = [1, 2, 3, 4, 5];
            if (ImPlot.BeginPlot("Plot1"))
            {
                ImPlot.PlotBars("Bar plot", ref bars[0], bars.Length);
                ImPlot.EndPlot();
            }

            bool switchResult = ErsImGui.SwitchButton("Test SwitchButton", ref switchValue);
            if (switchResult)
            {
                Logger.Warning($"Switch: {switchValue}");
            }

            bool xyzResult = ErsImGui.DragVectorXYZ("Test DragVectorXYZ", ref vectorValue);
            if (xyzResult)
            {
                Logger.Info($"Vector: {vectorValue.X}, {vectorValue.Y}, {vectorValue.Z}");
            }

            ImGui.End();
        }

        public void Update()
        {
            Window.BeginFrame();
            BeginDockSpace();
            if (visualization.Is3DMode)
                renderContext.Begin3D();
            else
                renderContext.Begin2D();

            if (ImGui.BeginMainMenuBar())
            {
                if (ImGui.BeginMenu("File"))
                {
                    if (ImGui.MenuItem("Exit"))
                    {
                        Window.WantsClose = true;
                    }
                    ImGui.EndMenu();
                }
                ImGui.EndMainMenuBar();
            }

            runControls.Window(modelContainer, ref isRunning, "Run Controls");
            logWidget.Window("Log");
            if (eventTimeline.Window(modelContainer, selectedEvent, isRunning, "Event Timeline"))
            {
                selectedType = SelectedType.Event;
            }
            modelHierarchy.Window(
                modelContainer, ref selectedSimulator, ref selectedSimulator, ref selectedEntity, ref selectedType, "Model Hierarchy");
            inspector.Window(
                selectedType, modelContainer, selectedSimulator, selectedSimulator, selectedEntity, selectedEvent, "Inspector");
            visualization.Window(renderContext, "Visualization");
            modelStructure.Window(modelContainer, "Model Structure");
            modelProgression.Window(modelContainer, "Model Progression");
            licensing.Window("Licensing Manager");

            CustomWidget();

            if (visualization.Is3DMode)
                renderContext.End3D();
            else
                renderContext.End2D();
            EndDockSpace();
            Window.EndFrame();
        }
    }

    /// <summary>
    /// Infinite event that does nothing so that there are events on the timeline.
    /// </summary>
    internal struct SomeEvent : ILocalEvent<SomeEvent>
    {
        public void OnEvent()
        {
            Logger.Info("Executed some event");
            EventScheduler.ScheduleLocalEvent(0, 10 * SubModel.Get().ModelPrecision, new SomeEvent());
        }
    }

    internal class Program
    {
        private static ModelContainer modelContainer;

        private static readonly int[] bars = [1, 2, 3, 4, 5];
        private static bool switchValue = false;
        private static Vector3 vectorValue = new(1, 2, 3);

        static void Main(string[] args)
        {
            ERS.Initialize();

            LocalEventRegistry<SomeEvent>.Register();

            ModelContainer modelContainer = ModelContainer.Create();
            Simulator sim1 = modelContainer.AddSimulator("Simulator 1", SimulatorType.DiscreteEvent);
            sim1.EnterSubModel();
            EventScheduler.ScheduleLocalEvent(0, 10 * SubModel.Get().ModelPrecision, new SomeEvent());
            sim1.ExitSubModel();

            CustomDebugger debugger = new(modelContainer);
            while (!debugger.Window.WantsClose)
            {
                debugger.Update();
            }

            ERS.Uninitialize();
        }
    }
}

