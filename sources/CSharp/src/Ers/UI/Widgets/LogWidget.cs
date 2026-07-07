using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget showing the ERS log.
    /// </summary>
    public class LogWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Construct a new <see cref="LogWidget"/>.
        /// </summary>
        public LogWidget() { CorePtr = ErsEngine.ERS_LogWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_LogWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// The minimum log level that is shown.
        /// </summary>
        public LogLevel SelectedLogLevel
        {
            get => (LogLevel)ErsEngine.ERS_LogWidget_Get_SelectedLogLevel(CorePtr);
            set => ErsEngine.ERS_LogWidget_Set_SelectedLogLevel(CorePtr, (int)value);
        }

        /// <summary>
        /// Whether the log automatically scrolls to the latest log entry.
        /// </summary>
        public bool AutoScroll
        {
            get => ErsEngine.ERS_LogWidget_Get_AutoScroll(CorePtr);
            set => ErsEngine.ERS_LogWidget_Set_AutoScroll(CorePtr, value);
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="name">The name for the window.</param>
        public void Window(string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_LogWidget_Window(CorePtr, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_LogWidget_Window(CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        public void Widget() => ErsEngine.ERS_LogWidget_Widget(CorePtr);
    }
}
