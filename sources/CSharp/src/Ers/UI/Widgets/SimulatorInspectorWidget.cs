using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to inspect and modify a <see cref="Simulator"/>'s data.
    /// </summary>
    public class SimulatorInspectorWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Create a new <see cref="SimulatorInspectorWidget"/> instance.
        /// </summary>
        public SimulatorInspectorWidget() { CorePtr = ErsEngine.ERS_SimulatorInspectorWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_SimulatorInspectorWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="simulator"></param>
        /// <param name="name"></param>
        public void Window(in Simulator simulator, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_SimulatorInspectorWidget_Window(CorePtr, simulator.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="simulator">The simulator to inspect.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(in Simulator simulator, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_SimulatorInspectorWidget_Window(CorePtr, simulator.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="simulator">The simulator to inspect.</param>
        public void Widget(in Simulator simulator) { ErsEngine.ERS_SimulatorInspectorWidget_Widget(CorePtr, simulator.CorePtr); }
    }
}
