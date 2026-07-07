using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget that shows the hierarchy of a <see cref="ModelContainer"/> with all <see cref="Simulator"/>s and entities.
    /// </summary>
    public class ModelHierarchyWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="ModelHierarchyWidget"/> instance.
        /// </summary>
        public ModelHierarchyWidget() { CorePtr = ErsEngine.ERS_ModelHierarchyWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_EventTimeLineWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        // clang-format off
        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the hierarchy of.</param>
        /// <param name="selectedSimulator">The currently selected <see cref="Simulator"/>. Will be overwritten when another one is selected.</param>
        /// <param name="selectedEntitySimulator">The <see cref="Simulator"/> in which the selected entity lives. Will be overwritten when another entity is selected.</param>
        /// <param name="selectedEntity">The currently selected <see cref="Entity"/>. Will be overwritten when another one is selected.</param>
        /// <param name="selectedType">Indicator for the type that is currently selected.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param> <returns>True when something is selected, otherwise false.</returns>
        /// <returns>True when something is selected, otherwise false.</returns>
        // clang-format on
        public bool Window(
            ModelContainer modelContainer,
            ref Simulator selectedSimulator,
            ref Simulator selectedEntitySimulator,
            ref Entity selectedEntity,
            ref SelectedType selectedType,
            string name,
            ref bool open,
            ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                byte selectedTypeInt = (byte)selectedType;
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    bool result = ErsEngine.ERS_ModelHierarchyWidget_Window(
                        CorePtr, modelContainer.CorePtr, ref selectedSimulator.CorePtr, ref selectedEntitySimulator.CorePtr,
                        ref selectedEntity, ref selectedTypeInt, utf8Name, openPtr, (int)flags);
                    selectedType = (SelectedType)selectedTypeInt;
                    return result;
                }
            }
        }

        // clang-format off
        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the hierarchy of.</param>
        /// <param name="selectedSimulator">The currently selected <see cref="Simulator"/>. Will be overwritten when another one is selected.</param>
        /// <param name="selectedEntitySimulator">The <see cref="Simulator"/> in which the selected entity lives. Will be overwritten when another entity is selected.</param>
        /// <param name="selectedEntity">The currently selected <see cref="Entity"/>. Will be overwritten when another one is selected.</param>
        /// <param name="selectedType">Indicator for the type that is currently selected.</param>
        /// <param name="name">The name for the window.</param>
        /// <returns>True when something is selected, otherwise false.</returns>
        // clang-format on
        public bool Window(
            ModelContainer modelContainer,
            ref Simulator selectedSimulator,
            ref Simulator selectedEntitySimulator,
            ref Entity selectedEntity,
            ref SelectedType selectedType,
            string name)
        {
            unsafe
            {
                byte selectedTypeInt = (byte)selectedType;
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    bool result = ErsEngine.ERS_ModelHierarchyWidget_Window(
                        CorePtr, modelContainer.CorePtr, ref selectedSimulator.CorePtr, ref selectedEntitySimulator.CorePtr,
                        ref selectedEntity, ref selectedTypeInt, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                    selectedType = (SelectedType)selectedTypeInt;
                    return result;
                }
            }
        }

        // clang-format off
        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the hierarchy of.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        /// <returns>True when something is selected, otherwise false.</returns>
        // clang-format on
        public bool Window(ModelContainer modelContainer, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            IntPtr selectedSimulatorPtr       = IntPtr.Zero;
            IntPtr selectedEntitySimulatorPtr = IntPtr.Zero;
            Entity selectedEntity             = 0;
            byte selectedTypeInt              = 0;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    bool result = ErsEngine.ERS_ModelHierarchyWidget_Window(
                        CorePtr, modelContainer.CorePtr, ref selectedSimulatorPtr, ref selectedEntitySimulatorPtr, ref selectedEntity,
                        ref selectedTypeInt, utf8Name, openPtr, (int)flags);
                    return result;
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the hierarchy of.</param>
        /// <param name="name">The name for the window.</param>
        /// <returns>True when something is selected, otherwise false.</returns>
        public bool Window(ModelContainer modelContainer, string name)
        {
            IntPtr selectedSimulatorPtr       = IntPtr.Zero;
            IntPtr selectedEntitySimulatorPtr = IntPtr.Zero;
            Entity selectedEntity             = 0;
            byte selectedTypeInt              = 0;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    bool result = ErsEngine.ERS_ModelHierarchyWidget_Window(
                        CorePtr, modelContainer.CorePtr, ref selectedSimulatorPtr, ref selectedEntitySimulatorPtr, ref selectedEntity,
                        ref selectedTypeInt, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                    return result;
                }
            }
        }

        // clang-format off
        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the hierarchy of.</param>
        /// <param name="treeNodeFlags">Any <see cref="ImGuiTreeNodeFlags"/> to apply to all nodes of the hierarchy.</param>
        /// <param name="selectedSimulator">The currently selected <see cref="Simulator"/>. Will be overwritten when another one is selected.</param>
        /// <param name="selectedEntitySimulator">The <see cref="Simulator"/> in which the selected entity lives. Will be overwritten when another entity is selected.</param>
        /// <param name="selectedEntity">The currently selected <see cref="Entity"/>. Will be overwritten when another one is selected.</param>
        /// <param name="selectedType">Indicator for the type that is currently selected.</param>
        /// <returns>True when something is selected, otherwise false.</returns>
        // clang-format on
        public static bool Widget(
            ModelContainer modelContainer,
            ImGuiTreeNodeFlags treeNodeFlags,
            ref Simulator selectedSimulator,
            ref Simulator selectedEntitySimulator,
            ref Entity selectedEntity,
            ref SelectedType selectedType)
        {
            byte selectedTypeInt = (byte)selectedType;
            bool result          = ErsEngine.ERS_ModelHierarchyWidget_Widget(
                modelContainer.CorePtr, (int)treeNodeFlags, ref selectedSimulator.CorePtr, ref selectedEntitySimulator.CorePtr,
                ref selectedEntity, ref selectedTypeInt);
            selectedType = (SelectedType)selectedTypeInt;
            return result;
        }

        // clang-format off
        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to show the hierarchy of.</param>
        /// <param name="treeNodeFlags">Any <see cref="ImGuiTreeNodeFlags"/> to apply to all nodes of the hierarchy.</param>
        // clang-format on
        public static void Widget(ModelContainer modelContainer, ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags.None)
        {
            IntPtr selectedSimulatorPtr       = IntPtr.Zero;
            IntPtr selectedEntitySimulatorPtr = IntPtr.Zero;
            Entity selectedEntity             = 0;
            byte selectedTypeInt              = 0;
            ErsEngine.ERS_ModelHierarchyWidget_Widget(
                modelContainer.CorePtr, (int)treeNodeFlags, ref selectedSimulatorPtr, ref selectedEntitySimulatorPtr, ref selectedEntity,
                ref selectedTypeInt);
        }
    }
}
