#include "ModelContainerInspectorWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    void ModelContainerInspectorWidget::Window(ModelContainer& modelContainer, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_ModelContainerInspectorWidget_Window(modelContainer.CorePtr(), name, open, flags);
    }

    void ModelContainerInspectorWidget::Widget(ModelContainer& modelContainer)
    {
        Ers::Engine::ERS_ModelContainerInspectorWidget_Widget(modelContainer.CorePtr());
    }
} // namespace Ers
