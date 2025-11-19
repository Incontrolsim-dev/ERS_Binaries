#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/Entity.h"

namespace Ers
{
    /// @brief System to perform animations along the path of a PathComponent.
    class PathAnimationSystem
    {
      public:
        static void
        Animate(EntityID entity, SimulationTime duration, float fromValue, float toValue, Entity entityContainingPath, int pathIndex);

        /// @brief Animate an entity moving along a straight path.
        /// @param entity The entity to animate.
        /// @param duration The duration of the animation.
        /// @param from The position where the animation starts.
        /// @param to The position where the animation ends.
        static void AnimateStraightPath(EntityID entity, SimulationTime duration, Vector3 from, Vector3 to);

        /// @brief Update the path animation system. This should be called every frame.
        /// @param currentTime The current time of the simulation.
        static void Update(SimulationTime currentTime);
    };
} // namespace Ers
