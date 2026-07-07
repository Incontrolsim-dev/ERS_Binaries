#include "PathAnimationSystem.h"

#include "Ers/Api.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    void PathAnimationSystem::Animate(
        EntityID entity, SimulationTime duration, float fromValue, float toValue, Entity entityContainingPath, int pathIndex)
    {
        SimulationTime currentTime = SubModel::Get().GetSimulator().CurrentTime();
        Ers::Engine::ERS_PathAnimationSystem_Animate(
            entity, currentTime, currentTime + duration, fromValue, toValue, entityContainingPath, pathIndex);
    }

    void PathAnimationSystem::AnimateStraightPath(EntityID entity, SimulationTime duration, Vector3 from, Vector3 to)
    {
        SimulationTime currentTime = SubModel::Get().GetSimulator().CurrentTime();
        Ers::Engine::ERS_PathAnimationSystem_AnimateStraightPath(
            entity, currentTime, currentTime + duration, from.X, from.Y, from.Z, to.X, to.Y, to.Z);
    }

    void PathAnimationSystem::Update(SimulationTime currentTime)
    {
        Ers::Engine::ERS_PathAnimationSystem_Update(currentTime);
    }
} // namespace Ers
