using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// Widget to inspect and edit an Entity and its attached components.
    /// </summary>
    public static class EntityInspectorWidget
    {
        /// <summary>
        /// The full entity inspector widget in a dedicated window.
        /// </summary>
        /// <param name="simulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The entity to inspect.</param>
        /// <param name="name">The name for the window.</param>
        public static void Window(in Simulator simulator, Entity entity, string name)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_EntityInspectorWidget_Window(simulator.CorePtr, entity, utf8Name, null, (int)ImGuiWindowFlags.None);
                }
            }
        }

        /// <summary>
        /// The full entity inspector widget in a dedicated window.
        /// </summary>
        /// <param name="simulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The entity to inspect.</param>
        /// <param name="name">The name for the window.</param>
        /// <param name="open">Whether the window is open.</param>
        /// <param name="flags">Any <see cref="ImGuiWindowFlags"/> for the window.</param>
        public static void Window(
            in Simulator simulator, Entity entity, string name, ref bool open, ImGuiWindowFlags flags = ImGuiWindowFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Name = name.ToUtf8NullTerminated()) fixed(bool* openPtr = &open)
                {
                    ErsEngine.ERS_EntityInspectorWidget_Window(simulator.CorePtr, entity, utf8Name, openPtr, (int)flags);
                }
            }
        }

        /// <summary>
        /// The full entity inspector widget.
        /// </summary>
        /// <param name="simulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The entity to inspect.</param>
        public static void Widget(in Simulator simulator, Entity entity) =>
            ErsEngine.ERS_EntityInspectorWidget_Widget(simulator.CorePtr, entity);

        /// <summary>
        /// A table with editable entity information.
        /// </summary>
        /// <param name="simulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The entity to inspect.</param>
        public static void EntityData(in Simulator simulator, Entity entity) =>
            ErsEngine.ERS_EntityInspectorWidget_EntityData(simulator.CorePtr, entity);

        /// <summary>
        /// Inspect and edit a list of components attached to a given entity.
        /// </summary>
        /// <param name="simulator">The <see cref="Simulator"/> in which the inspected entity lives.</param>
        /// <param name="entity">The entity whose components to inspect.</param>
        public static void ComponentData(in Simulator simulator, Entity entity) =>
            ErsEngine.ERS_EntityInspectorWidget_ComponentData(simulator.CorePtr, entity);
    }
}
