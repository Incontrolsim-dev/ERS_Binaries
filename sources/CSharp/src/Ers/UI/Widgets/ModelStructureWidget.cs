using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// The mode of the heat map.
    /// </summary>
    public enum HeatMapMode : int
    {
        /// <summary>
        /// No heatmap, just show the simulators.
        /// </summary>
        Off = 0,
        /// <summary>
        /// Heat map of the scheduled local-events per simulator.
        /// </summary>
        LocalEvents = 1,
        /// <summary>
        /// Heat map of the incoming sync-events per simulator.
        /// </summary>
        IncomingSyncEvents = 2,
    }

    /// <summary>
    /// The style of the simulator groups rendering.
    /// </summary>
    public enum GroupStyle : int
    {
        /// <summary>
        /// Render as metaballs.
        /// </summary>
        Metaballs = 0,
        /// <summary>
        /// Render as bounding boxes.
        /// </summary>
        BoundingBoxes = 1,
    }

    /// <summary>
    /// Widget to show the structure of a model (simulator dependencies).
    /// </summary>
    public class ModelStructureWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Constructs a new <see cref="ModelStructureWidget"/>.
        /// </summary>
        public ModelStructureWidget() { CorePtr = ErsEngine.ERS_ModelStructureWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_ModelProgressionWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Whether to show the background grid.
        /// </summary>
        public bool ShowGrid
        {
            get => ErsEngine.ERS_ModelStructureWidget_Get_ShowGrid(CorePtr);
            set => ErsEngine.ERS_ModelStructureWidget_Set_ShowGrid(CorePtr, value);
        }

        /// <summary>
        /// The selected heat map mode.
        /// </summary>
        public HeatMapMode SelectedHeatMapMode
        {
            get => (HeatMapMode)ErsEngine.ERS_ModelStructureWidget_Get_SelectedHeatMapMode(CorePtr);
            set => ErsEngine.ERS_ModelStructureWidget_Set_SelectedHeatMapMode(CorePtr, (int)value);
        }

        /// <summary>
        /// Whether to show the simulator groups.
        /// </summary>
        public bool ShowSimulatorGroups
        {
            get => ErsEngine.ERS_ModelStructureWidget_Get_ShowSimulatorGroups(CorePtr);
            set => ErsEngine.ERS_ModelStructureWidget_Set_ShowSimulatorGroups(CorePtr, value);
        }

        /// <summary>
        /// Whether to show the simulator super groups.
        /// </summary>
        public bool ShowSimulatorSuperGroups
        {
            get => ErsEngine.ERS_ModelStructureWidget_Get_ShowSimulatorSuperGroups(CorePtr);

            set => ErsEngine.ERS_ModelStructureWidget_Set_ShowSimulatorSuperGroups(CorePtr, value);
        }

        /// <summary>
        /// The selected group rendering style.
        /// </summary>
        public GroupStyle SelectedGroupStyle
        {
            get => (GroupStyle)ErsEngine.ERS_ModelStructureWidget_Get_SelectedGroupStyle(CorePtr);
            set => ErsEngine.ERS_ModelStructureWidget_Set_SelectedGroupStyle(CorePtr, (int)value);
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the structure of.</param>
        /// <param name="name">The name of the window.</param>
        public void Window(ModelContainer modelContainer, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_ModelStructureWidget_Window(
                        CorePtr, modelContainer.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the structure of.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(ModelContainer modelContainer, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_ModelStructureWidget_Window(CorePtr, modelContainer.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the structure of.</param>
        /// <param name="heatMapMode">The <see cref="HeatMapMode"/> to show.</param>
        public void Widget(ModelContainer modelContainer, HeatMapMode heatMapMode = HeatMapMode.Off)
        {
            ErsEngine.ERS_ModelStructureWidget_Widget(CorePtr, modelContainer.CorePtr, (int)heatMapMode);
        }
    }
}
