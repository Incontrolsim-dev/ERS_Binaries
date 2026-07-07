using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget that wraps around the other inspector widgets to have a single window or widget where any of the <see cref="SelectedType"/>
    /// types can be inspected.
    /// </summary>
    public class InspectorWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="InspectorWidget"/> instance.
        /// </summary>
        public InspectorWidget() { CorePtr = ErsEngine.ERS_InspectorWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_InspectorWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="selectedType">Indicator for the type that is currently selected / shown.</param>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> that may be inspected.</param>
        /// <param name="simulator">The <see cref="Simulator"/> that may be inspected.</param>
        /// <param name="entitySimulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The <see cref="Entity"/> that may be inspected.</param>
        /// <param name="persistentEvent">The event that may be inspected.</param>
        /// <param name="name">The name for the window.</param>
        public void Window(
            SelectedType selectedType,
            in ModelContainer modelContainer,
            in Simulator simulator,
            in Simulator entitySimulator,
            in Entity entity,
            in PersistentEvent persistentEvent,
            string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_InspectorWidget_Window(
                        CorePtr, (byte)selectedType, modelContainer.CorePtr, simulator.CorePtr, entitySimulator.CorePtr, entity,
                        persistentEvent.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="selectedType">Indicator for the type that is currently selected / shown.</param>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> that may be inspected.</param>
        /// <param name="simulator">The <see cref="Simulator"/> that may be inspected.</param>
        /// <param name="entitySimulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The <see cref="Entity"/> that may be inspected.</param>
        /// <param name="persistentEvent">The event that may be inspected.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(
            SelectedType selectedType,
            in ModelContainer modelContainer,
            in Simulator simulator,
            in Simulator entitySimulator,
            in Entity entity,
            in PersistentEvent persistentEvent,
            string name,
            ref bool open,
            ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_InspectorWidget_Window(
                        CorePtr, (byte)selectedType, modelContainer.CorePtr, simulator.CorePtr, entitySimulator.CorePtr, entity,
                        persistentEvent.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="selectedType">Indicator for the type that is currently selected / shown.</param>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> that may be inspected.</param>
        /// <param name="simulator">The <see cref="Simulator"/> that may be inspected.</param>
        /// <param name="entitySimulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The <see cref="Entity"/> that may be inspected.</param>
        /// <param name="persistentEvent">The event that may be inspected.</param>
        public void Widget(
            SelectedType selectedType,
            in ModelContainer modelContainer,
            in Simulator simulator,
            in Simulator entitySimulator,
            in Entity entity,
            in PersistentEvent persistentEvent)
        {
            ErsEngine.ERS_InspectorWidget_Widget(
                CorePtr, (byte)selectedType, modelContainer.CorePtr, simulator.CorePtr, entitySimulator.CorePtr, entity,
                persistentEvent.CorePtr);
        }
    }
}
