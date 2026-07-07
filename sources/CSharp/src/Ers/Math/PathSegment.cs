using System;
using System.Numerics;
using Ers.Engine;

namespace Ers
{
    public enum PathSegmentType
    {
        Straight,
        Helical,
        CubicBezier,
    }

    public ref struct PathSegment
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        public PathSegment(IntPtr corePtr) => CorePtr = corePtr;

        public PathSegmentType Type
        {
            get => (PathSegmentType)ErsEngine.ERS_PathSegment_GetType(CorePtr);
        }

        public Vector3 From
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetFromX(CorePtr),
                ErsEngine.ERS_PathSegment_GetFromY(CorePtr),
                ErsEngine.ERS_PathSegment_GetFromZ(CorePtr));
        }

        public Vector3 To
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetToX(CorePtr),
                ErsEngine.ERS_PathSegment_GetToY(CorePtr),
                ErsEngine.ERS_PathSegment_GetToZ(CorePtr));
        }

        public Vector3 Center
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetCenterX(CorePtr),
                ErsEngine.ERS_PathSegment_GetCenterY(CorePtr),
                ErsEngine.ERS_PathSegment_GetCenterZ(CorePtr));
        }

        public float Radius => ErsEngine.ERS_PathSegment_GetRadius(CorePtr);

        public float BeginAngle => ErsEngine.ERS_PathSegment_GetBeginAngle(CorePtr);

        public float EndAngle => ErsEngine.ERS_PathSegment_GetEndAngle(CorePtr);

        public float EndZ => ErsEngine.ERS_PathSegment_GetEndZ(CorePtr);

        public Vector3 P0
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP0X(CorePtr),
                ErsEngine.ERS_PathSegment_GetP0Y(CorePtr),
                ErsEngine.ERS_PathSegment_GetP0Z(CorePtr));
        }

        public Vector3 P1
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP1X(CorePtr),
                ErsEngine.ERS_PathSegment_GetP1Y(CorePtr),
                ErsEngine.ERS_PathSegment_GetP1Z(CorePtr));
        }

        public Vector3 P2
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP2X(CorePtr),
                ErsEngine.ERS_PathSegment_GetP2Y(CorePtr),
                ErsEngine.ERS_PathSegment_GetP2Z(CorePtr));
        }

        public Vector3 P3
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP3X(CorePtr),
                ErsEngine.ERS_PathSegment_GetP3Y(CorePtr),
                ErsEngine.ERS_PathSegment_GetP3Z(CorePtr));
        }

        public Vector3 GetPointAlongPath(float t)
        {
            unsafe
            {
                float* result = stackalloc float[3];
                ErsEngine.ERS_PathSegment_GetPointAlongPath(CorePtr, t, (IntPtr)result);
                return new Vector3(result[0], result[1], result[2]);
            }
        }

        public Vector3 GetRotationAlongPath(float t)
        {
            unsafe
            {
                float* result = stackalloc float[3];
                ErsEngine.ERS_PathSegment_GetRotationAlongPath(CorePtr, t, (IntPtr)result);
                return new Vector3(result[0], result[1], result[2]);
            }
        }
    }
}
