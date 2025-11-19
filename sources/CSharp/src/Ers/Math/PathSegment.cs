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
        readonly IntPtr Data;
        public PathSegment(IntPtr data) => Data = data;

        public PathSegmentType Type
        {
            get => (PathSegmentType)ErsEngine.ERS_PathSegment_GetType(Data);
        }

        public Vector3 From
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetFromX(Data),
                ErsEngine.ERS_PathSegment_GetFromY(Data),
                ErsEngine.ERS_PathSegment_GetFromZ(Data));
        }

        public Vector3 To
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetToX(Data), ErsEngine.ERS_PathSegment_GetToY(Data), ErsEngine.ERS_PathSegment_GetToZ(Data));
        }

        public Vector3 Center
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetCenterX(Data),
                ErsEngine.ERS_PathSegment_GetCenterY(Data),
                ErsEngine.ERS_PathSegment_GetCenterZ(Data));
        }

        public float Radius => ErsEngine.ERS_PathSegment_GetRadius(Data);

        public float BeginAngle => ErsEngine.ERS_PathSegment_GetBeginAngle(Data);

        public float EndAngle => ErsEngine.ERS_PathSegment_GetEndAngle(Data);

        public float EndZ => ErsEngine.ERS_PathSegment_GetEndZ(Data);

        public Vector3 P0
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP0X(Data), ErsEngine.ERS_PathSegment_GetP0Y(Data), ErsEngine.ERS_PathSegment_GetP0Z(Data));
        }

        public Vector3 P1
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP1X(Data), ErsEngine.ERS_PathSegment_GetP1Y(Data), ErsEngine.ERS_PathSegment_GetP1Z(Data));
        }

        public Vector3 P2
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP2X(Data), ErsEngine.ERS_PathSegment_GetP2Y(Data), ErsEngine.ERS_PathSegment_GetP2Z(Data));
        }

        public Vector3 P3
        {
            get => new Vector3(
                ErsEngine.ERS_PathSegment_GetP3X(Data), ErsEngine.ERS_PathSegment_GetP3Y(Data), ErsEngine.ERS_PathSegment_GetP3Z(Data));
        }

        public Vector3 GetPointAlongPath(float t)
        {
            unsafe
            {
                float* result = stackalloc float[3];
                ErsEngine.ERS_PathSegment_GetPointAlongPath(Data, t, (IntPtr)result);
                return new Vector3(result[0], result[1], result[2]);
            }
        }

        public Vector3 GetRotationAlongPath(float t)
        {
            unsafe
            {
                float* result = stackalloc float[3];
                ErsEngine.ERS_PathSegment_GetRotationAlongPath(Data, t, (IntPtr)result);
                return new Vector3(result[0], result[1], result[2]);
            }
        }
    }
}
