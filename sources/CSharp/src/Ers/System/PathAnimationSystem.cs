using System;
using System.Numerics;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// System for animating entities along paths.
    /// </summary>
    public static class PathAnimationSystem
    {
        public static void Animate(
            Entity toAnimate, SimulationTime duration, float fromValue, float toValue, Entity entityContainingPath, int pathIndex)
        {
            SimulationTime currentTime = SubModel.GetSubModel().GetSimulator().GetCurrentTime();
            ErsEngine.ERS_PathAnimationSystem_Animate(
                toAnimate, currentTime, currentTime + duration, fromValue, toValue, entityContainingPath, pathIndex);
        }

        /// <summary>
        /// Animate an entity moving along a straight path.
        /// </summary>
        /// <param name="toAnimate">The entity to animate.</param>
        /// <param name="duration">The duration of the animation.</param>
        /// <param name="from">The position from which the animation starts.</param>
        /// <param name="to">The position where the animation ends.</param>
        public static void AnimateStraightPath(Entity toAnimate, SimulationTime duration, Vector3 from, Vector3 to)
        {
            SimulationTime currentTime = SubModel.GetSubModel().GetSimulator().GetCurrentTime();
            ErsEngine.ERS_PathAnimationSystem_AnimateStraightPath(
                toAnimate, currentTime, currentTime + duration, from.X, from.Y, from.Z, to.X, to.Y, to.Z);
        }

        /// <summary>
        /// Update the path animation system.
        ///
        /// <para>This function should be called once per frame.</para>
        /// <para><see cref="Ers.Debugger.Run(ModelContainer, Action{RenderContext}?, Action{RenderContext}?)"/> calls this
        /// automatically.</para>
        /// </summary>
        /// <param name="currentTime"></param>
        public static void Update(SimulationTime currentTime) { ErsEngine.ERS_PathAnimationSystem_Update(currentTime); }
    }
}
