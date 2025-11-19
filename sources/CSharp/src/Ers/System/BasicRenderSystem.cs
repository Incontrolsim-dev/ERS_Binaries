using Ers;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Functions related to the collision between different types of objects.
    /// </summary>
    public static class BasicRenderSystem
    {
        /// <summary>
        /// Render the <see cref="BasicRenderComponent"/> on all eligable entities in a given submodel in 2D.
        /// </summary>
        /// <param name="subModel">The SubModel in which the basic renders are rendered.</param>
        /// <param name="renderContext">The render context to use.</param>
        public static void Render2D(in SubModel subModel, in RenderContext renderContext)
        {
            ErsEngine.ERS_BasicRenderSystem_Render2D(subModel.Data, renderContext.GetCoreInstance());
        }

        /// <summary>
        /// Render the <see cref="BasicRenderComponent"/> on all eligable entities in a given submodel in 3D.
        /// </summary>
        /// <param name="subModel">The SubModel in which the basic renders are rendered.</param>
        /// <param name="renderContext">The render context to use.</param>
        public static void Render3D(in SubModel subModel, in RenderContext renderContext)
        {
            ErsEngine.ERS_BasicRenderSystem_Render3D(subModel.Data, renderContext.GetCoreInstance());
        }
    }
}
