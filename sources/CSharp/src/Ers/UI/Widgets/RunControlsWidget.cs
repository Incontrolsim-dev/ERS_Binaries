using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Widget to control the execution of a <see cref="ModelContainer"/>.
    /// Includes play, pause, step, and speed control.
    /// </summary>
    public class RunControlsWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="RunControlsWidget"/> instance.
        /// </summary>
        public RunControlsWidget() { CorePtr = ErsEngine.ERS_RunControlsWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_RunControlsWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The model to control.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        /// <param name="name">The name for the window.</param>
        public void Window(ModelContainer modelContainer, ref bool isRunning, string name)
        {
            unsafe
            {
                fixed(bool* isRunningPtr = &isRunning) fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_RunControlsWidget_Window(CorePtr, modelContainer.CorePtr, isRunningPtr, utf8Name);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The model to control.</param>
        /// <param name="isRunning">Whether the model is currently running.</param>
        public void Widget(ModelContainer modelContainer, ref bool isRunning)
        {
            unsafe
            {
                fixed(bool* isRunningPtr = &isRunning)
                {
                    ErsEngine.ERS_RunControlsWidget_Widget(CorePtr, modelContainer.CorePtr, isRunningPtr);
                }
            }
        }
    }
}
