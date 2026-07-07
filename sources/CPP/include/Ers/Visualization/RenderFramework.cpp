#include "RenderFramework.h"
#include "Ers/Api.h"

namespace Ers
{
    RenderFramework::RenderFramework(void* windowHandle, void* displayHandle, int screenWidth, int screenHeight)
    {
        corePtr = Ers::Engine::ERS_RenderFramework_Create(windowHandle, displayHandle, screenWidth, screenHeight);
    }

    void RenderFramework::Present()
    {
        Ers::Engine::ERS_RenderFramework_Present(corePtr);
    }

    void RenderFramework::DrawRenderContext(RenderContext& renderContext)
    {
        Ers::Engine::ERS_RenderFramework_DrawRenderContext(corePtr, renderContext.CorePtr());
    }

    RenderFramework::~RenderFramework()
    {
        Ers::Engine::ERS_RenderFramework_Destroy(corePtr);
    }

} // namespace Ers
