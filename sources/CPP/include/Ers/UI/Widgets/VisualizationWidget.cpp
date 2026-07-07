#include "VisualizationWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    VisualizationWidget::VisualizationWidget()
    {
        corePtr = Ers::Engine::ERS_VisualizationWidget_Create();
    }

    VisualizationWidget::~VisualizationWidget()
    {
        Ers::Engine::ERS_VisualizationWidget_Destroy(corePtr);
    }

    bool VisualizationWidget::GetIs3DMode() const
    {
        return Ers::Engine::ERS_VisualizationWidget_Get_Is3DMode(corePtr);
    }

    void VisualizationWidget::SetIs3DMode(bool value)
    {
        Ers::Engine::ERS_VisualizationWidget_Set_Is3DMode(corePtr, value);
    }

    void VisualizationWidget::Window(RenderContext& renderContext, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_VisualizationWidget_Window(corePtr, renderContext.CorePtr(), name, open, flags);
    }

    void VisualizationWidget::Widget(RenderContext& renderContext)
    {
        Ers::Engine::ERS_VisualizationWidget_Widget(corePtr, renderContext.CorePtr());
    }
} // namespace Ers
