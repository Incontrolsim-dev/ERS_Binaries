using Ers.Engine;

namespace Ers.Visualization
{
    /// <summary>
    /// Movement controller for 2D cameras using dragging and zooming.
    /// </summary>
    public class Camera2DController
    {
        private readonly IntPtr coreInstance;

        /// <summary>
        /// Construct a new CameraController2D, attached to a given camera.
        /// </summary>
        /// <param name="camera">The camera to attach to.</param>
        public Camera2DController(Camera2D camera) { coreInstance = ErsEngine.ERS_Camera2DController_Create(camera.Data); }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~Camera2DController() => ErsEngine.ERS_Camera2DController_Destroy(coreInstance);

        /// <summary>
        /// The default dragging and zooming behaviour.
        /// This function will automatically manage all other functions in the controller.
        /// </summary>
        /// <param name="screenWidth">The width of the screen.</param>
        /// <param name="screenHeight">The height of the screen.</param>
        public void ControlCamera(int screenWidth, int screenHeight)
        {
            ErsEngine.ERS_Camera2DController_ControlCamera(coreInstance, screenWidth, screenHeight);
        }

        /// <summary>
        /// Set the camera controller's known camera width and height.
        /// </summary>
        /// <param name="width">The width of the camera.</param>
        /// <param name="height">The height of the camera.</param>
        public void SetScreenSize(int width, int height) => ErsEngine.ERS_Camera2DController_SetScreenSize(coreInstance, width, height);

        /// <summary>
        /// Update the controller.
        /// </summary>
        /// <param name="mouseX">The mouse X-position.</param>
        /// <param name="mouseY">The mouse Y-position.</param>
        public void Update(float mouseX, float mouseY) => ErsEngine.ERS_Camera2DController_Update(coreInstance, mouseX, mouseY);

        /// <summary>
        /// Notify the controller that the user starts dragging the camera.
        /// </summary>
        /// <param name="mouseX">The mouse X-position at the start of dragging.</param>
        /// <param name="mouseY">The mouse Y-position at the start of dragging.</param>
        public void StartDragging(float mouseX, float mouseY)
        {
            ErsEngine.ERS_Camera2DController_StartDragging(coreInstance, mouseX, mouseY);
        }

        /// <summary>
        /// Notify the controller that the user stops dragging the camera.
        /// </summary>
        public void StopDragging() => ErsEngine.ERS_Camera2DController_StopDragging(coreInstance);

        /// <summary>
        /// Notify the controller that the user is zooming in or out.
        ///
        /// <para>Calculates a zoom factor by doing base to the power of power.</para>
        /// </summary>
        /// <param name="base">The base zoom factor.</param>
        /// <param name="power">The power of the zoom. Positive values zoom in, negative values zoom out. Larger values increase
        /// speed.</param>
        public void Zoom(float @base, float power) => ErsEngine.ERS_Camera2DController_Zoom(coreInstance, @base, power);
    }
}
