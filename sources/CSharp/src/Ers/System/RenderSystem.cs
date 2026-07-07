using Ers;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Functions related to the standard rendering system.
    /// </summary>
    public static class RenderSystem
    {
        /// <summary>
        /// Render the <see cref="RenderComponent"/> on all eligable entities in a given submodel in 2D.
        /// </summary>
        /// <param name="subModel">The submodel in which the entities are rendered.</param>
        /// <param name="renderContext">The render context to use.</param>
        public static void Render2D(in SubModel subModel, in RenderContext renderContext)
        {
            ErsEngine.ERS_RenderSystem_Render2D(subModel.CorePtr, renderContext.CorePtr);
        }

        /// <summary>
        /// Render the <see cref="RenderComponent"/> on all eligable entities in a given submodel in 3D.
        /// </summary>
        /// <param name="subModel">The submodel in which the entities are rendered.</param>
        /// <param name="renderContext">The render context to use.</param>
        public static void Render3D(in SubModel subModel, in RenderContext renderContext)
        {
            ErsEngine.ERS_RenderSystem_Render3D(subModel.CorePtr, renderContext.CorePtr);
        }
    }
}
