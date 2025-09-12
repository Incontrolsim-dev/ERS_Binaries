using System.Numerics;
using Ers.Engine;

namespace Ers.Visualization
{
    /// <summary>
    /// 2D othrographic camera.
    /// </summary>
    public class Camera2D
    {
        internal readonly IntPtr Data;

        internal Camera2D(IntPtr coreInstance) { Data = coreInstance; }

        /// <summary>
        /// Update the camera's projection and view matrices.
        /// </summary>
        /// <param name="screenWidth"></param>
        /// <param name="screenHeight"></param>
        public void UpdateTransform(int screenWidth, int screenHeight)
        {
            ErsEngine.ERS_Camera2D_UpdateTransform(Data, screenWidth, screenHeight);
        }

        /// <summary>
        /// The 2D position of the camera.
        /// </summary>
        public Vector2 Position
        {
            get {
                unsafe
                {
                    return new Vector2(*(float*)ErsEngine.ERS_Camera2D_PositionX(Data), *(float*)ErsEngine.ERS_Camera2D_PositionY(Data));
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera2D_PositionX(Data) = value.X;
                    *(float*)ErsEngine.ERS_Camera2D_PositionY(Data) = value.Y;
                }
            }
        }

        /// <summary>
        /// The zoom factor of the camera.
        /// </summary>
        public float Zoom
        {
            get {
                unsafe
                {
                    return *(float*)ErsEngine.ERS_Camera2D_Zoom(Data);
                }
            }
            set {
                unsafe
                {
                    *(float*)ErsEngine.ERS_Camera2D_Zoom(Data) = value;
                }
            }
        }

        /// <summary>
        /// Get the size of an object if it should be rendered as a single pixel (1 / Zoom).
        /// Multiply the number of pixels (N) by the returned value to get the size of something that is N pixels in size.
        /// </summary>
        /// <returns></returns>
        public float SizePerPixel() => ErsEngine.ERS_Camera2D_SizePerPixel(Data);

        /// <summary>
        /// Get the world position of a point on the screen.
        /// </summary>
        /// <param name="screenWidth">The current width of the screen.</param>
        /// <param name="screenHeight">The current height of the screen.</param>
        /// <param name="screenPos">The screen position to get the world position of.</param>
        /// <returns></returns>
        public Vector2 GetWorldPos(int screenWidth, int screenHeight, Vector2 screenPos)
        {
            unsafe
            {
                float x = 0.0f;
                float y = 0.0f;
                ErsEngine.ERS_Camera2D_GetWorldPos(Data, screenWidth, screenHeight, screenPos.X, screenPos.Y, (IntPtr)(&x), (IntPtr)(&y));
                return new Vector2(x, y);
            }
        }
    }
}
