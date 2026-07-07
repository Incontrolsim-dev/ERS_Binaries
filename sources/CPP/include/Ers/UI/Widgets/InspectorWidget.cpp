#include "InspectorWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    InspectorWidget::InspectorWidget()
    {
        corePtr = Ers::Engine::ERS_InspectorWidget_Create();
    }

    InspectorWidget::~InspectorWidget()
    {
        Ers::Engine::ERS_InspectorWidget_Destroy(corePtr);
    }

    void InspectorWidget::Window(
        SelectedType selectedType,
        ModelContainer& modelContainer,
        Simulator* simulator,
        Simulator* entitySimulator,
        EntityID entity,
        PersistentEvent& persistentEvent,
        const char* name,
        bool* open,
        ImGuiWindowFlags flags)
    {
        void* simulatorPtr       = simulator ? simulator->CorePtr() : nullptr;
        void* entitySimulatorPtr = entitySimulator ? entitySimulator->CorePtr() : nullptr;
        Ers::Engine::ERS_InspectorWidget_Window(
            corePtr, static_cast<uint8_t>(selectedType), modelContainer.CorePtr(), simulatorPtr, entitySimulatorPtr, entity,
            persistentEvent.CorePtr(), name, open, flags);
    }

    void InspectorWidget::Widget(
        SelectedType selectedType,
        ModelContainer& modelContainer,
        Simulator* simulator,
        Simulator* entitySimulator,
        EntityID entity,
        PersistentEvent& persistentEvent)
    {
        void* simulatorPtr       = simulator->CorePtr();
        void* entitySimulatorPtr = entitySimulator->CorePtr();
        Ers::Engine::ERS_InspectorWidget_Widget(
            corePtr, static_cast<uint8_t>(selectedType), modelContainer.CorePtr(), &simulatorPtr, &entitySimulatorPtr, entity,
            persistentEvent.CorePtr());
    }
} // namespace Ers
