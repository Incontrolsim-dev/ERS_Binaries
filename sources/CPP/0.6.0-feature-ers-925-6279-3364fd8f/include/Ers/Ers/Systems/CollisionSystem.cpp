#include "CollisionSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    void CollisionSystem::UpdateBounds(Ers::SubModel& subModel)
    {
        ersAPIFunctionPointers.ERS_CollisionSystem_UpdateBoundingBoxes(subModel.Data());
    }
} // namespace Ers
