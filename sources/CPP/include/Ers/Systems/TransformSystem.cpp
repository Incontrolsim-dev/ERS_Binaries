#include "TransformSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    void TransformSystem::UpdateGlobals(Ers::SubModel& subModel)
    {
        Ers::Engine::ERS_TransformSystem_UpdateGlobals(subModel.CorePtr());
    }
} // namespace Ers
