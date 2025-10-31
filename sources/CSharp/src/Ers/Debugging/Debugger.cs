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
    }
}
