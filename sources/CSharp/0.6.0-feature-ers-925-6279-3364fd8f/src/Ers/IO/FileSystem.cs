using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Virtual File System used for easy access to asset for the visualization.
    ///
    /// <para>Use it to mount directories before adding assets in them to the <see cref="Visualization.AssetManager"/>.</para>
    /// </summary>
    public static class VirtualFileSystem
    {
        /// <summary>
        /// Mount a directory to the virtual file system.
        /// </summary>
        /// <param name="path">The pat to mount, relative to the working directory of the program.</param>
        /// <param name="directoryName">The alias for the directory.</param>
        /// <returns>True when the directory was successfuly mounted, false if not.</returns>
        public static bool MountDirectory(string path, string directoryName)
        {
            var pathUtf8          = path.ToUtf8NullTerminated();
            var directoryNameutf8 = path.ToUtf8NullTerminated();

            unsafe
            {
                fixed(byte* pathByte = pathUtf8)
                {
                    fixed(byte* directoryByte = directoryNameutf8)
                    {
                        return ErsEngine.ERS_VirtualFileSystem_MountDirectory(pathByte, directoryByte);
                    }
                }
            }
        }
    }
}
