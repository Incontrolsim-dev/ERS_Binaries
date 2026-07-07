using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget that shows the speedup over realtime of a <see cref="ModelContainer"/>.
    /// </summary>
    public class SpeedupWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="SpeedupWidget"/> instance.
        /// </summary>
        public SpeedupWidget() { CorePtr = ErsEngine.ERS_SpeedupWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_SpeedupWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
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
                    ErsEngine.ERS_SpeedupWidget_Window(CorePtr, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_SpeedupWidget_Window(CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        public void Widget() => ErsEngine.ERS_SpeedupWidget_Widget(CorePtr);

        /// <summary>
        /// Update the speedup widget. This is where the widget collects data from the <see cref="ModelContainer"/>.
        ///
        /// <para>
        /// This function should always be called in the main update loop of the program, even when the widget itself is not shown.
        /// Otherwise there will be gaps in the speedup widget's data.
        /// </para>
        /// </summary>
        /// <param name="modelContainer">The model to read the speedup from.</param>
        public void Update(ModelContainer modelContainer) => ErsEngine.ERS_SpeedupWidget_Update(CorePtr, modelContainer.CorePtr);
    }
}
