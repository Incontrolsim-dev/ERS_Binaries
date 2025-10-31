using System.Numerics;
using Ers.Engine;
using Ers.Visualization;

namespace Ers
{
    /// <summary>
    /// Debugger tool for ERS models. Opens a debugger window that allows inspecting and controlling model execution.
    /// </summary>
    public class Debugger
    {
        /// <summary>
        /// Native pointer to the core debugger instance
        /// </summary>
        private IntPtr coreInstance;

        /// <summary>
        /// Constructs a new Debugger instance attached to the given model container.
        /// </summary>
        /// <param name="modelContainer">The model container to debug and inspect</param>
        public Debugger(ModelContainer modelContainer) { coreInstance = ErsEngine.ERS_Debugger_Create(modelContainer.Data); }

        /// <summary>
        /// Changes the model container being debugged to a different one.
        /// </summary>
        /// <param name="modelContainer">The new model container to debug</param>
        public void SetModelContainer(ModelContainer modelContainer)
        {
            ErsEngine.ERS_Debugger_SetModelContainer(coreInstance, modelContainer.Data);
        }

        /// <summary>
        /// Gets the currently selected simulator in the debugger interface.
        /// </summary>
        /// <returns>The selected Simulator instance, or null if none selected</returns>
        public Simulator GetSelectedSimulator() { return new Simulator(ErsEngine.ERS_Debugger_GetSelectedSimulator(coreInstance)); }

        /// <summary>
        /// Gets the currently selected entity in the debugger interface.
        /// </summary>
        /// <returns>The selected Entity instance</returns>
        public Entity GetSelectedEntity() { return ErsEngine.ERS_Debugger_GetSelectedEntity(coreInstance); }

        /// <summary>
        /// Gets the render context used by the debugger for visualization.
        /// </summary>
        /// <returns>The RenderContext instance used for rendering</returns>
        public RenderContext GetRenderContext() { return new RenderContext(ErsEngine.ERS_Debugger_GetRenderContext(coreInstance)); }

        /// <summary>
        /// Checks if the debugger is requesting a model restart.
        /// </summary>
        /// <returns>True if restart requested, false otherwise</returns>
        public bool WantsRestart() { return ErsEngine.ERS_Debugger_WantsRestart(coreInstance); }

        /// <summary>
        /// Checks if the debugger visualization is in 3D mode.
        /// </summary>
        /// <returns>True if in 3D mode, false if in 2D mode</returns>
        public bool Is3DMode() { return ErsEngine.ERS_Debugger_Is3DMode(coreInstance); }

        /// <summary>
        /// Whether the background grid of the 2D/3D view should be shown.
        /// </summary>
        /// <returns></returns>
        public bool ShowBackgroundGrid() => ErsEngine.ERS_Debugger_ShowBackgroundGrid(coreInstance);

        /// <summary>
        /// Updates the debugger state and UI. Must be called regularly in a loop for the debugger to function.
        /// This handles input processing, UI updates, and visualization updates.
        /// </summary>
        public void Update() { ErsEngine.ERS_Debugger_Update(coreInstance); }

        /// <summary>
        /// Open the debugger to inspect, debug, and run the model.
        ///
        /// <para>This function should be used instead of <see cref="ModelManager.Update"/> or <see
        /// cref="ModelContainer.Update(ulong)"/>.</para>
        /// </summary>
        /// <param name="modelContainer">The model container to debug.</param>
        /// <param name="render2D">Optional 2D render function. Uses basic render system when no custom function is given.</param>
        /// <param name="render3D">Optional 3D render function. Uses basic render system when no custom function is given.</param>
        public static void Run(
            ModelContainer modelContainer, Action<RenderContext>? render2D = null, Action<RenderContext>? render3D = null)
        {
            Ers.Platform platform = new Ers.Platform();
            Ers.Debugger debugger = new Ers.Debugger(modelContainer);

            Simulator simulator = modelContainer.GetSimulatorByIndex(0);

            while (!platform.WantsClose())
            {
                platform.BeginFrame();

                simulator.EnterSubModel();
                PathAnimationSystem.Update(simulator.GetCurrentTime());
                TransformSystem.UpdateGlobals(SubModel.GetSubModel());
                simulator.ExitSubModel();

                RenderContext renderContext = debugger.GetRenderContext();
                if (debugger.Is3DMode())
                {
                    // 3D rendering
                    simulator.EnterSubModel();
                    SubModel subModel3D = SubModel.GetSubModel();
                    renderContext.Begin3D();

                    if (debugger.ShowBackgroundGrid())
                    {
                        Vector3 gridColor = new Vector3(0.8f, 0.8f, 0.8f);
                        renderContext.DrawInfiniteGrid3D(gridColor);
                    }
                    if (render3D != null)
                        render3D(renderContext);
                    else
                        BasicRenderSystem.Render3D(subModel3D, renderContext);

                    renderContext.End3D();
                    simulator.ExitSubModel();
                }
                else
                {
                    // 2D rendering
                    simulator.EnterSubModel();
                    SubModel subModel2D = SubModel.GetSubModel();
                    renderContext.Begin2D();

                    if (debugger.ShowBackgroundGrid())
                    {
                        Vector3 gridColor = new Vector3(0.8f, 0.8f, 0.8f);
                        renderContext.DrawInfiniteGrid2D(gridColor, 1.0f, 0.1f, 64.0f);
                    }
                    if (render2D != null)
                        render2D(renderContext);
                    else
                        BasicRenderSystem.Render2D(subModel2D, renderContext);

                    renderContext.End2D();
                    simulator.ExitSubModel();
                }

                debugger.Update();
                platform.EndFrame();
            }
        }
    }
}
