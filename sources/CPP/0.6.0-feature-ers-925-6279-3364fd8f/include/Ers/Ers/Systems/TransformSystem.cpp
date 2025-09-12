#include "TransformSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    void TransformSystem::UpdateGlobals(Ers::SubModel& subModel)
    {
        ersAPIFunctionPointers.ERS_TransformSystem_UpdateGlobals(subModel.Data());
    }
} // namespace Ers
