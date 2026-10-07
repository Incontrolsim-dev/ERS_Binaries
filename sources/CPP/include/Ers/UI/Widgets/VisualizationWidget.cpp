#include "VisualizationWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    VisualizationWidget::EntitySelectionArgs::EntitySelectionArgs(
        ModelContainer& modelContainer, SelectedType& selectedType, EntityID& selectedEntity, Simulator*& selectedEntitySimulator) :
        Model(modelContainer),
        Type(selectedType),
        SelectedEntity(selectedEntity),
        SelectedEntitySimulator(selectedEntitySimulator)
    {
    }

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

    void VisualizationWidget::Window(
        RenderContext& renderContext, EntitySelectionArgs* entitySelectionArgs, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        void* modelContainerPtr          = nullptr;
        uint8_t* selectedTypePtr         = nullptr;
        EntityID* selectedEntityPtr      = nullptr;
        void* selectedEntitySimulatorPtr = nullptr;
        if (entitySelectionArgs)
        {
            modelContainerPtr = entitySelectionArgs->Model.CorePtr();
            selectedTypePtr   = reinterpret_cast<uint8_t*>(&entitySelectionArgs->Type);
            selectedEntityPtr = &entitySelectionArgs->SelectedEntity;
            selectedEntitySimulatorPtr =
                entitySelectionArgs->SelectedEntitySimulator ? entitySelectionArgs->SelectedEntitySimulator->CorePtr() : nullptr;
        }
        const uint8_t* selectedTypePtrOrig         = selectedTypePtr;
        const EntityID* selectedEntityPtrOrig      = selectedEntityPtr;
        const void* selectedEntitySimulatorPtrOrig = selectedEntitySimulatorPtr;

        Ers::Engine::ERS_VisualizationWidget_Window(
            corePtr, renderContext.CorePtr(), &modelContainerPtr, &selectedTypePtr, &selectedEntityPtr, &selectedEntitySimulatorPtr, name,
            open, flags);

        if (selectedTypePtr != selectedTypePtrOrig)
            entitySelectionArgs->Type = *reinterpret_cast<Ers::SelectedType*>(selectedTypePtr);
        if (selectedEntityPtr != selectedEntityPtrOrig)
            entitySelectionArgs->SelectedEntity = *selectedEntityPtr;
        if (selectedEntitySimulatorPtr != selectedEntitySimulatorPtrOrig)
        {
            if (entitySelectionArgs->SelectedEntitySimulator != nullptr)
                delete entitySelectionArgs->SelectedEntitySimulator;

            entitySelectionArgs->SelectedEntitySimulator = new Ers::Simulator(selectedEntitySimulatorPtr);
        }
    }

    void VisualizationWidget::BeginWindow(RenderContext& renderContext, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_VisualizationWidget_BeginWindow(corePtr, renderContext.CorePtr(), name, open, flags);
    }

    void VisualizationWidget::EndWindow()
    {
        Ers::Engine::ERS_VisualizationWidget_EndWindow(corePtr);
    }

    void VisualizationWidget::Widget(RenderContext& renderContext, EntitySelectionArgs* entitySelectionArgs)
    {
        void* modelContainerPtr          = nullptr;
        uint8_t* selectedTypePtr         = nullptr;
        EntityID* selectedEntityPtr      = nullptr;
        void* selectedEntitySimulatorPtr = nullptr;
        if (entitySelectionArgs)
        {
            modelContainerPtr = entitySelectionArgs->Model.CorePtr();
            selectedTypePtr   = reinterpret_cast<uint8_t*>(&entitySelectionArgs->Type);
            selectedEntityPtr = &entitySelectionArgs->SelectedEntity;
            selectedEntitySimulatorPtr =
                entitySelectionArgs->SelectedEntitySimulator ? entitySelectionArgs->SelectedEntitySimulator->CorePtr() : nullptr;
        }
        const uint8_t* selectedTypePtrOrig         = selectedTypePtr;
        const EntityID* selectedEntityPtrOrig      = selectedEntityPtr;
        const void* selectedEntitySimulatorPtrOrig = selectedEntitySimulatorPtr;

        Ers::Engine::ERS_VisualizationWidget_Widget(
            corePtr, renderContext.CorePtr(), &modelContainerPtr, &selectedTypePtr, &selectedEntityPtr, &selectedEntitySimulatorPtr);

        if (selectedTypePtr != selectedTypePtrOrig)
            entitySelectionArgs->Type = *reinterpret_cast<Ers::SelectedType*>(selectedTypePtr);
        if (selectedEntityPtr != selectedEntityPtrOrig)
            entitySelectionArgs->SelectedEntity = *selectedEntityPtr;
        if (selectedEntitySimulatorPtr != selectedEntitySimulatorPtrOrig)
        {
            if (entitySelectionArgs->SelectedEntitySimulator != nullptr)
                delete entitySelectionArgs->SelectedEntitySimulator;

            entitySelectionArgs->SelectedEntitySimulator = new Ers::Simulator(selectedEntitySimulatorPtr);
        }
    }
} // namespace Ers
