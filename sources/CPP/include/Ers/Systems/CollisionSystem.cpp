#include "CollisionSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    void CollisionSystem::UpdateBounds(Ers::SubModel& subModel)
    {
        Ers::Engine::ERS_CollisionSystem_UpdateBoundingBoxes(subModel.CorePtr());
    }
} // namespace Ers
