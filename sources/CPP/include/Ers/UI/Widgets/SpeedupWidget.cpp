#include "SpeedupWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    SpeedupWidget::SpeedupWidget()
    {
        corePtr = Ers::Engine::ERS_SpeedupWidget_Create();
    }

    SpeedupWidget::~SpeedupWidget()
    {
        Ers::Engine::ERS_SpeedupWidget_Destroy(corePtr);
    }

    void SpeedupWidget::Window(const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_SpeedupWidget_Window(corePtr, name, open, flags);
    }

    void SpeedupWidget::Widget()
    {
        Ers::Engine::ERS_SpeedupWidget_Widget(corePtr);
    }

    void SpeedupWidget::Update(const ModelContainer& modelContainer)
    {
        Ers::Engine::ERS_SpeedupWidget_Update(corePtr, modelContainer.CorePtr());
    }
} // namespace Ers
