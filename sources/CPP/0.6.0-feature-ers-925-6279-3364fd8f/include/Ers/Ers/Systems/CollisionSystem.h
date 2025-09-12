#pragma once

#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    class CollisionSystem
    {
      public:
        static void UpdateBounds(Ers::SubModel& subModel);
    };
} // namespace Ers
