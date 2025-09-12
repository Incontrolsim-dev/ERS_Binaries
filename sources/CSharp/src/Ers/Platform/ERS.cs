using System.Text.Unicode;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// The used ERS instance.
    /// </summary>
    public class ERS
    {
        /// <summary>
        /// Initialize ERS platform.
        /// </summary>
        public static void Initialize()
        {
#if false
            if (!System.Runtime.GCSettings.IsServerGC)
            {
                Console.Error.WriteLine("ERS Requires Server GC since this is better optimized for multi-threaded applications");
                Environment.Exit(1414213562);
            }
#endif
            unsafe
            {
                // clang-format off
                fixed (byte* ptr = "C#"u8)
                {
                    ErsEngine.ERS_SetBindingType(ptr);
                }
                // clang-format on
            }
            ErsEngine.ERS_Initialize();
        }

        /// <summary>
        /// Uninitialize ERS platform.
        /// </summary>
        public static void Uninitialize() { ErsEngine.ERS_Uninitialize(); }

        /// <summary>
        /// Get the major version number of the ERS platform (A in version A.B.C).
        /// </summary>
        /// <returns>The major version number as an unsigned integer.</returns>
        public static UInt32 MajorVersion() => ErsEngine.ERS_GetMajorVersion();

        /// <summary>
        /// Get the minor version number of the ERS platform (B in version A.B.C).
        /// </summary>
        /// <returns>The minor version number as an unsigned integer.</returns>
        public static UInt32 MinorVersion() => ErsEngine.ERS_GetMinorVersion();

        /// <summary>
        /// Get the patch version number of the ERS platform (C in version A.B.C).
        /// </summary>
        /// <returns>The patch version number as an unsigned integer.</returns>
        public static UInt32 PatchVersion() => ErsEngine.ERS_GetPatchVersion();

        /// <summary>
        /// Whether the ERS platform was built in Debug mode.
        /// </summary>
        /// <returns>True if the platform was built in Debug mode, false if it was built in Release mode.</returns>
        public static bool IsDebugBuild() => ErsEngine.ERS_IsDebugBuild();
    }
}
