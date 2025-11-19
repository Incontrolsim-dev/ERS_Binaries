using System;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Component to define paths along which entities can be rendered and animated.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct PathComponent : ICoreComponent
    {
        public static nuint CoreTypeId() => ErsEngine.ERS_PathComponent_TypeId();

        public int GetNumSegments() => ErsEngine.ERS_PathComponent_GetNumSegments(CorePointer());

        public PathSegment GetSegment(int index) => new PathSegment(ErsEngine.ERS_PathComponent_GetSegment(CorePointer(), index));

        public void AddStraight(Vector3 from, Vector3 to)
        {
            ErsEngine.ERS_PathComponent_AddStraight(CorePointer(), from.X, from.Y, from.Z, to.X, to.Y, to.Z);
        }
        public void AddHelical(Vector3 center, float radius, float beginAngle, float endAngle, float endZ)
        {
            ErsEngine.ERS_PathComponent_AddHelical(CorePointer(), center.X, center.Y, center.Z, radius, beginAngle, endAngle, endZ);
        }

        public void AddCubicBezier(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3)
        {
            ErsEngine.ERS_PathComponent_AddCubicBezier(
                CorePointer(), p0.X, p0.Y, p0.Z, p1.X, p1.Y, p1.Z, p2.X, p2.Y, p2.Z, p3.X, p3.Y, p3.Z);
        }

        public void AddCubicBezierFromDirections(Vector3 start, Vector3 startDir, Vector3 end, Vector3 endDir, float curvature)
        {
            ErsEngine.ERS_PathComponent_AddCubicBezierFromDirections(
                CorePointer(), start.X, start.Y, start.Z, startDir.X, startDir.Y, startDir.Z, end.X, end.Y, end.Z, endDir.X, endDir.Y,
                endDir.Z, curvature);
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
