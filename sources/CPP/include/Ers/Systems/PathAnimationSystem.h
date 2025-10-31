#pragma once

#include "Ers/SubModel/Entity.h"

namespace Ers
{
    /// @brief System to perform animations along the path of a PathComponent.
    class PathAnimationSystem
    {
      public:
        static void
        Animate(EntityID entity, SimulationTime duration, float fromValue, float toValue, Entity entityContainingPath, int pathIndex);

        /// @brief Update the path animation system. This should be called every frame.
        /// @param currentTime The current time of the simulation.
        static void Update(SimulationTime currentTime);
    };
} // namespace Ers
