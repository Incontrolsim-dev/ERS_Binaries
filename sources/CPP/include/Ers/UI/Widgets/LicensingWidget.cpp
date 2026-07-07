#include "LicensingWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    LicensingWidget::LicensingWidget()
    {
        corePtr = Ers::Engine::ERS_LicensingWidget_Create();
    }

    LicensingWidget::~LicensingWidget()
    {
        Ers::Engine::ERS_LicensingWidget_Destroy(corePtr);
    }

    void LicensingWidget::Window(const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_LicensingWidget_Window(corePtr, name, open, flags);
    }

    void LicensingWidget::Widget()
    {
        Ers::Engine::ERS_LicensingWidget_Widget(corePtr);
    }
} // namespace Ers
