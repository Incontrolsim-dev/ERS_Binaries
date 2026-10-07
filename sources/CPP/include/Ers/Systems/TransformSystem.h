#pragma once

#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    class TransformSystem
    {
      public:
        /// @brief Update all global values of each entity that has a transform component in a given submodel.
        ///
        /// NOTE: Getting a global variable from a transform component already calculates the global when necessary.
        /// Using UpdateGlobals is redundant, but can be used if you wish to force re-calculate all globals.
        /// @param subModel The submodel in which to update the entities' transform components.
        static void UpdateGlobals(Ers::SubModel& subModel);
    };
} // namespace Ers
