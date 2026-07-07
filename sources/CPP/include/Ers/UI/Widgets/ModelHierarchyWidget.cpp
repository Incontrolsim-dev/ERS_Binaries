#include "ModelHierarchyWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    ModelHierarchyWidget::ModelHierarchyWidget()
    {
        corePtr = Ers::Engine::ERS_ModelHierarchyWidget_Create();
    }

    ModelHierarchyWidget::~ModelHierarchyWidget()
    {
        Ers::Engine::ERS_ModelHierarchyWidget_Destroy(corePtr);
    }

    bool ModelHierarchyWidget::Window(
        ModelContainer& modelContainer,
        Simulator*& selectedSimulator,
        Simulator*& selectedEntitySimulator,
        EntityID& selectedEntity,
        SelectedType& selectedType,
        const char* name,
        bool* open,
        ImGuiWindowFlags flags)
    {
        void* selectedSimulatorPtr                 = selectedSimulator ? selectedSimulator->CorePtr() : nullptr;
        void* selectedEntitySimulatorPtr           = selectedEntitySimulator ? selectedEntitySimulator->CorePtr() : nullptr;
        const void* selectedSimulatorPtrOrig       = selectedSimulatorPtr;
        const void* selectedEntitySimulatorPtrOrig = selectedEntitySimulatorPtr;
        uint8_t selectedTypeInt                    = static_cast<uint8_t>(selectedType);
        const bool result                          = Ers::Engine::ERS_ModelHierarchyWidget_Window(
            corePtr, modelContainer.CorePtr(), &selectedSimulatorPtr, &selectedEntitySimulatorPtr, &selectedEntity, &selectedTypeInt, name,
            open, flags);
        selectedType = static_cast<SelectedType>(selectedTypeInt);
        // Replace selected simulator when a new one is selected
        if (selectedSimulatorPtr && selectedSimulatorPtr != selectedSimulatorPtrOrig)
        {
            if (selectedSimulator != nullptr)
                delete selectedSimulator;

            selectedSimulator = new Simulator(selectedSimulatorPtr);
        }
        // Replace selected entity simulator when a new one is selected
        if (selectedEntitySimulatorPtr && selectedEntitySimulatorPtr != selectedEntitySimulatorPtrOrig)
        {
            if (selectedEntitySimulator != nullptr)
                delete selectedEntitySimulator;

            selectedEntitySimulator = new Simulator(selectedEntitySimulatorPtr);
        }
        return result;
    }

    bool ModelHierarchyWidget::Widget(
        ModelContainer& modelContainer,
        ImGuiTreeNodeFlags treeNodeFlags,
        Simulator*& selectedSimulator,
        Simulator*& selectedEntitySimulator,
        EntityID& selectedEntity,
        SelectedType& selectedType)
    {
        void* selectedSimulatorPtr                 = selectedSimulator ? selectedSimulator->CorePtr() : nullptr;
        void* selectedEntitySimulatorPtr           = selectedEntitySimulator ? selectedEntitySimulator->CorePtr() : nullptr;
        const void* selectedSimulatorPtrOrig       = selectedSimulatorPtr;
        const void* selectedEntitySimulatorPtrOrig = selectedEntitySimulatorPtr;
        uint8_t selectedTypeInt                    = static_cast<uint8_t>(selectedType);
        const bool result                          = Ers::Engine::ERS_ModelHierarchyWidget_Widget(
            modelContainer.CorePtr(), treeNodeFlags, &selectedSimulatorPtr, &selectedEntitySimulatorPtr, &selectedEntity, &selectedTypeInt);
        selectedType = static_cast<SelectedType>(selectedTypeInt);
        // Replace selected simulator when a new one is selected
        if (selectedSimulatorPtr && selectedSimulatorPtr != selectedSimulatorPtrOrig)
        {
            if (selectedSimulator != nullptr)
                delete selectedSimulator;

            selectedSimulator = new Simulator(selectedSimulatorPtr);
        }
        // Replace selected entity simulator when a new one is selected
        if (selectedEntitySimulatorPtr && selectedEntitySimulatorPtr != selectedEntitySimulatorPtrOrig)
        {
            if (selectedEntitySimulator != nullptr)
                delete selectedEntitySimulator;

            selectedEntitySimulator = new Simulator(selectedSimulatorPtr);
        }
        return result;
    }

    void ModelHierarchyWidget::Widget(ModelContainer& modelContainer, ImGuiTreeNodeFlags treeNodeFlags)
    {
        Ers::Engine::ERS_ModelHierarchyWidget_Widget(modelContainer.CorePtr(), treeNodeFlags, nullptr, nullptr, nullptr, 0);
    }
} // namespace Ers
