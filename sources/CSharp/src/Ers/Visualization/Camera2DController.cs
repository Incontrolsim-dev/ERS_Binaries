using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Movement controller for 2D cameras using dragging and zooming.
    /// </summary>
    public class Camera2DController
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        /// <summary>
        /// Construct a new CameraController2D, attached to a given camera.
        /// </summary>
        /// <param name="camera">The camera to attach to.</param>
        public Camera2DController(Camera2D camera) { CorePtr = ErsEngine.ERS_Camera2DController_Create(camera.CorePtr); }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~Camera2DController() => ErsEngine.ERS_Camera2DController_Destroy(CorePtr);

        /// <summary>
        /// The default dragging and zooming behaviour.
        /// This function will automatically manage all other functions in the controller.
        /// </summary>
        /// <param name="screenWidth">The width of the screen.</param>
        /// <param name="screenHeight">The height of the screen.</param>
        public void ControlCamera(int screenWidth, int screenHeight)
        {
            ErsEngine.ERS_Camera2DController_ControlCamera(CorePtr, screenWidth, screenHeight);
        }

        /// <summary>
        /// Set the camera controller's known camera width and height.
        /// </summary>
        /// <param name="width">The width of the camera.</param>
        /// <param name="height">The height of the camera.</param>
        public void SetScreenSize(int width, int height) => ErsEngine.ERS_Camera2DController_SetScreenSize(CorePtr, width, height);

        /// <summary>
        /// Update the controller.
        /// </summary>
        /// <param name="mouseX">The mouse X-position.</param>
        /// <param name="mouseY">The mouse Y-position.</param>
        public void Update(float mouseX, float mouseY) => ErsEngine.ERS_Camera2DController_Update(CorePtr, mouseX, mouseY);

        /// <summary>
        /// Notify the controller that the user starts dragging the camera.
        /// </summary>
        /// <param name="mouseX">The mouse X-position at the start of dragging.</param>
        /// <param name="mouseY">The mouse Y-position at the start of dragging.</param>
        public void StartDragging(float mouseX, float mouseY) { ErsEngine.ERS_Camera2DController_StartDragging(CorePtr, mouseX, mouseY); }

        /// <summary>
        /// Notify the controller that the user stops dragging the camera.
        /// </summary>
        public void StopDragging() => ErsEngine.ERS_Camera2DController_StopDragging(CorePtr);

        /// <summary>
        /// Notify the controller that the user is zooming in or out.
        ///
        /// <para>Calculates a zoom factor by doing base to the power of power.</para>
        /// </summary>
        /// <param name="base">The base zoom factor.</param>
        /// <param name="power">The power of the zoom. Positive values zoom in, negative values zoom out. Larger values increase
        /// speed.</param>
        public void Zoom(float @base, float power) => ErsEngine.ERS_Camera2DController_Zoom(CorePtr, @base, power);
    }
}
