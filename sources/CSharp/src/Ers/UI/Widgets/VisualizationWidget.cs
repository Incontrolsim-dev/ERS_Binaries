using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to show the visualization of the model.
    /// </summary>
    public class VisualizationWidget : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="VisualizationWidget"/> instance.
        /// </summary>
        public VisualizationWidget() { CorePtr = ErsEngine.ERS_VisualizationWidget_Create(); }

        /// <summary>
        /// Destroy the widget instance.
        /// </summary>
        public void Dispose()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_VisualizationWidget_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        /// <summary>
        /// Whether the visualization is in 3D mode.
        /// </summary>
        public bool Is3DMode
        {
            get => ErsEngine.ERS_VisualizationWidget_Get_Is3DMode(CorePtr);
            set => ErsEngine.ERS_VisualizationWidget_Set_Is3DMode(CorePtr, value);
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="renderContext">The render context to show the visualization of.</param>
        /// <param name="name">The name for the window.</param>
        public void Window(RenderContext renderContext, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_VisualizationWidget_Window(CorePtr, renderContext.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.MenuBar);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public void Window(RenderContext renderContext, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.MenuBar)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_VisualizationWidget_Window(CorePtr, renderContext.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="renderContext">The <see cref="RenderContext"/> to show the visualization of.</param>
        public void Widget(RenderContext renderContext) { ErsEngine.ERS_VisualizationWidget_Widget(CorePtr, renderContext.CorePtr); }
    }
}
