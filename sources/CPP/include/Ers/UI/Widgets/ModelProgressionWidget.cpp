#include "ModelProgressionWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    ModelProgressionWidget::ModelProgressionWidget()
    {
        corePtr = Ers::Engine::ERS_ModelProgressionWidget_Create();
    }

    ModelProgressionWidget::~ModelProgressionWidget()
    {
        Ers::Engine::ERS_ModelProgressionWidget_Destroy(corePtr);
    }

    Simulator* ModelProgressionWidget::Window(ModelContainer& modelContainer, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        void* result = Ers::Engine::ERS_ModelProgressionWidget_Window(corePtr, modelContainer.CorePtr(), name, open, flags);
        if (result == nullptr)
            return nullptr;

        return new Simulator(result);
    }

    Simulator* ModelProgressionWidget::Widget(ModelContainer& modelContainer)
    {
        void* result = Ers::Engine::ERS_ModelProgressionWidget_Widget(corePtr, modelContainer.CorePtr());
        if (result == nullptr)
            return nullptr;

        return new Simulator(result);
    }
} // namespace Ers
