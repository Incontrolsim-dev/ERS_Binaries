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
        /// Update all global values of each entity that has a <see cref="TransformComponent"/> in a given submodel
        /// .
        /// <para>
        /// NOTE: Getting a global variable from a transform component already calculates the global when necessary.
        /// Using UpdateGlobals is redundant, but can be used if you wish to force re-calculate all globals.
        /// </para>
        /// </summary>
        /// <param name="subModel">The submodel in which to update the entities' transform components.</param>
        public static void UpdateGlobals(in SubModel subModel) => ErsEngine.ERS_TransformSystem_UpdateGlobals(subModel.CorePtr);
    }
}
