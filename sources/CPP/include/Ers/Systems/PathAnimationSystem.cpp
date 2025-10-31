#include "PathAnimationSystem.h"

#include "Ers/Api.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    void PathAnimationSystem::Animate(
        EntityID entity, SimulationTime duration, float fromValue, float toValue, Entity entityContainingPath, int pathIndex)
    {
        SimulationTime currentTime = GetSubModel().GetSimulator().CurrentTime();
        ersAPIFunctionPointers.ERS_PathAnimationSystem_Animate(
            entity, currentTime, duration, fromValue, toValue, entityContainingPath, pathIndex);
    }

    void PathAnimationSystem::Update(SimulationTime currentTime)
    {
        ersAPIFunctionPointers.ERS_PathAnimationSystem_Update(currentTime);
    }
} // namespace Ers
