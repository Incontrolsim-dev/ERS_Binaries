using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to inspect and modify a <see cref="ModelContainer"/>'s data.
    /// </summary>
    public static class ModelContainerInspectorWidget
    {
        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to inspect.</param>
        /// <param name="name">The name for the window.</param>
        public static void Window(ModelContainer modelContainer, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_ModelContainerInspectorWidget_Window(modelContainer.CorePtr, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }
        }

        /// <summary>
        /// Show the window.
        /// </summary>
        /// <param name="modelContainer">The <see cref="ModelContainer"/> to inspect.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public static void Window(ModelContainer modelContainer, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_ModelContainerInspectorWidget_Window(modelContainer.CorePtr, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// Show the widget.
        /// </summary>
        /// <param name="modelContainer">The model container to inspect.</param>
        public static void Widget(ModelContainer modelContainer) =>
            ErsEngine.ERS_ModelContainerInspectorWidget_Widget(modelContainer.CorePtr);
    }
}
