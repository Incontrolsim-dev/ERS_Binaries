#include "Window.h"
#include "Ers/Api.h"

namespace Ers::Visualization
{
    Window::Window(void* windowHandle, void* displayHandle, int screenWidth, int screenHeight)
    {
        data = ersAPIFunctionPointers.ERS_Window_Create(windowHandle, displayHandle, screenWidth, screenHeight);
    }

    void Window::Present()
    {
        ersAPIFunctionPointers.ERS_Window_Present(data);
    }

    void Window::DrawRenderContext(RenderContext& renderContext)
    {
        ersAPIFunctionPointers.ERS_Window_DrawRenderContext(data, renderContext.GetData());
    }

    Window::~Window()
    {
        ersAPIFunctionPointers.ERS_Window_Destroy(data);
    }

} // namespace Ers::Visualization