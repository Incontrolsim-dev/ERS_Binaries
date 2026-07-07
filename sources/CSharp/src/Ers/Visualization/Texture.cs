using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// A texture on the GPU.
    /// </summary>
    public class Texture : IDisposable
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        /// <summary>
        /// Create an empty texture.
        /// </summary>
        public Texture() { CorePtr = ErsEngine.ERS_Texture_Create(); }

        /// <summary>
        /// Create a texture from an image file.
        /// </summary>
        /// <param name="path">The path to the image file.</param>
        public Texture(string path)
        {
            CorePtr      = ErsEngine.ERS_Texture_Create();
            var pathUtf8 = path.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* pathByte = pathUtf8)
                {
                    ErsEngine.ERS_Texture_Load(CorePtr, pathByte);
                }
            }
        }

        internal Texture(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~Texture() => DisposeInner();

        /// <summary>
        /// Indicate the Texture is no longer required and can be freed from memory.
        /// </summary>
        public void Dispose()
        {
            DisposeInner();
            GC.SuppressFinalize(this);
        }

        private void DisposeInner()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_Texture_Release(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }
    }
}
