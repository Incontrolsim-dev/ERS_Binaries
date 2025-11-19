using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    public class Window
    {
        private IntPtr coreInstance;

        public Window(IntPtr windowHandle, IntPtr displayHandle, int width, int height)
        {
            this.coreInstance = ErsEngine.ERS_Window_Create(windowHandle, displayHandle, width, height);
        }

        public IntPtr GetCoreInstance() { return coreInstance; }

        public void DrawRenderContext(RenderContext renderContext)
        {
            ErsEngine.ERS_Window_DrawRenderContext(coreInstance, renderContext.GetCoreInstance());
        }

        public void Present() { ErsEngine.ERS_Window_Present(coreInstance); }

        public void DisposeInner()
        {
            if (coreInstance != IntPtr.Zero)
            {
                ErsEngine.ERS_Window_Destroy(coreInstance);
                coreInstance = IntPtr.Zero;
            }
        }

        ~Window() => DisposeInner();
    }
}