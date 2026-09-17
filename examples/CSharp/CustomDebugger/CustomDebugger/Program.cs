using System.Numerics;
using Ers;
using ImGuiNET;
using ImPlotNET;

namespace CustomDebugger
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

        bool windowModelHierarchyOpen = true;
        bool windowModelStructureOpen = false;
        bool windowInspectorOpen = true;
        bool windowEventTimeLineOpen = true;
        bool windowLogOpen = true;
        bool windowVisualizationOpen = true;
        bool windowModelProgressionOpen = false;
        bool windowLicensingOpen = false;
        bool windowCustomOpen = true;

        bool isDarkMode = false;

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

        private void CustomWidget(ref bool open)
        {
            ImGui.SetNextWindowSize(new Vector2(800, 600));
            ImGui.Begin("Test window", ref open);

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
                // File
                if (ImGui.BeginMenu("File"))
                {
                    if (ImGui.MenuItem("Exit"))
                    {
                        Window.WantsClose = true;
                    }
                    ImGui.EndMenu();
                }

                // Window
                if (ImGui.BeginMenu("Window"))
                {
                    // Run Controls is locked/always visible now (hidden from menu)
                    if (ImGui.BeginMenu("Model"))
                    {
                        ImGui.MenuItem("Hierarchy", null, ref windowModelHierarchyOpen);
                        ImGui.MenuItem("Structure", null, ref windowModelStructureOpen);
                        ImGui.EndMenu();
                    }
                    ImGui.MenuItem("Inspector", null, ref windowInspectorOpen);
                    ImGui.MenuItem("Event Timeline", null, ref windowEventTimeLineOpen);
                    ImGui.MenuItem("Model Progression", null, ref windowModelProgressionOpen);
                    ImGui.MenuItem("Log", null, ref windowLogOpen);
                    ImGui.MenuItem("Visualization", null, ref windowVisualizationOpen);
                    ImGui.MenuItem("Custom", null, ref windowCustomOpen);
                    ImGui.EndMenu();
                }

                // View
                if (ImGui.BeginMenu("View"))
                {
                    if (ImGui.Checkbox("Dark mode", ref isDarkMode))
                    {
                        if (isDarkMode)
                        {
                            ErsImGui.StyleColorsErsDark();
                            renderContext.BackgroundColor = Ers.Color.FromFloats(0.2f, 0.2f, 0.2f, 1.0f);
                            renderContext.BackgroundGridColor = Ers.Color.FromFloats(0.8f, 0.8f, 0.8f);
                        }
                        else
                        {
                            ErsImGui.StyleColorsErsLight();
                            renderContext.BackgroundColor = Ers.Color.FromFloats(0.8f, 0.8f, 0.8f, 1.0f);
                            renderContext.BackgroundGridColor = Ers.Color.FromFloats(0.2f, 0.2f, 0.2f);
                        }
                    }
                    ImGui.EndMenu();
                }

                // Help
                if (ImGui.BeginMenu("Help"))
                {
                    ImGui.MenuItem("License Manager", null, ref windowLicensingOpen);
                    ImGui.EndMenu();
                }

                ImGui.EndMainMenuBar();
            }

            runControls.Window(modelContainer, ref isRunning, "Run Controls");

            if (windowLogOpen)
                logWidget.Window("Log", ref windowLogOpen);

            if (windowEventTimeLineOpen)
            {
                if (eventTimeline.Window(modelContainer, selectedEvent, isRunning, "Event Timeline", ref windowEventTimeLineOpen))
                {
                    selectedType = SelectedType.Event;
                }
            }

            if (windowModelHierarchyOpen)
                modelHierarchy.Window(
                    modelContainer, ref selectedSimulator, ref selectedSimulator, ref selectedEntity, ref selectedType, "Model Hierarchy", ref windowModelHierarchyOpen);

            if (windowInspectorOpen)
                inspector.Window(
                    selectedType, modelContainer, selectedSimulator, selectedSimulator, selectedEntity, selectedEvent, "Inspector", ref windowInspectorOpen);

            if (windowVisualizationOpen)
                visualization.Window(renderContext, "Visualization", ref windowVisualizationOpen);

            if (windowModelStructureOpen)
                modelStructure.Window(modelContainer, "Model Structure", ref windowModelStructureOpen);

            if (windowModelProgressionOpen)
                modelProgression.Window(modelContainer, "Model Progression", ref windowModelProgressionOpen);

            if (windowLicensingOpen)
                licensing.Window("Licensing Manager", ref windowLicensingOpen);

            if (windowCustomOpen)
                CustomWidget(ref windowCustomOpen);

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

