using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// The available camera modes.
    /// </summary>
    public enum Camera3DMode
    {
        /// <summary>
        /// The camera rotates around a position on the ground.
        ///
        /// <para>
        /// By dragging with the left mouse button the camera can be moved.
        /// By dragging with the right mouse button the camera can be rotated.
        /// </para>
        /// </summary>
        Spherical = 0,
        /// <summary>
        /// Walk around from a first person perspective.
        ///
        /// <para>Use WASD to move and Left Shift to move faster.</para>
        /// </summary>
        FirstPerson = 1,
        /// <summary>
        /// Fly around from a first person perspective.
        ///
        /// <para>Use Space to ascend, Ctrl to go descend.</para>
        /// </summary>
        Flying = 2,
    }

    /// <summary>
    /// Movement controller for 3D cameras.
    /// See <see cref="Camera3DMode"/> for descriptions of the available camera modes.
    /// </summary>
    public class Camera3DController
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        /// <summary>
        /// Construct a new Camera3DController, attached to a given camera.
        /// </summary>
        /// <param name="camera">The camera that is to be controlled.</param>
        public Camera3DController(Camera3D camera) { CorePtr = ErsEngine.ERS_Camera3DController_Create(camera.CorePtr); }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~Camera3DController() => ErsEngine.ERS_Camera3DController_Destroy(CorePtr);

        /// <summary>
        /// The intensity of the head (camera height) moving up and down when walking in first person mode.
        /// </summary>
        public float HeadBobbingIntensity
        {
            get => ErsEngine.ERS_Camera3DController_GetHeadBobbingIntensity(CorePtr);
            set => ErsEngine.ERS_Camera3DController_SetHeadBobbingIntensity(CorePtr, value);
        }

        /// <summary>
        /// The default 3D camera behavior.
        /// This function will automatically manage all other functions in the controller.
        /// </summary>
        /// <param name="screenWidth">The width of the screen.</param>
        /// <param name="screenHeight">The height of the screen.</param>
        /// <param name="deltaTime">The elapsed time (in ms) between frames.</param>
        /// <param name="lookAtZ">The Z-coordinate of the ground position the camera is looking at. Generally, this is 0.</param>
        public void ControlCamera(int screenWidth, int screenHeight, float deltaTime, float lookAtZ)
        {
            ErsEngine.ERS_Camera3DController_ControlCamera(CorePtr, screenWidth, screenHeight, deltaTime, lookAtZ);
        }

        /// <summary>
        /// Update the controller.
        /// </summary>
        /// <param name="deltaTime">The elapsed time in ms since the last update.</param>
        public void Update(float deltaTime) { ErsEngine.ERS_Camera3DController_Update(CorePtr, deltaTime); }

        /// <summary>
        /// Switch to a different camera mode. See <see cref="Camera3DMode"/>.
        /// </summary>
        /// <param name="mode">The new camera mode.</param>
        public void SwitchCameraMode(Camera3DMode mode) { ErsEngine.ERS_Camera3DController_SwitchCameraMode(CorePtr, (int)mode); }

        /// <summary>
        /// Get the currently selected camera mode. See <see cref="Camera3DMode"/>.
        /// </summary>
        /// <returns></returns>
        public Camera3DMode GetCameraMode() => (Camera3DMode)ErsEngine.ERS_Camera3DController_GetCameraMode(CorePtr);
    }
}
