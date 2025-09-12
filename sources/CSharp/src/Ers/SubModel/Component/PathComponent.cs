using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;
using Ers.Math;

namespace Ers
{
    [StructLayout(LayoutKind.Sequential)]
    public struct PathComponent : ICoreComponent
    {
        public static nuint CoreTypeId() => ErsEngine.ERS_PathComponent_TypeId();

        public int GetNumSegments()
        {
            return ErsEngine.ERS_PathComponent_GetNumSegments(CorePointer());
        }

        public PathSegment GetSegment(int index) 
        {
            return new PathSegment(ErsEngine.ERS_PathComponent_GetSegment(CorePointer(), index));
        }

        public void AddStraight(Vector3 from, Vector3 to)
        {
            ErsEngine.ERS_PathComponent_AddStraight(CorePointer(), from.X, from.Y, from.Z, to.X, to.Y, to.Z);
        }
        public void AddHelical(Vector3 center, float radius, float beginAngle, float endAngle, float endZ)
        {
            ErsEngine.ERS_PathComponent_AddHelical(CorePointer(), center.X, center.Y, center.Z, radius, beginAngle, endAngle, endZ);
        }

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed(PathComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}
