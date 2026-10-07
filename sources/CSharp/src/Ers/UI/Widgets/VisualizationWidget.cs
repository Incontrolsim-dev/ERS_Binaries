using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to show the visualization of the model.
    /// </summary>
    public class VisualizationWidget : IDisposable
    {
        /// <summary>
        /// Arguments used for entity selection.
        /// </summary>
        public ref struct EntitySelectionArgs
        {
            /// <summary>
            /// The <see cref="ModelContainer"/> that is visualized, in which all entities live.
            /// </summary>
            public ModelContainer Model;
            /// <summary>
            /// The currently selected type.
            /// </summary>
            public ref SelectedType Type;
            /// <summary>
            /// The currently selected entity.
            /// </summary>
            public ref Entity SelectedEntity;
            /// <summary>
            /// The <see cref="Simulator"/> in which the currently selected entity lives.
            /// </summary>
            public ref Simulator SelectedEntitySimulator;

            /// <summary>
            /// Construct a new <see cref="EntitySelectionArgs"/>.
            /// <param name="modelContainer">The <see cref="Model"/> that is visualized, in which all entities live.</param>
            /// <param name="selectedType">he currently selected type.</param>
            /// <param name="selectedEntity">he currently selected entity.</param>
            /// <param name="selectedEntitySimulator">The <see cref="Simulator"/> in which the currently selected entity lives.</param>
            /// </summary>
            public EntitySelectionArgs(
                ModelContainer modelContainer,
                ref SelectedType selectedType,
                ref Entity selectedEntity,
                ref Simulator selectedEntitySimulator)
            {
                Model                   = modelContainer;
                Type                    = ref selectedType;
                SelectedEntity          = ref selectedEntity;
                SelectedEntitySimulator = ref selectedEntitySimulator;
            }
        }

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="VisualizationWidget"/> instance.
        /// </summary>
        public VisualizationWidget() { CorePtr = ErsEngine.ERS_VisualizationWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_VisualizationWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Whether the visualization is in 3D mode.
        /// </summary>
        public bool Is3DMode
        {
            get => ErsEngine.ERS_VisualizationWidget_Get_Is3DMode(CorePtr);
            set => ErsEngine.ERS_VisualizationWidget_Set_Is3DMode(CorePtr, value);
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="renderContext">The render context to show the visualization of.</param>
        /// <param name="name">The name for the window.</param>
        public void Window(RenderContext renderContext, string name)
        {
            IntPtr modelContainerPtr          = IntPtr.Zero;
            IntPtr selectedTypePtr            = IntPtr.Zero;
            IntPtr selectedEntityPtr          = IntPtr.Zero;
            IntPtr selectedEntitySimulatorPtr = IntPtr.Zero;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_VisualizationWidget_Window(
                        CorePtr, renderContext.CorePtr, ref modelContainerPtr, ref selectedTypePtr, ref selectedEntityPtr,
                        ref selectedEntitySimulatorPtr, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="renderContext">The render context to show the visualization of.</param>
        /// <param name="entitySelectionArgs">Arguments used to handle entity selection.</param>
        /// <param name="name">The name for the window.</param>
        public void Window(RenderContext renderContext, EntitySelectionArgs entitySelectionArgs, string name)
        {
            IntPtr modelContainerPtr          = entitySelectionArgs.Model.CorePtr;
            IntPtr selectedEntitySimulatorPtr = entitySelectionArgs.SelectedEntitySimulator.CorePtr;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    IntPtr selectedTypePtr   = (IntPtr)(SelectedType*)&entitySelectionArgs.Type;
                    IntPtr selectedEntityPtr = (IntPtr)(Entity*)&entitySelectionArgs.SelectedEntity;
                    ErsEngine.ERS_VisualizationWidget_Window(
                        CorePtr, renderContext.CorePtr, ref modelContainerPtr, ref selectedTypePtr, ref selectedEntityPtr,
                        ref selectedEntitySimulatorPtr, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }

            if (selectedEntitySimulatorPtr != entitySelectionArgs.SelectedEntitySimulator.CorePtr)
            {
                entitySelectionArgs.SelectedEntitySimulator = new Simulator(selectedEntitySimulatorPtr);
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        /// <param name="entitySelectionArgs">Arguments used to handle entity selection.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(
            RenderContext renderContext,
            EntitySelectionArgs entitySelectionArgs,
            string name,
            ref bool open,
            ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            IntPtr modelContainerPtr          = entitySelectionArgs.Model.CorePtr;
            IntPtr selectedEntitySimulatorPtr = entitySelectionArgs.SelectedEntitySimulator.CorePtr;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    IntPtr selectedTypePtr   = (IntPtr)(SelectedType*)&entitySelectionArgs.Type;
                    IntPtr selectedEntityPtr = (IntPtr)(Entity*)&entitySelectionArgs.SelectedEntity;
                    ErsEngine.ERS_VisualizationWidget_Window(
                        CorePtr, renderContext.CorePtr, ref modelContainerPtr, ref selectedTypePtr, ref selectedEntityPtr,
                        ref selectedEntitySimulatorPtr, utf8Name, openPtr, (int)flags);
                }
            }

            if (selectedEntitySimulatorPtr != entitySelectionArgs.SelectedEntitySimulator.CorePtr)
            {
                entitySelectionArgs.SelectedEntitySimulator = new Simulator(selectedEntitySimulatorPtr);
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(RenderContext renderContext, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            IntPtr modelContainerPtr          = IntPtr.Zero;
            IntPtr selectedTypePtr            = IntPtr.Zero;
            IntPtr selectedEntityPtr          = IntPtr.Zero;
            IntPtr selectedEntitySimulatorPtr = IntPtr.Zero;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_VisualizationWidget_Window(
                        CorePtr, renderContext.CorePtr, ref modelContainerPtr, ref selectedTypePtr, ref selectedEntityPtr,
                        ref selectedEntitySimulatorPtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// End the widget's default window. Call BeginWindow() and Widget() before this.
        /// Additional ImGui code can be added in between the extend the default window's functionality.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        /// <param name="name">The name for the window.</param>
        public void BeginWindow(RenderContext renderContext, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_VisualizationWidget_BeginWindow(
                        CorePtr, renderContext.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        /// <summary>
        /// End the widget's default window. Call BeginWindow() and Widget() before this.
        /// Additional ImGui code can be added in between the extend the default window's functionality.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void BeginWindow(RenderContext renderContext, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_VisualizationWidget_BeginWindow(CorePtr, renderContext.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// End the widget's default window. Call BeginWindow() and Widget() before this.
        /// Additional ImGui code can be added in between the extend the default window's functionality.
        /// </summary>
        public void EndWindow() => ErsEngine.ERS_VisualizationWidget_EndWindow(CorePtr);

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        public void Widget(RenderContext renderContext)
        {
            IntPtr modelContainerPtr          = IntPtr.Zero;
            IntPtr selectedTypePtr            = IntPtr.Zero;
            IntPtr selectedEntityPtr          = IntPtr.Zero;
            IntPtr selectedEntitySimulatorPtr = IntPtr.Zero;
            ErsEngine.ERS_VisualizationWidget_Widget(
                CorePtr, renderContext.CorePtr, ref modelContainerPtr, ref selectedTypePtr, ref selectedEntityPtr,
                ref selectedEntitySimulatorPtr);
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        /// <param name="entitySelectionArgs">Arguments used to handle entity selection.</param>
        public void Widget(RenderContext renderContext, EntitySelectionArgs entitySelectionArgs)
        {
            IntPtr modelContainerPtr          = entitySelectionArgs.Model.CorePtr;
            IntPtr selectedEntitySimulatorPtr = entitySelectionArgs.SelectedEntitySimulator.CorePtr;
            unsafe
            {
                IntPtr selectedTypePtr   = (IntPtr)(SelectedType*)&entitySelectionArgs.Type;
                IntPtr selectedEntityPtr = (IntPtr)(Entity*)&entitySelectionArgs.SelectedEntity;
                ErsEngine.ERS_VisualizationWidget_Widget(
                    CorePtr, renderContext.CorePtr, ref modelContainerPtr, ref selectedTypePtr, ref selectedEntityPtr,
                    ref selectedEntitySimulatorPtr);
            }

            if (selectedEntitySimulatorPtr != entitySelectionArgs.SelectedEntitySimulator.CorePtr)
            {
                entitySelectionArgs.SelectedEntitySimulator = new Simulator(selectedEntitySimulatorPtr);
            }
        }
    }
}
