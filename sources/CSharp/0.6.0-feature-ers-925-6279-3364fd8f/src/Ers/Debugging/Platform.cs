using Ers.Engine;
using Ers;

namespace Ers
{
    /// <summary>
    /// Platform class that handles the core platform instance and frame management
    /// </summary>
    public class Platform
    {
        /// <summary>
        /// Core platform instance pointer
        /// </summary>
        private IntPtr coreInstance;

        /// <summary>
        /// Creates a new platform instance
        /// </summary>
        public Platform() { coreInstance = ErsEngine.ERS_Platform_Create(); }

        /// <summary>
        /// Begins a new frame
        /// </summary>
        public void BeginFrame() { ErsEngine.ERS_Platform_BeginFrame(coreInstance); }

        /// <summary>
        /// Ends the current frame
        /// </summary>
        public void EndFrame() { ErsEngine.ERS_Platform_EndFrame(coreInstance); }

        /// <summary>
        /// Checks if the platform should close
        /// </summary>
        /// <returns>True if platform should close, false otherwise</returns>
        public bool WantsClose() { return ErsEngine.ERS_Platform_WantsClose(coreInstance); }

        /// <summary>
        /// Destroys the platform instance and frees resources
        /// </summary>
        public void Destroy() { ErsEngine.ERS_Platform_Destroy(coreInstance); }
    }
}
