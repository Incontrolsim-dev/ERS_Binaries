using Ers.Engine;
using Ers;

namespace Ers
{
    /// <summary>
    /// Functions related to the collision between different types of objects.
    /// </summary>
    public static class CollisionSystem
    {
        /// <summary>
        /// Update the <see cref="BoundingBoxComponent"/> on all eligable entities in a given submodel.
        /// </summary>
        /// <param name="subModel">The SubModel in which the bounding boxes are updated.</param>
        public static void UpdateBoundingBoxes(in SubModel subModel) => ErsEngine.ERS_CollisionSystem_UpdateBoundingBoxes(subModel.Data);
    }
}
