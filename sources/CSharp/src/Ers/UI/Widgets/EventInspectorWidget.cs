using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to inspect the data of a <see cref="SimEvent"/>.
    /// </summary>
    public static class EventInspectorWidget
    {
        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="name">The name for the window.</param>
        /// <param name="persistentEvent">The event to inspect.</param>
        public static void Window(PersistentEvent persistentEvent, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_EventInspectorWidget_Window(persistentEvent.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="persistentEvent">The event to inspect.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public static void Window(
            PersistentEvent persistentEvent, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_EventInspectorWidget_Window(persistentEvent.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="persistentEvent">The event to inspect.</param>
        public static void Widget(PersistentEvent persistentEvent) => ErsEngine.ERS_EventInspectorWidget_Widget(persistentEvent.CorePtr);

        /// <summary>
        /// Show a table containing generic <see cref="SimEvent"/> data that applies to both local- and sync-events.
        /// </summary>
        /// <param name="persistentEvent">The event to inspect.</param>
        public static void EventDetails(PersistentEvent persistentEvent) =>
            ErsEngine.ERS_EventInspectorWidget_EventDetails(persistentEvent.CorePtr);

        /// <summary>
        /// Show a table containing sync-event specific data.
        /// </summary>
        /// <param name="persistentEvent">The event to inspect.</param>
        public static void SyncEventDetails(PersistentEvent persistentEvent) =>
            ErsEngine.ERS_EventInspectorWidget_SyncEventDetails(persistentEvent.CorePtr);

        /// <summary>
        /// Show a table containing local-event specific data.
        /// </summary>
        /// <param name="persistentEvent">The event to inspect.</param>
        public static void LocalEventDetails(PersistentEvent persistentEvent) =>
            ErsEngine.ERS_EventInspectorWidget_LocalEventDetails(persistentEvent.CorePtr);
    }
}
