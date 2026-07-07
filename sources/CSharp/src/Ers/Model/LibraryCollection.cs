using System;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Collection for managing dynamically loaded libraries.
    /// </summary>
    public class LibraryCollection
    {
        public readonly IntPtr CorePtr;

        internal LibraryCollection(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// Open a dynamic library.
        /// </summary>
        /// <param name="libraryPath">The path to the library</param>
        /// <returns>True if the library was opened successfully</returns>
        public bool OpenLibrary(string libraryPath)
        {
            var pathUtf8 = libraryPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* pathByte = pathUtf8)
                {
                    return ErsEngine.ERS_LibraryCollection_OpenLibrary(CorePtr, pathByte);
                }
            }
        }

        /// <summary>
        /// Check if a library is open.
        /// </summary>
        /// <param name="libraryPath">The path to the library</param>
        /// <returns>True if the library is open</returns>
        public bool IsLibraryOpen(string libraryPath)
        {
            var pathUtf8 = libraryPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* pathByte = pathUtf8)
                {
                    return ErsEngine.ERS_LibraryCollection_IsLibraryOpen(CorePtr, pathByte);
                }
            }
        }

        /// <summary>
        /// Get a raw function pointer from a library.
        /// </summary>
        /// <param name="libraryPath">The path to the library</param>
        /// <param name="functionName">The name of the function</param>
        /// <returns>Pointer to the function</returns>
        public IntPtr GetFunctionRaw(string libraryPath, string functionName)
        {
            var pathUtf8 = libraryPath.ToUtf8NullTerminated();
            var nameUtf8 = functionName.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* pathByte = pathUtf8) fixed(byte* nameByte = nameUtf8)
                {
                    return ErsEngine.ERS_LibraryCollection_GetFunctionFromLibrary(CorePtr, pathByte, nameByte);
                }
            }
        }

        /// <summary>
        /// Get the library handle.
        /// </summary>
        /// <param name="libraryPath">The path to the library</param>
        /// <returns>Handle to the library</returns>
        public IntPtr GetLibraryHandle(string libraryPath)
        {
            var pathUtf8 = libraryPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* pathByte = pathUtf8)
                {
                    return ErsEngine.ERS_LibraryCollection_GetLibraryHandle(CorePtr, pathByte);
                }
            }
        }
    }
}
