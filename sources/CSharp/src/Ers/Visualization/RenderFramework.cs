using Ers.Engine;

namespace Ers
{
    public class RenderFramework
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr;

        public RenderFramework(IntPtr windowHandle, IntPtr displayHandle, int width, int height)
        {
            this.CorePtr = ErsEngine.ERS_RenderFramework_Create(windowHandle, displayHandle, width, height);
        }

        public void DrawRenderContext(RenderContext renderContext)
        {
            ErsEngine.ERS_RenderFramework_DrawRenderContext(CorePtr, renderContext.CorePtr);
        }

        public void Present() => ErsEngine.ERS_RenderFramework_Present(CorePtr);

        public void DisposeInner()
        {
            if (CorePtr != IntPtr.Zero)
            {
                ErsEngine.ERS_RenderFramework_Destroy(CorePtr);
                CorePtr = IntPtr.Zero;
            }
        }

        ~RenderFramework() => DisposeInner();
    }
}
