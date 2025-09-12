using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;

namespace Ers
{
    public static class PathAnimationSystem
    {
        public static void Animate(Entity toAnimate, SimulationTime duration, float fromValue, float toValue, Entity entityContainingPath, int pathIndex)
        {
            SimulationTime currentTime = SubModel.GetSubModel().GetSimulator().GetCurrentTime();
            ErsEngine.ERS_PathAnimationSystem_Animate(toAnimate, currentTime, currentTime+duration, fromValue, toValue, entityContainingPath, pathIndex);
        }

        public static void Update(SimulationTime currentTime)
        {
            ErsEngine.ERS_PathAnimationSystem_Update(currentTime);
        }
    }
}
