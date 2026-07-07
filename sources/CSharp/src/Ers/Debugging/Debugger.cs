using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Debugger tool for ERS models. Opens a debugger window that allows inspecting and controlling model execution.
    /// </summary>
    public class Debugger
    {
        private static readonly string windowTitle = "ERS Debugger";

        /// <summary>
        /// Native pointer to the core debugger instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        /// <summary>
        /// The window used when a window needs to be created ahead of the debugger (see <see cref="Open"/>).
        /// </summary>
        private static Ers.Window? runWindow = null;

        /// <summary>
        /// Constructs a new Debugger instance attached to the given model container.
        /// </summary>
        /// <param name="modelContainer">The model container to debug</param>
        public Debugger(ModelContainer modelContainer) { CorePtr = ErsEngine.ERS_Debugger_Create(modelContainer.CorePtr); }

        /// <summary>
        /// Create a new Debugger instanced attached to the given model container, with previously created <see cref="Ers.Window"/>.
        /// <para>Normally, the <see cref="Ers.Window"/> is created automatically when the debugger is created.</para>
        /// </summary>
        /// <param name="modelContainer">The model container to debug</param>
        /// <param name="window">The <see cref="Ers.Window"/> the debugger should use.</param>
        public Debugger(ModelContainer modelContainer, Ers.Window window)
        {
            CorePtr = ErsEngine.ERS_Debugger_Create_Window(modelContainer.CorePtr, window.CorePtr);
        }

        /// <summary>
        /// The currently selected simulator in the debugger interface.
        /// </summary>
        /// <returns>The selected Simulator instance, or null if none selected</returns>
        public Simulator SelectedSimulator
        {
            get => new Simulator(ErsEngine.ERS_Debugger_GetSelectedSimulator(CorePtr));
        }

        /// <summary>
        /// The currently selected entity in the debugger interface.
        /// </summary>
        /// <returns>The selected Entity instance</returns>
        public Entity SelectedEntity
        {
            get => ErsEngine.ERS_Debugger_GetSelectedEntity(CorePtr);
        }

        /// <summary>
        /// Get the <see cref="Ers.Window"/> used by this Debugger.
        /// </summary>
        public Ers.Window Window
        {
            get => new Window(ErsEngine.ERS_Debugger_GetWindow(CorePtr));
        }

        /// <summary>
        /// The render context used by the debugger for visualization.
        /// </summary>
        /// <returns>The RenderContext instance used for rendering</returns>
        public RenderContext RenderContext
        {
            get => new RenderContext(ErsEngine.ERS_Debugger_GetRenderContext(CorePtr));
        }

        /// <summary>
        /// Whether the debugger is currently running (updating the model).
        /// </summary>
        public bool IsRunning
        {
            get => ErsEngine.ERS_Debugger_Get_IsRunning(CorePtr);
            set => ErsEngine.ERS_Debugger_Set_IsRunning(CorePtr, value);
        }

        /// <summary>
        /// Whether the debugger visualization is in 3D mode.
        /// </summary>
        /// <returns>True if in 3D mode, false if in 2D mode</returns>
        public bool Is3DMode
        {
            get => ErsEngine.ERS_Debugger_Is3DMode(CorePtr);
        }

        /// <summary>
        /// The ID of the top bar dock node.
        /// </summary>
        public uint TopBarDockID => ErsEngine.ERS_Debugger_Get_TopBarDockID(CorePtr);

        /// <summary>
        /// The ID of the main dock node.
        /// </summary>
        public uint MainDockID => ErsEngine.ERS_Debugger_Get_MainDockID(CorePtr);

        /// <summary>
        /// The ID of the left sidebar dock node.
        /// </summary>
        public uint LeftSidebarDockID => ErsEngine.ERS_Debugger_Get_LeftSidebarDockID(CorePtr);

        /// <summary>
        /// The ID of the center dock node.
        /// </summary>
        public uint CenterDockID => ErsEngine.ERS_Debugger_Get_CenterDockID(CorePtr);

        /// <summary>
        /// The ID of the right sidebar dock node.
        /// </summary>
        public uint RightSidebarDockID => ErsEngine.ERS_Debugger_Get_RightSidebarDockID(CorePtr);

        /// <summary>
        /// The ID of the center main dock node.
        /// </summary>
        public uint CenterMainDockID => ErsEngine.ERS_Debugger_Get_CenterMainDockID(CorePtr);

        /// <summary>
        /// The ID of the center bottom dock node.
        /// </summary>
        public uint CenterBottomDockID => ErsEngine.ERS_Debugger_Get_CenterBottomDockID(CorePtr);

        /// <summary>
        /// Begin the update loop of the debugger. Be sure to call this in a loop for the debugger to work.
        /// <para>Any rendering and ImGui code should go in between <see cref="BeginUpdate"/> and <see cref="EndUpdate"/>.</para>
        /// </summary>
        public void BeginUpdate() => ErsEngine.ERS_Debugger_BeginUpdate(CorePtr);

        /// <summary>
        /// End the update loop of the debugger. Be sure to call this in a loop for the debugger to work.
        /// </summary>
        public void EndUpdate() => ErsEngine.ERS_Debugger_EndUpdate(CorePtr);

        /// <summary>
        /// Open the debugger window.
        ///
        /// <para>This should be called before loading textures and 3D models.</para>
        /// </summary>
        public static void Open() { runWindow = new Ers.Window(windowTitle); }

        // clang-format off
        /// <summary>
        /// Open the debugger to inspect, debug, and run the model.
        ///
        /// <para>This function should be used instead of <see cref="ModelManager.Update"/> or <see
        /// cref="ModelContainer.Update(ulong)"/>.</para>
        /// <para>When loading textures or 3D models, use <see cref="Debugger.Open"/> before loading the textures or models.</para>
        /// </summary>
        /// <param name="modelContainer">The model container to debug.</param>
        /// <param name="render2D">Optional 2D render function. Uses the standard render system when no custom function is given. Is called for every <see cref="Simulator"/> on each frame.</param>
        /// <param name="render3D">Optional 3D render function. Uses the standard render system when no custom function is given. Is called for every <see cref="Simulator"/> on each frame.</param>
        /// <param name="renderUI">Optional UI render function. Called each frame, regardless of 2D/3D render mode.</param>
        // clang-format on
        public static void Run(
            ModelContainer modelContainer,
            Action<Debugger, Simulator>? render2D = null,
            Action<Debugger, Simulator>? render3D = null,
            Action<Debugger>? renderUI            = null)
        {
            if (runWindow == null)
                runWindow = new Ers.Window(windowTitle);

            Ers.Debugger debugger = new Ers.Debugger(modelContainer, runWindow);
            Ers.Window window     = debugger.Window;

            while (!window.WantsClose)
            {
                window.BeginFrame();
                debugger.BeginUpdate();

                RenderContext renderContext = debugger.RenderContext;

                if (debugger.Is3DMode)
                {
                    renderContext.Begin3D();
                }
                else
                {
                    renderContext.Begin2D();
                }

                for (int i = 0; i < (int)modelContainer.SimulatorCount; i++)
                {
                    Simulator simulator = modelContainer.GetSimulatorByIndex(i);
                    simulator.EnterSubModel();
                    PathAnimationSystem.Update(simulator.CurrentTime);
                    TransformSystem.UpdateGlobals(SubModel.Get());
                    simulator.ExitSubModel();

                    if (debugger.Is3DMode)
                    {
                        // 3D rendering
                        simulator.EnterSubModel();
                        SubModel subModel3D = SubModel.Get();

                        if (render3D != null)
                            render3D(debugger, simulator);
                        else
                            RenderSystem.Render3D(subModel3D, renderContext);

                        simulator.ExitSubModel();
                    }
                    else
                    {
                        // 2D rendering
                        simulator.EnterSubModel();
                        SubModel subModel2D = SubModel.Get();

                        if (render2D != null)
                            render2D(debugger, simulator);
                        else
                            RenderSystem.Render2D(subModel2D, renderContext);

                        simulator.ExitSubModel();
                    }
                }

                if (debugger.Is3DMode)
                    renderContext.End3D();
                else
                    renderContext.End2D();

                renderUI?.Invoke(debugger);

                debugger.EndUpdate();
                window.EndFrame();
            }
        }
    }
}
