using System.Numerics;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// An area to which 2D and 3D data can be rendered.
    /// </summary>
    public class RenderContext : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Create a new RenderContext.
        /// </summary>
        /// <param name="screenWidth">The width of the render area.</param>
        /// <param name="screenHeight">The height of the render area.</param>
        public RenderContext(int screenWidth, int screenHeight)
        {
            this.CorePtr = ErsEngine.ERS_RenderContext_Create(screenWidth, screenHeight);
        }

        internal RenderContext(IntPtr corePtr) { CorePtr = corePtr; }

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
        /// Whether to draw the background grid (applies to both 2D and 3D).
        /// </summary>
        public bool DrawBackgroundGrid
        {
            get => ErsEngine.ERS_RenderContext_Get_DrawBackgroundGrid(CorePtr);
            set => ErsEngine.ERS_RenderContext_Set_DrawBackgroundGrid(CorePtr, value);
        }

        /// <summary>
        /// The background color.
        /// </summary>
        public Color BackgroundColor
        {
            get => Color.FromInt(ErsEngine.ERS_RenderContext_Get_BackgroundColor(CorePtr));
            set => ErsEngine.ERS_RenderContext_Set_BackgroundColor(CorePtr, value.Value);
        }

        /// <summary>
        /// The background grid color.
        /// </summary>
        public Color BackgroundGridColor
        {
            get => Color.FromInt(ErsEngine.ERS_RenderContext_Get_BackgroundGridColor(CorePtr));
            set => ErsEngine.ERS_RenderContext_Set_BackgroundGridColor(CorePtr, value.Value);
        }

        /// <summary>
        /// Clear the currently queued draw calls.
        /// </summary>
        public void Clear() => ErsEngine.ERS_RenderContext_ClearScreen(CorePtr);

        /// <summary>
        /// Clear the screen.
        /// <para>The screen will be cleared using the configured background color.</para>
        /// </summary>
        public void ClearScreen() => ErsEngine.ERS_RenderContext_ClearScreen(CorePtr);

        /// <summary>
        /// Set the viewport size.
        /// </summary>
        /// <param name="width">The width of the viewport.</param>
        /// <param name="height">The height of the viewport.</param>
        public void SetViewport(int width, int height) => ErsEngine.ERS_RenderContext_SetViewport(CorePtr, width, height);

        /// <summary>
        /// Begin 2D rendering mode.
        /// </summary>
        public void Begin2D() => ErsEngine.ERS_RenderContext_Begin2D(CorePtr);

        /// <summary>
        /// End 2D rendering mode.
        /// </summary>
        public void End2D() => ErsEngine.ERS_RenderContext_End2D(CorePtr);

        /// <summary>
        /// Begin 3D rendering mode.
        /// </summary>
        public void Begin3D() => ErsEngine.ERS_RenderContext_Begin3D(CorePtr);

        /// <summary>
        /// End 3D rendering mode.
        /// </summary>
        public void End3D() => ErsEngine.ERS_RenderContext_End3D(CorePtr);

        public void DrawScreenLine2D(Vector2 start, Vector2 end, float thickness, Color color, int zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawScreenLine2D(CorePtr, start.X, start.Y, end.X, end.Y, thickness, color.Value, zIndex);
        }

        public void DrawScreenLineRect2D(Vector2 center, Vector2 size, float angle, float thickness, Color color, int zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawScreenLineRect2D(
                CorePtr, center.X, center.Y, size.X, size.Y, angle, thickness, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a 2D line.
        /// </summary>
        /// <param name="start">The start position of the line.</param>
        /// <param name="end">The end position of the line.</param>
        /// <param name="thickness">The thickness of the line.</param>
        /// <param name="color">The color of the line.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawLine2D(Vector2 start, Vector2 end, float thickness, Color color, Int64 zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawLine2D(CorePtr, start.X, start.Y, end.X, end.Y, thickness, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a 2D triangle.
        /// </summary>
        /// <param name="v0">The first vertex of the triangle.</param>
        /// <param name="v1">The second vertex of the triangle.</param>
        /// <param name="v2">The third vertex of the triangle.</param>
        /// <param name="color">The color of the triangle.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawTriangle2D(Vector2 v0, Vector2 v1, Vector2 v2, Color color, Int64 zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawTriangle2D(CorePtr, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, color.Value, zIndex);
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
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawTriangle2D(Vector2 center, Vector2 size, float angle, Color color, Int64 zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawTriangle2D_Box(CorePtr, center.X, center.Y, size.X, size.Y, angle, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a 2D rectangle.
        /// </summary>
        /// <param name="center">The center of the rectangle.</param>
        /// <param name="size">The width and height of the rectangle.</param>
        /// <param name="angle">The counterclockwise rotation in turns.</param>
        /// <param name="color">The color of the rectangle.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawRect2D(Vector2 center, Vector2 size, float angle = 0.0f, Color color = default, int zIndex = 0)
        {
            if (color == default)
                color = Color.FromFloats(1.0f, 1.0f, 1.0f, 1.0f);

            ErsEngine.ERS_RenderContext_DrawRect2D(CorePtr, center.X, center.Y, size.X, size.Y, angle, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a 2D circle.
        /// </summary>
        /// <param name="center">The center of the circle.</param>
        /// <param name="size">The width and height of the circle.</param>
        /// <param name="segments">The number of segments the circle is made of.</param>
        /// <param name="angle">The counterclockwise rotation in turns.</param>
        /// <param name="color">The color of the circle.</param>
        /// <param name="zIndex">The z-index of the circle.</param>
        public void DrawCircle2D(Vector2 center, Vector2 size, int segments, float angle = 0.0f, Color color = default, int zIndex = 0)
        {
            if (color == default)
                color = Color.FromBytes(255, 255, 255, 255);

            ErsEngine.ERS_RenderContext_DrawCircle2D(CorePtr, center.X, center.Y, size.X, size.Y, segments, angle, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a 2D arc.
        /// </summary>
        /// <param name="center">The center of the arc.</param>
        /// <param name="radius">The radius of the arc.</param>
        /// <param name="width">The width of the arc.</param>
        /// <param name="beginAngle">The angle (in turns) at the start of the arc (1 turn = 360 degrees).</param>
        /// <param name="endAngle">The angle (in turns) at the end of the arc (1 turn = 360 degrees).</param>
        /// <param name="color">The color of the arc.</param>
        /// <param name="segments">The number of segments the arc consists of.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawArc2D(
            Vector2 center,
            float radius,
            float width,
            float beginAngle,
            float endAngle,
            Color color  = default,
            int segments = 10,
            Int64 zIndex = 0)
        {
            if (color == default)
                color = Color.FromFloats(1.0f, 1.0f, 1.0f, 1.0f);

            ErsEngine.ERS_RenderContext_DrawArc2D(
                CorePtr, center.X, center.Y, radius, width, beginAngle, endAngle, segments, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a texture.
        /// </summary>
        /// <param name="texture">The texture to draw.</param>
        /// <param name="center">The center position for the rectangle.</param>
        /// <param name="size">The size of the rectangle.</param>
        /// <param name="angle">The counterclockwise rotation in turns.</param>
        /// <param name="color">The color tint of the texture.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawTexture2D(
            Texture texture, Vector2 center, Vector2 size, float angle = 0.0f, Color color = default, Int64 zIndex = 0)
        {
            if (color == default)
                color = Color.FromBytes(255, 255, 255, 255);
            Vector2 uvMin = new Vector2(0, 0);
            Vector2 uvMax = new Vector2(1, 1);

            ErsEngine.ERS_RenderContext_DrawTexture2D(
                CorePtr, texture.CorePtr, center.X, center.Y, size.X, size.Y, uvMin.X, uvMin.Y, uvMax.X, uvMax.Y, angle, color.Value,
                zIndex);
        }

        /// <summary>
        /// Draw mesh data.
        /// </summary>
        /// <param name="mesh">The mesh to draw.</param>
        public void DrawMesh(Mesh mesh) => ErsEngine.ERS_RenderContext_DrawMesh(CorePtr, mesh.CorePtr);

        /// <summary>
        /// Draw a 3D model.
        /// </summary>
        /// <param name="model">The 3D model to draw.</param>
        public void DrawModel3D(Model3D model) => ErsEngine.ERS_RenderContext_DrawModel3D(CorePtr, model.CorePtr);

        /// <summary>
        /// Get the camera used for 2D rendering.
        /// </summary>
        /// <returns></returns>
        public Camera2D GetCamera2D() => new Camera2D(ErsEngine.ERS_RenderContext_GetCamera2D(CorePtr));

        /// <summary>
        /// Get the camera used for 3D rendering.
        /// </summary>
        /// <returns></returns>
        public Camera3D GetCamera3D() => new Camera3D(ErsEngine.ERS_RenderContext_GetCamera3D(CorePtr));

        /// <summary>
        /// Draw a 2D quadrilateral.
        /// </summary>
        /// <param name="v0">The first vertex of the quad.</param>
        /// <param name="v1">The second vertex of the quad.</param>
        /// <param name="v2">The third vertex of the quad.</param>
        /// <param name="v3">The fourth vertex of the quad.</param>
        /// <param name="color">The color of the quad.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawQuad2D(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3, Color color, Int64 zIndex = 0)
        {
            ErsEngine.ERS_RenderContext_DrawQuad2D(CorePtr, v0.X, v0.Y, v1.X, v1.Y, v2.X, v2.Y, v3.X, v3.Y, color.Value, zIndex);
        }

        /// <summary>
        /// Draw a 3D cube.
        /// </summary>
        /// <param name="position">The position of the cube.</param>
        /// <param name="rotation">The rotation of the cube (in turns).</param>
        /// <param name="scale">The scale of the cube.</param>
        /// <param name="color">The color of the cube.</param>
        public void DrawCube3D(Vector3 position, Vector3 rotation = default, Vector3 scale = default, Color color = default)
        {
            if (rotation == default)
                rotation = Vector3.Zero;
            if (scale == default)
                scale = Vector3.One;
            if (color == default)
                color = Color.FromBytes(255, 255, 255, 255);

            ErsEngine.ERS_RenderContext_DrawCube3D(
                CorePtr, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, scale.X, scale.Y, scale.Z, color.Value);
        }

        /// <summary>
        /// Draw an instanced 3D model using a mesh and instancing data.
        /// </summary>
        /// <param name="mesh">The mesh to draw.</param>
        /// <param name="instancedModel">The instancing data.</param>
        public void DrawInstancedModel3D(Mesh mesh, InstancedModel instancedModel)
        {
            ErsEngine.ERS_RenderContext_DrawInstancedModel3DWithMesh(CorePtr, mesh.CorePtr, instancedModel.CorePtr);
        }

        public void DrawInstancedModel3D(InstancedModel instancedModel)
        {
            ErsEngine.ERS_RenderContext_DrawInstancedModel3D(CorePtr, instancedModel.CorePtr);
        }

        /// <summary>
        /// Draw 2D text using a built-in font.
        /// </summary>
        /// <param name="text">The text to draw.</param>
        /// <param name="pos">The position to draw the text from (top-left of first character).</param>
        /// <param name="scale">The scale of the font.</param>
        /// <param name="color">The color of the text.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawText2D(string text, Vector2 pos, float scale, Color color = default, Int64 zIndex = 0)
        {
            if (color == default)
                color = Color.FromBytes(0, 0, 0, 255);

            var textUtf8 = text.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_RenderContext_DrawText2D(CorePtr, textByte, pos.X, pos.Y, scale, color.Value, zIndex);
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
        public void DrawText3D(string text, Vector3 center, Vector3 normal, Vector3 worldUp, float scale, Color color = default)
        {
            if (color == default)
                color = Color.FromBytes(0, 0, 0, 255);

            var textUtf8 = text.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_RenderContext_DrawText3D(
                        CorePtr, textByte, center.X, center.Y, center.Z, normal.X, normal.Y, normal.Z, worldUp.X, worldUp.Y, worldUp.Z,
                        scale, color.Value);
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
        public void DrawTextBillboard(string text, Vector3 center, float scale, Color color = default)
        {
            if (color == default)
                color = Color.FromBytes(255, 255, 255, 255);
            var textUtf8 = text.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* textByte = textUtf8)
                {
                    ErsEngine.ERS_RenderContext_DrawTextBillboard(CorePtr, textByte, center.X, center.Y, center.Z, scale, color.Value);
                }
            }
        }

        /// <summary>
        /// Set the direction of the light.
        /// </summary>
        /// <param name="direction">The direction of the light.</param>
        public void SetLightDirection(Vector3 direction)
        {
            ErsEngine.ERS_RenderContext_SetLightDirection(CorePtr, direction.X, direction.Y, direction.Z);
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
        /// <param name="color">The color tint.</param>
        /// <param name="zIndex">The z-index for layering.</param>
        public void DrawTexture2D(
            Texture texture,
            Vector2 position,
            Vector2 size,
            Vector2 uvMin,
            Vector2 uvMax,
            float angle  = 0.0f,
            Color color  = default,
            Int64 zIndex = 0)
        {
            if (color == default)
                color = Color.FromBytes(255, 255, 255, 255);

            ErsEngine.ERS_RenderContext_DrawTexture2D(
                CorePtr, texture.CorePtr, position.X, position.Y, size.X, size.Y, uvMin.X, uvMin.Y, uvMax.X, uvMax.Y, angle, color.Value,
                zIndex);
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
                    ErsEngine.ERS_RenderContext_CalculateTextSize(CorePtr, textByte, scale, (IntPtr)(&width), (IntPtr)(&height));
                }
                return new Vector2(width, height);
            }
        }
    }
}
