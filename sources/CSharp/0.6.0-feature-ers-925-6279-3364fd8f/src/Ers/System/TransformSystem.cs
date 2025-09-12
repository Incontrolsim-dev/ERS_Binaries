using Ers.Engine;
using Ers;

namespace Ers
{
    /// <summary>
    /// Functions related to the Transform component.
    /// </summary>
    public static class TransformSystem
    {
        /// <summary>
        /// Update the global Position, Rotation, and Scale on all entities with a <see cref="TransformComponent"/>.
        /// </summary>
        /// <param name="subModel">The SubModel in which the globals are calculated.</param>
        public static void UpdateGlobals(in SubModel subModel) => ErsEngine.ERS_TransformSystem_UpdateGlobals(subModel.Data);
    }
}
