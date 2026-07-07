#include "RunControlsWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    RunControlsWidget::RunControlsWidget()
    {
        corePtr = Ers::Engine::ERS_RunControlsWidget_Create();
    }

    RunControlsWidget::~RunControlsWidget()
    {
        Ers::Engine::ERS_RunControlsWidget_Destroy(corePtr);
    }

    void RunControlsWidget::Window(ModelContainer& modelContainer, bool& isRunning, const char* name)
    {
        Ers::Engine::ERS_RunControlsWidget_Window(corePtr, modelContainer.CorePtr(), &isRunning, name);
    }

    void RunControlsWidget::Widget(ModelContainer& modelContainer, bool& isRunning)
    {
        Ers::Engine::ERS_RunControlsWidget_Widget(corePtr, modelContainer.CorePtr(), &isRunning);
    }
} // namespace Ers
