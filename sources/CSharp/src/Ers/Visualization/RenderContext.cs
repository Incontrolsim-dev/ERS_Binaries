using System.Numerics;
using Ers.Engine;

namespace Ers.Visualization
{
    /// <summary>
    /// An area to which 2D and 3D data can be rendered.
    /// </summary>
    public class RenderContext : IDisposable
    {
        private IntPtr coreInstance;

        /// <summary>
        /// Create a new RenderContext.
        /// </summary>
        /// <param name="screenWidth">The width of the render area.</param>
        /// <param name="screenHeight">The height of the render area.</param>
        public RenderContext(int screenWidth, int screenHeight)
        {
            this.coreInstance = ErsEngine.ERS_RenderContext_Create(screenWidth, screenHeight);
        }

        public RenderContext(IntPtr corePtr) { coreInstance = corePtr; }

        /// <summary>
        /// Finalizer / Destructor for RenderContext.
        /// </summary>
        //~RenderContext() => DisposeInner();

        /// <summary>
        /// Dispose this RenderContext, releasing its resources and shutting down the render engine.
        /// </summary>
        public void Dispose()
        {
            // DisposeInner();
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Clear the currently queued draw calls (those that have net yet been drawn by calling <see cref="NextFrame"/>).
        /// </summary>
        public void Clear() => ErsEngine.ERS_RenderContext_ClearScreen(coreInstance);

        public void Present() => ErsEngine.ERS_RenderContext_Present(coreInstance);

        /// <summary>
        /// Clear the screen.
        /// <para>The screen will be cleared using the configured background color.</para>
        /// </summary>
        public void ClearScreen() => ErsEngine.ERS_RenderContext_ClearScreen(coreInstance);

        /// <summary>
        /// Set the viewport size.
        /// </summary>
        /// <param name="width">The width of the viewport.</param>
        /// <param name="height">The height of the viewport.</param>
        public void SetViewport(int width, int height) => ErsEngine.ERS_RenderContext_SetViewport(coreInstance, width, height);

        /// <summary>
        /// Begin 2D rendering mode.
        /// </summary>
        public void Begin2D() => ErsEngine.ERS_RenderContext_Begin2D(coreInstance);

        /// <summary>
        /// End 2D rendering mode.
        /// </summary>
        public void End2D() => ErsEngine.ERS_RenderContext_End2D(coreInstance);

        /// <summary>
        /// Begin 3D rendering mode.
        /// </summary>
        public void Begin3D() => ErsEngine.ERS_RenderContext_Begin3D(coreInstance);

        /// <summary>
        /// End 3D rendering mode.
        /// </summary>
        public void End3D() => ErsEngine.ERS_RenderContext_End3D(coreInstance);

        /// <summary>
        /// Set the background color.
        /// </summary>
        /// <param name="color">The color as an RGB vector with color channels in range [0,1].</param>
        public void SetBackgroundColor(Vector3 color = default)
        {
            if (color == default)
                color = new Vector3(0.7f, 0.7f, 1.0f);

            ErsEngine.ERS_RenderContext_SetBackgroundColor(coreInstance, color.X, color.Y, color.Z, 1.0f);
        }

        public void DrawScreenLine2D(Vector2 start, Vector2 end, float thickness, Vector4 color, int zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawScreenLine2D(
                coreInstance, start.X, start.Y, end.X, end.Y, thickness, color.X, color.Y, color.Z, color.W, zIndex);
        }

        public void DrawScreenLineRect2D(Vector2 center, Vector2 size, float angle, float thickness, Vector4 color, int zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawScreenLineRect2D(
                coreInstance, center.X, center.Y, size.X, size.Y, angle, thickness, color.X, color.Y, color.Z, color.W, zIndex);
        }

        /// <summary>
        /// Draw a 2D line.
        /// </summary>
        /// <param name="start">The start position of the line.</param>
        /// <param name="end">The end position of the line.</param>
        /// <param name="thickness">The thickness of the line.</param>
        /// <param name="color">The color of the line.</param>
        public void DrawLine2D(Vector2 start, Vector2 end, float thickness, Vector4 color)
        {
            ErsEngine.ERS_RenderContext_DrawLine2D(
                coreInstance, start.X, start.Y, end.X, end.Y, thickness, color.X, color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Draw a 2D triangle.
        /// </summary>
        /// <param name="v0">The first vertex of the triangle.</param>
        /// <param name="v1">The second vertex of the triangle.</param>
        /// <param name="v2">The third vertex of the triangle.</param>
        /// <param name="color">The color of the triangle.</param>
        public void DrawTriangle2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector4 color)
        {
            ErsEngine.ERS_RenderContext_DrawTriangle2D(
                coreInstance, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, color.X, color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Draw a 2D triangle.
        ///
        /// <para>The triangle is drawn as it would be inside a bounding box where the bottom-left and bottom-right vertices match the box's
        /// and the top vertex is in the middle of the top edge of the box.</para>
        /// </summary>
        /// <param name="center">The center of the bounding box.</param>
        /// <param name="size">The dimensions of the bounding box.</param>
        /// <param name="angle">The counterclockwise rotation of the triangle.</param>
        /// <param name="color">The color of the triangle.</param>
        public void DrawTriangle2D(Vector2 center, Vector2 size, float angle, Vector4 color)
        {
            ErsEngine.ERS_RenderContext_DrawTriangle2D_Box(
                coreInstance, center.X, center.Y, size.X, size.Y, angle, color.X, color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Draw a 2D rectangle.
        /// </summary>
        /// <param name="center">The center of the rectangle.</param>
        /// <param name="size">The width and height of the rectangle.</param>
        /// <param name="angle">The counterclockwise rotation in turns.</param>
        /// <param name="color">The color of the rectangle.</param>
        /// <param name="zIndex">The z-index of the rectangle.</param>
        public void DrawRect2D(Vector2 center, Vector2 size, float angle = 0.0f, Vector4 color = default, int zIndex = 0)
        {
            if (color == default)
                color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);

            ErsEngine.ERS_RenderContext_DrawRect2D(
                coreInstance, center.X, center.Y, size.X, size.Y, angle, color.X, color.Y, color.Z, color.W, zIndex);
        }

        /// <summary>
        /// Draw a 2D arc.
        /// </summary>
        /// <param name="center">The center of the arc.</param>
        /// <param name="radius">The radius of the arc.</param>
        /// <param name="width">The width of the arc.</param>
        /// <param name="beginAngle">The angle at the start of the arc.</param>
        /// <param name="endAngle">The angle at the end of the arc.</param>
        /// <param name="color">The color of the arc.</param>
        /// <param name="segments">The number of segments the arc consists of.</param>
        public void DrawArc2D(
            Vector2 center, float radius, float width, float beginAngle, float endAngle, Vector4 color = default, int segments = 10)
        {
            if (color == default)
                color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);

            ErsEngine.ERS_RenderContext_DrawArc2D(
                coreInstance, center.X, center.Y, radius, width, beginAngle, endAngle, segments, color.X, color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Draw an infinite 2D grid. The grid fades between different grid sizes based on the camera zoom.
        /// </summary>
        /// <param name="color">The color of the grid lines.</param>
        /// <param name="lineThickness">The thickness of the grid lines.</param>
        /// <param name="armLength">The length of the grid arms. A value of 0.5 creates a full grid.</param>
        /// <param name="targetPixelSize">The target pixel size of the grid cells.</param>
        public void DrawInfiniteGrid2D(
            Vector3 color = default, float lineThickness = 1.0f, float armLength = 0.1f, float targetPixelSize = 64.0f)
        {
            if (color == default)
                color = new Vector3(0.0f, 0.0f, 0.0f);

            ErsEngine.ERS_RenderContext_DrawInfiniteGrid2D(
                coreInstance, color.X, color.Y, color.Z, lineThickness, armLength, targetPixelSize);
        }

        /// <summary>
        /// Draw a texture.
        /// </summary>
        /// <param name="texture">The texture to draw.</param>
        /// <param name="center">The center position for the rectangle.</param>
        /// <param name="size">The size of the rectangle.</param>
        /// <param name="angle">The counterclockwise rotation in turns.</param>
        /// <param name="color">The color of the rectangle as an RGB vector with channels in range [0,1].</param>
        public void DrawTexture2D(Texture texture, Vector2 center, Vector2 size, float angle = 0.0f, Vector3 color = default)
        {
            if (color == default)
                color = new Vector3(1.0f, 1.0f, 1.0f);
            Vector2 uvMin = new Vector2(0, 0);
            Vector2 uvMax = new Vector2(1, 1);

            ErsEngine.ERS_RenderContext_DrawTexture2D(
                coreInstance, texture.Data, center.X, center.Y, size.X, size.Y, uvMin.X, uvMin.Y, uvMax.X, uvMax.Y, angle, color.X, color.Y,
                color.Z, 1.0f);
        }

        /// <summary>
        /// Draw mesh data.
        /// </summary>
        /// <param name="mesh">The mesh to draw.</param>
        public void DrawMesh(Mesh mesh) => ErsEngine.ERS_RenderContext_DrawMesh(coreInstance, mesh.Data);

        /// <summary>
        /// Draw a 3D model.
        /// </summary>
        /// <param name="model">The 3D model to draw.</param>
        public void DrawModel3D(Model3D model) => ErsEngine.ERS_RenderContext_DrawModel3D(coreInstance, model.Data);

        /// <summary>
        /// Draw an infinite 3D grid. The grid fades between different grid sizes based on the camera zoom.
        /// </summary>
        /// <param name="color">The color of the grid.</param>
        /// <param name="lineThickness">The thickness of the grid lines.</param>
        /// <param name="targetPixelSize">The target pixel size of the grid cells.</param>
        public void DrawInfiniteGrid3D(Vector3 color = default, float lineThickness = 1.0f, float targetPixelSize = 64.0f)
        {
            if (color == default)
                color = new Vector3(0.0f, 0.0f, 0.0f);

            ErsEngine.ERS_RenderContext_DrawInfiniteGrid3D(coreInstance, color.X, color.Y, color.Z, lineThickness, targetPixelSize);
        }

        /// <summary>
        /// Get the camera used for 2D rendering.
        /// </summary>
        /// <returns></returns>
        public Camera2D GetCamera2D() => new Camera2D(ErsEngine.ERS_RenderContext_GetCamera2D(coreInstance));

        /// <summary>
        /// Get the camera used for 3D rendering.
        /// </summary>
        /// <returns></returns>
        public Camera3D GetCamera3D() => new Camera3D(ErsEngine.ERS_RenderContext_GetCamera3D(coreInstance));

        /// <summary>
        /// Draw a 2D quadrilateral.
        /// </summary>
        /// <param name="v0">The first vertex of the quad.</param>
        /// <param name="v1">The second vertex of the quad.</param>
        /// <param name="v2">The third vertex of the quad.</param>
        /// <param name="v3">The fourth vertex of the quad.</param>
        /// <param name="color">The color of the quad.</param>
        public void DrawQuad2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, Vector4 color)
        {
            uint colorU32 = ColorToUInt32(color);
            ErsEngine.ERS_RenderContext_DrawQuad2D(
                coreInstance, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, v3.X, v3.Y, color.X, color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Draw a 3D cube.
        /// </summary>
        /// <param name="position">The position of the cube.</param>
        /// <param name="rotation">The rotation of the cube (in turns).</param>
        /// <param name="scale">The scale of the cube.</param>
        /// <param name="color">The color of the cube.</param>
        public void DrawCube3D(Vector3 position, Vector3 rotation = default, Vector3 scale = default, Vector4 color = default)
        {
            if (rotation == default)
                rotation = Vector3.Zero;
            if (scale == default)
                scale = Vector3.One;
            if (color == default)
                color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);

            ErsEngine.ERS_RenderContext_DrawCube3D(
                coreInstance, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, scale.X, scale.Y, scale.Z, color.X,
                color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Draw an instanced 3D model using a mesh and instancing data.
        /// </summary>
        /// <param name="mesh">The mesh to draw.</param>
        /// <param name="instancedModel">The instancing data.</param>
        public void DrawInstancedModel3D(Mesh mesh, InstancedModel instancedModel)
        {
            ErsEngine.ERS_RenderContext_DrawInstancedModel3DWithMesh(coreInstance, mesh.Data, instancedModel.Data);
        }

        public void DrawInstancedModel3D(InstancedModel instancedModel)
        {
            ErsEngine.ERS_RenderContext_DrawInstancedModel3D(coreInstance, instancedModel.Data);
        }

        /// <summary>
        /// Draw 2D text using a built-in font.
        /// </summary>
        /// <param name="text">The text to draw.</param>
        /// <param name="pos">The position to draw the text from (top-left of first character).</param>
        /// <param name="scale">The scale of the font.</param>
        /// <param name="color">The color o
        public void DrawText2D(string text, Vector2 pos, float scale, Vector4 color = default)
        {
            if (color == default)
                color = new Vector4(0.0f, 0.0f, 0.0f, 1.0f);

            var textUtf8 = text.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_RenderContext_DrawText2D(coreInstance, textByte, pos.X, pos.Y, scale, color.X, color.Y, color.Z, color.W);
                }
            }
        }

        /// <summary>
        /// Draw 3D text.
        /// </summary>
        /// <param name="text">The text to draw.</param>
        /// <param name="center">The center position of the text.</param>
        /// <param name="normal">The normal vector of the text plane.</param>
        /// <param name="worldUp">The world up vector.</param>
        /// <param name="scale">The scale of the font.</param>
        /// <param name="color">The color of the text.</param>
        public void DrawText3D(string text, Vector3 center, Vector3 normal, Vector3 worldUp, float scale, Vector4 color = default)
        {
            if (color == default)
                color = new Vector4(0.0f, 0.0f, 0.0f, 1.0f);

            var textUtf8 = text.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_RenderContext_DrawText3D(
                        coreInstance, textByte, center.X, center.Y, center.Z, normal.X, normal.Y, normal.Z, worldUp.X, worldUp.Y, worldUp.Z,
                        scale, color.X, color.Y, color.Z, color.W);
                }
            }
        }

        /// <summary>
        /// Draw text as a billboard (always facing the camera).
        /// </summary>
        /// <param name="text">The text to draw.</param>
        /// <param name="center">The center position of the text.</param>
        /// <param name="scale">The scale of the font.</param>
        /// <param name="color">The color of the text.</param>
        public void DrawTextBillboard(string text, Vector3 center, float scale, Vector4 color = default)
        {
            if (color == default)
                color = new Vector4(1, 1, 1, 1);
            var textUtf8 = text.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_RenderContext_DrawTextBillboard(
                        coreInstance, textByte, center.X, center.Y, center.Z, scale, color.X, color.Y, color.Z, color.W);
                }
            }
        }

        /// <summary>
        /// Set the direction of the light.
        /// </summary>
        /// <param name="direction">The direction of the light.</param>
        public void SetLightDirection(Vector3 direction)
        {
            ErsEngine.ERS_RenderContext_SetLightDirection(coreInstance, direction.X, direction.Y, direction.Z);
        }

        /// <summary>
        /// Draw a texture with UV coordinates.
        /// </summary>
        /// <param name="texture">The texture to draw.</param>
        /// <param name="position">The position of the texture.</param>
        /// <param name="size">The size of the texture.</param>
        /// <param name="uvMin">The minimum UV coordinates.</param>
        /// <param name="uvMax">The maximum UV coordinates.</param>
        /// <param name="angle">The counterclockwise rotation in turns.</param>
        /// <param name="color">The color tint as an RGBA vector with channels in range [0,1].</param>
        public void DrawTexture2D(
            Texture texture, Vector2 position, Vector2 size, Vector2 uvMin, Vector2 uvMax, float angle = 0.0f, Vector4 color = default)
        {
            if (color == default)
                color = new Vector4(1.0f, 1.0f, 1.0f, 1.0f);

            ErsEngine.ERS_RenderContext_DrawTexture2D(
                coreInstance, texture.Data, position.X, position.Y, size.X, size.Y, uvMin.X, uvMin.Y, uvMax.X, uvMax.Y, angle, color.X,
                color.Y, color.Z, color.W);
        }

        /// <summary>
        /// Calculate the size of a piece of text.
        /// </summary>
        /// <param name="text">The text to calculate the size of.</param>
        /// <param name="scale">The scale of the text.</param>
        /// <returns>The width and height of the text.</returns>
        public Vector2 CalculateTextSize(string text, float scale)
        {
            unsafe
            {
                float width = 0, height = 0;

                fixed(byte* textByte = text.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_RenderContext_CalculateTextSize(coreInstance, textByte, scale, (IntPtr)(&width), (IntPtr)(&height));
                }
                return new Vector2(width, height);
            }
        }

        /// <summary>
        /// Helper method to convert a Vector4 color to a uint32 color value.
        /// </summary>
        /// <param name="color">The color as a Vector4 with components in range [0,1].</param>
        /// <returns>The color as a packed uint32 value.</returns>
        private static uint ColorToUInt32(Vector4 color)
        {
            byte r = (byte)(MathF.Max(0.0f, MathF.Min(1.0f, color.X)) * 255.0f);
            byte g = (byte)(MathF.Max(0.0f, MathF.Min(1.0f, color.Y)) * 255.0f);
            byte b = (byte)(MathF.Max(0.0f, MathF.Min(1.0f, color.Z)) * 255.0f);
            byte a = (byte)(MathF.Max(0.0f, MathF.Min(1.0f, color.W)) * 255.0f);

            return (uint)((a << 24) | (b << 16) | (g << 8) | r);
        }

        internal IntPtr GetCoreInstance() { return coreInstance; }

        /// <summary>
        /// The ambient light color of the scene.
        ///
        /// <para>The color channels are in range [0,1].</para>
        /// </summary>
        // public Vector3 AmbientLightColor
        //{
        //     get {
        //         unsafe
        //         {
        //             return new Vector3(
        //                 *(float*)ErsEngine.ERS_RenderContext_AmbientLightColor_X(coreInstance),
        //                 *(float*)ErsEngine.ERS_RenderContext_AmbientLightColor_Y(coreInstance),
        //                 *(float*)ErsEngine.ERS_RenderContext_AmbientLightColor_Z(coreInstance));
        //         }
        //     }
        //     set {
        //         unsafe
        //         {
        //             *(float*)ErsEngine.ERS_RenderContext_AmbientLightColor_X(coreInstance) = value.X;
        //             *(float*)ErsEngine.ERS_RenderContext_AmbientLightColor_Y(coreInstance) = value.Y;
        //             *(float*)ErsEngine.ERS_RenderContext_AmbientLightColor_Z(coreInstance) = value.Z;
        //         }
        //     }
        // }
    }
}
