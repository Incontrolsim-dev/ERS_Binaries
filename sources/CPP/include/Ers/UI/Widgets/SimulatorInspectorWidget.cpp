#include "SimulatorInspectorWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    SimulatorInspectorWidget::SimulatorInspectorWidget()
    {
        corePtr = Ers::Engine::ERS_SimulatorInspectorWidget_Create();
    }

    SimulatorInspectorWidget::~SimulatorInspectorWidget()
    {
        Ers::Engine::ERS_SimulatorInspectorWidget_Destroy(corePtr);
    }

    void SimulatorInspectorWidget::Window(Simulator& simulator, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_SimulatorInspectorWidget_Window(corePtr, simulator.CorePtr(), name, open, flags);
    }

    void SimulatorInspectorWidget::Widget(Simulator& simulator)
    {
        Ers::Engine::ERS_SimulatorInspectorWidget_Widget(corePtr, simulator.CorePtr());
    }
} // namespace Ers
