using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget showing a timeline of events.
    /// </summary>
    public class EventTimelineWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Construct a new <see cref="EventTimelineWidget"/>.
        /// </summary>
        public EventTimelineWidget() { CorePtr = ErsEngine.ERS_EventTimelineWidget_Create(); }

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

        /// <summary>
        /// Whether local-events are shown on the timeline.
        /// </summary>
        public bool ShowLocalEvents
        {
            get => ErsEngine.ERS_EventTimelineWidget_Get_ShowLocalEvents(CorePtr);
            set => ErsEngine.ERS_EventTimelineWidget_Set_ShowLocalEvents(CorePtr, value);
        }

        /// <summary>
        /// Whether sync-events are shown on the timeline.
        /// </summary>
        public bool ShowSyncEvents
        {
            get => ErsEngine.ERS_EventTimelineWidget_Get_ShowSyncEvents(CorePtr);
            set => ErsEngine.ERS_EventTimelineWidget_Set_ShowSyncEvents(CorePtr, value);
        }

        /// <summary>
        /// Whether the timeline automatically scrolls along with the simulation time.
        /// </summary>
        public bool AutoScroll
        {
            get => ErsEngine.ERS_EventTimelineWidget_Get_AutoScroll(CorePtr);
            set => ErsEngine.ERS_EventTimelineWidget_Set_AutoScroll(CorePtr, value);
        }

        /// <summary>
        /// The maximum number of events to show on the timeline.
        /// </summary>
        public nuint MaxEvents
        {
            get => ErsEngine.ERS_EventTimelineWidget_Get_MaxEvents(CorePtr);
            set => ErsEngine.ERS_EventTimelineWidget_Set_MaxEvents(CorePtr, value);
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose event timeline to show.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        /// <param name="name">The name for the window.</param>
        public void Window(ModelContainer modelContainer, bool isRunning, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_EventTimelineWidget_Window(
                        CorePtr, modelContainer.CorePtr, IntPtr.Zero, isRunning, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose event timeline to show.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(
            ModelContainer modelContainer, bool isRunning, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_EventTimelineWidget_Window(
                        CorePtr, modelContainer.CorePtr, IntPtr.Zero, isRunning, utf8Name, openPtr, (int)flags);
                }
            }
        }

        // clang-format off

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose event timeline to show.</param>
        /// <param name="persistentEvent">The currently selected <see cref="PersistentEvent"/>. Will be modified when an event is selected.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        /// <param name="name">The name for the window.</param>
        /// <returns>Returns true when an event is clicked, otherwise false.</returns>
        // clang-format on
        public bool Window(ModelContainer modelContainer, PersistentEvent persistentEvent, bool isRunning, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    return ErsEngine.ERS_EventTimelineWidget_Window(
                        CorePtr, modelContainer.CorePtr, persistentEvent.CorePtr, isRunning, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        // clang-format off

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose event timeline to show.</param>
        /// <param name="persistentEvent">The currently selected <see cref="PersistentEvent"/>. Will be modified when an event is selected.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        /// <returns>Returns true when an event is clicked, otherwise false.</returns>
        // clang-format on
        public bool Window(
            ModelContainer modelContainer,
            PersistentEvent persistentEvent,
            bool isRunning,
            string name,
            ref bool open,
            ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    return ErsEngine.ERS_EventTimelineWidget_Window(
                        CorePtr, modelContainer.CorePtr, persistentEvent.CorePtr, isRunning, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose event timeline to show.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        /// <returns></returns>
        public bool Widget(ModelContainer modelContainer, bool isRunning)
        {
            return ErsEngine.ERS_EventTimelineWidget_Widget(CorePtr, modelContainer.CorePtr, IntPtr.Zero, isRunning);
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose event timeline to show.</param>
        /// <param name="persistentEvent">The currently selected <see cref="PersistentEvent"/>. Will be modified when an event is
        /// selected.</param> <param name="isRunning">Whether the model is currently running.</param> <returns>Returns true when an event is
        /// clicked, otherwise false.</returns>
        public bool Widget(ModelContainer modelContainer, PersistentEvent persistentEvent, bool isRunning)
        {
            return ErsEngine.ERS_EventTimelineWidget_Widget(CorePtr, modelContainer.CorePtr, persistentEvent.CorePtr, isRunning);
        }
    }
}
