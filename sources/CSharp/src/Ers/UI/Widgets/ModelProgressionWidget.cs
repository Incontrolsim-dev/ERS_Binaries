using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to show the simulation progression of the simulators in a model.
    /// </summary>
    public class ModelProgressionWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Constructs a new <see cref="ModelProgressionWidget"/>.
        /// </summary>
        public ModelProgressionWidget() { CorePtr = ErsEngine.ERS_ModelProgressionWidget_Create(); }

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
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose progression to show.</param>
        /// <param name="name">The name for the window.</param>
        /// <returns>The selected <see cref="Simulator"/> when the user clicks on a timeline bar, otherwise null.</returns>
        public Simulator? Window(ModelContainer modelContainer, string name)
        {
            IntPtr result = IntPtr.Zero;

            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    result = ErsEngine.ERS_ModelProgressionWidget_Window(
                        CorePtr, modelContainer.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }

            if (result == IntPtr.Zero)
                return null;

            return new Simulator(result);
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose progression to show.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        /// <returns>The selected <see cref="Simulator"/> when the user clicks on a timeline bar, otherwise null.</returns>
        public Simulator? Window(ModelContainer modelContainer, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            IntPtr result = IntPtr.Zero;
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_ModelProgressionWidget_Window(CorePtr, modelContainer.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }

            if (result == IntPtr.Zero)
                return null;

            return new Simulator(result);
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> whose progression to show.</param>
        /// <returns>The selected <see cref="Simulator"/> when the user clicks on a timeline bar, otherwise null.</returns>
        public Simulator? Widget(ModelContainer modelContainer)
        {
            IntPtr result = ErsEngine.ERS_ModelProgressionWidget_Widget(CorePtr, modelContainer.CorePtr);

            if (result == IntPtr.Zero)
                return null;

            return new Simulator(result);
        }
    }
}
