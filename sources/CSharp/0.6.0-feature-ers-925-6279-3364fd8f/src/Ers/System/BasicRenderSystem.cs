
using Ers.Engine;
using Ers;
using Ers.Visualization;

namespace Ers
{
    /// <summary>
    /// Functions related to the collision between different types of objects.
    /// </summary>
    public static class BasicRenderSystem
    {
        /// <summary>
        /// Render the <see cref="BasicRenderComponent"/> on all eligable entities in a given submodel.
        /// </summary>
        /// <param name="subModel">The SubModel in which the basic renders are rendered.</param>
        public static void Render(in SubModel subModel, in RenderContext renderContext)
        {
            ErsEngine.ERS_BasicRenderSystem_Render(subModel.Data, renderContext.GetCoreInstance());
        }
    }
}
