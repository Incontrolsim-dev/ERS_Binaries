using System.Numerics;
using Ers.Engine;

namespace Ers.Visualization
{
    /// <summary>
    /// Camera used for 3D rendering.
    /// </summary>
    public class Camera3D
    {
        internal readonly IntPtr Data;

        internal Camera3D(IntPtr coreInstance) { Data = coreInstance; }

        /// <summary>
        /// The 3D position of the camera.
        /// </summary>
        public Vector3 Position
        {
            get {
                unsafe
                {
                    return new Vector3(
                        *(float*)ErsEngine.ERS_Camera3D_PositionX(Data), *(float*)ErsEngine.ERS_Camera3D_PositionY(Data),
                        *(float*)ErsEngine.ERS_Camera3D_PositionZ(Data));
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera3D_PositionX(Data) = value.X;
                    *(float*)ErsEngine.ERS_Camera3D_PositionY(Data) = value.Y;
                    *(float*)ErsEngine.ERS_Camera3D_PositionZ(Data) = value.Z;
                }
            }
        }

        /// <summary>
        /// The position the camera is looking at.
        /// </summary>
        public Vector3 LookAt
        {
            get {
                unsafe
                {
                    return new Vector3(
                        *(float*)ErsEngine.ERS_Camera3D_LookAtX(Data), *(float*)ErsEngine.ERS_Camera3D_LookAtY(Data),
                        *(float*)ErsEngine.ERS_Camera3D_LookAtZ(Data));
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera3D_LookAtX(Data) = value.X;
                    *(float*)ErsEngine.ERS_Camera3D_LookAtY(Data) = value.Y;
                    *(float*)ErsEngine.ERS_Camera3D_LookAtZ(Data) = value.Z;
                }
            }
        }

        /// <summary>
        /// The vertical Field Of View (FOV) in turns.
        ///
        /// <para>One turn is a full rotation of 360 degrees.</para>
        /// </summary>
        public float FovInTurns
        {
            get {
                unsafe
                {
                    return *(float*)ErsEngine.ERS_Camera3D_FovInTurns(Data);
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera3D_FovInTurns(Data) = value;
                }
            }
        }

        /// <summary>
        /// The distance of the near plane of the camera.
        /// </summary>
        public float ZNear
        {
            get {
                unsafe
                {
                    return *(float*)ErsEngine.ERS_Camera3D_ZNear(Data);
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera3D_ZNear(Data) = value;
                }
            }
        }

        /// <summary>
        /// The distance of the far plane of the camera.
        /// </summary>
        public float ZFar
        {
            get {
                unsafe
                {
                    return *(float*)ErsEngine.ERS_Camera3D_ZFar(Data);
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera3D_ZFar(Data) = value;
                }
            }
        }

        /// <summary>
        /// Update the transform of the camera.
        /// </summary>
        /// <param name="screenWidth">The current width of the screen in pixels.</param>
        /// <param name="screenHeight">The current height of the screen in pixels.</param>
        public void UpdateTransform(int screenWidth, int screenHeight)
        {
            ErsEngine.ERS_Camera3D_UpdateTransform(Data, screenWidth, screenHeight);
        }

        /// <summary>
        /// Get a pick ray from the camera eye position to a screen position, in world coordinates.
        /// </summary>
        /// <param name="screenWidth">The current width of the screen.</param>
        /// <param name="screenHeight">The current height of the screen.</param>
        /// <param name="screenPos">The screen position used to calculate the ray.</param>
        /// <returns></returns>
        public Ray GetPickRay(int screenWidth, int screenHeight, Vector2 screenPos)
        {
            unsafe
            {
                float posX, posY, posZ;
                float dirX, dirY, dirZ;
                ErsEngine.ERS_Camera3D_GetPickRay(
                    Data, screenWidth, screenHeight, (int)screenPos.X, (int)screenPos.Y, (IntPtr)(&posX), (IntPtr)(&posY), (IntPtr)(&posZ),
                    (IntPtr)(&dirX), (IntPtr)(&dirY), (IntPtr)(&dirZ));
                return new Ray(new Vector3(posX, posY, posZ), new Vector3(dirX, dirY, dirZ));
            }
        }
    }
}
