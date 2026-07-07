using Ers;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Window for creating a User Interface (UI) using ImGui.
    /// </summary>
    public class Window
    {
        /// <summary>
        /// Core window instance pointer.
        /// </summary>
        public readonly IntPtr CorePtr;

        /// <summary>
        /// Creates a new <see cref="Window"/> instance
        /// </summary>
        public Window() { CorePtr = ErsEngine.ERS_Window_Create(); }

        /// <summary>
        /// Creates a new <see cref="Window"/> instance with a given title.
        /// </summary>
        /// <param name="title">The title for the window.</param>
        public Window(string title)
        {
            unsafe
            {
                fixed(byte* utf8 = title.ToUtf8NullTerminated())
                {
                    CorePtr = ErsEngine.ERS_Window_Create_Title(utf8);
                }
            }
        }

        /// <summary>
        /// Create a <see cref="Window"/> from an existing window in the core.
        /// </summary>
        /// <param name="ptr">The core pointer of the existing window.</param>
        internal Window(IntPtr ptr) { CorePtr = ptr; }

        /// <summary>
        /// Begins a new frame.
        /// </summary>
        public void BeginFrame() => ErsEngine.ERS_Window_BeginFrame(CorePtr);

        /// <summary>
        /// Ends the current frame.
        /// </summary>
        public void EndFrame() => ErsEngine.ERS_Window_EndFrame(CorePtr);

        /// <summary>
        /// Begin the creation / configuration of the default root dock space.
        /// </summary>
        /// <returns>Returns true on the first frame, use this to set up the layout.</returns>
        public bool BeginRootDockSpace() => ErsEngine.ERS_Window_BeginRootDockSpace(CorePtr);

        /// <summary>
        /// End the creation / configuration of the root dock space.
        /// </summary>
        public void EndRootDockSpace() => ErsEngine.ERS_Window_EndRootDockSpace(CorePtr);

        /// <summary>
        /// The ImGuiID of the root dock space.
        /// </summary>
        public uint RootDockSpaceID => ErsEngine.ERS_Window_GetRootDockSpaceID(CorePtr);

        /// <summary>
        /// Whether the <see cref="Window"/> should close.
        /// True if it should close, false if not.
        /// </summary>
        public bool WantsClose
        {
            get => ErsEngine.ERS_Window_Get_WantsClose(CorePtr);
            set => ErsEngine.ERS_Window_Set_WantsClose(CorePtr, value);
        }

        /// <summary>
        /// Destroys the <see cref="Window"/> instance and frees resources.
        /// </summary>
        public void Destroy() => ErsEngine.ERS_Window_Destroy(CorePtr);

        /// <summary>
        /// Set the title of the window.
        ///
        /// <para>Supported image file formats are: JPEG, PNG, TGA, BMP, and GIF (first frame is used).</para>
        /// </summary>
        /// <param name="title">The new title for the window.</param>
        public void SetWindowTitle(string title)
        {
            unsafe
            {
                fixed(byte* utf8 = title.ToUtf8NullTerminated())
                {
                    ErsEngine.ERS_Window_SetWindowTitle(CorePtr, utf8);
                }
            }
        }

        /// <summary>
        /// Set the icon of the window.
        /// </summary>
        /// <param name="imagePath">The path to the image to use (relative to the ers-engine.dll file).</param>
        /// <returns>True if the icon was successfully set, false if not.</returns>
        public bool SetWindowIcon(string imagePath)
        {
            unsafe
            {
                fixed(byte* utf8 = imagePath.ToUtf8NullTerminated())
                {
                    return ErsEngine.ERS_Window_SetWindowIcon(CorePtr, utf8);
                }
            }
        }
    }
}
