using System.Numerics;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Camera used for 3D rendering.
    /// </summary>
    public class Camera3D
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal Camera3D(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// The 3D position of the camera.
        /// </summary>
        public Vector3 Position
        {
            get {
                return new Vector3(
                    ErsEngine.ERS_Camera3D_GetPositionX(CorePtr),
                    ErsEngine.ERS_Camera3D_GetPositionY(CorePtr),
                    ErsEngine.ERS_Camera3D_GetPositionZ(CorePtr));
            }
            set {
                ErsEngine.ERS_Camera3D_SetPositionX(CorePtr, value.X);
                ErsEngine.ERS_Camera3D_SetPositionY(CorePtr, value.Y);
                ErsEngine.ERS_Camera3D_SetPositionZ(CorePtr, value.Z);
            }
        }

        /// <summary>
        /// The position the camera is looking at.
        /// </summary>
        public Vector3 LookAt
        {
            get {
                return new Vector3(
                    ErsEngine.ERS_Camera3D_GetLookAtX(CorePtr),
                    ErsEngine.ERS_Camera3D_GetLookAtY(CorePtr),
                    ErsEngine.ERS_Camera3D_GetLookAtZ(CorePtr));
            }
            set {
                ErsEngine.ERS_Camera3D_SetLookAtX(CorePtr, value.X);
                ErsEngine.ERS_Camera3D_SetLookAtY(CorePtr, value.Y);
                ErsEngine.ERS_Camera3D_SetLookAtZ(CorePtr, value.Z);
            }
        }

        /// <summary>
        /// The vertical Field Of View (FOV) in turns.
        ///
        /// <para>One turn is a full rotation of 360 degrees.</para>
        /// </summary>
        public float FovInTurns
        {
            get => ErsEngine.ERS_Camera3D_GetFovInTurns(CorePtr);
            set => ErsEngine.ERS_Camera3D_SetFovInTurns(CorePtr, value);
        }

        /// <summary>
        /// The distance of the near plane of the camera.
        /// </summary>
        public float ZNear
        {
            get => ErsEngine.ERS_Camera3D_GetZNear(CorePtr);
            set => ErsEngine.ERS_Camera3D_SetZNear(CorePtr, value);
        }

        /// <summary>
        /// The distance of the far plane of the camera.
        /// </summary>
        public float ZFar
        {
            get => ErsEngine.ERS_Camera3D_GetZFar(CorePtr);
            set => ErsEngine.ERS_Camera3D_SetZFar(CorePtr, value);
        }

        /// <summary>
        /// Update the transform of the camera.
        /// </summary>
        /// <param name="screenWidth">The current width of the screen in pixels.</param>
        /// <param name="screenHeight">The current height of the screen in pixels.</param>
        public void UpdateTransform(int screenWidth, int screenHeight)
        {
            ErsEngine.ERS_Camera3D_UpdateTransform(CorePtr, screenWidth, screenHeight);
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
                    CorePtr, screenWidth, screenHeight, (int)screenPos.X, (int)screenPos.Y, (IntPtr)(&posX), (IntPtr)(&posY),
                    (IntPtr)(&posZ), (IntPtr)(&dirX), (IntPtr)(&dirY), (IntPtr)(&dirZ));
                return new Ray(new Vector3(posX, posY, posZ), new Vector3(dirX, dirY, dirZ));
            }
        }
    }
}
