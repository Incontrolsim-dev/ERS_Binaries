using Ers.Engine;

namespace Ers.Visualization
{
    /// <summary>
    /// A texture on the GPU.
    /// </summary>
    public class Texture : IDisposable
    {
        internal IntPtr Data;

        /// <summary>
        /// Create an empty texture.
        /// </summary>
        public Texture() { Data = ErsEngine.ERS_Texture_Create(); }

        /// <summary>
        /// Create a texture from an image file.
        /// </summary>
        /// <param name="path">The path to the image file.</param>
        public Texture(string path)
        {
            Data         = ErsEngine.ERS_Texture_Create();
            var pathUtf8 = path.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* pathByte = pathUtf8)
                {
                    ErsEngine.ERS_Texture_Load(Data, pathByte);
                }
            }
        }

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
            if (Data != IntPtr.Zero)
            {
                ErsEngine.ERS_Texture_Release(Data);
                Data = IntPtr.Zero;
            }
        }
    }
}
