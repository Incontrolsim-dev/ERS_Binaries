#include "ModelStructureWidget.h"

#include "Ers/Api.h"

namespace Ers
{
    ModelStructureWidget::ModelStructureWidget()
    {
        corePtr = Ers::Engine::ERS_ModelStructureWidget_Create();
    }

    ModelStructureWidget::~ModelStructureWidget()
    {
        Ers::Engine::ERS_ModelStructureWidget_Destroy(corePtr);
    }

    bool ModelStructureWidget::GetShowGrid() const
    {
        return Ers::Engine::ERS_ModelStructureWidget_Get_ShowGrid(corePtr);
    }

    void ModelStructureWidget::SetShowGrid(bool value)
    {
        Ers::Engine::ERS_ModelStructureWidget_Set_ShowGrid(corePtr, value);
    }

    ModelStructureWidget::HeatMapMode ModelStructureWidget::GetSelectedHeatMapMode() const
    {
        return static_cast<ModelStructureWidget::HeatMapMode>(Ers::Engine::ERS_ModelStructureWidget_Get_SelectedHeatMapMode(corePtr));
    }

    void ModelStructureWidget::SetSelectedHeatMapMode(ModelStructureWidget::HeatMapMode mode)
    {
        Ers::Engine::ERS_ModelStructureWidget_Set_SelectedHeatMapMode(corePtr, static_cast<int>(mode));
    }

    bool ModelStructureWidget::GetShowSimulatorGroups() const
    {
        return Ers::Engine::ERS_ModelStructureWidget_Get_ShowSimulatorGroups(corePtr);
    }

    void ModelStructureWidget::SetShowSimulatorGroups(bool value)
    {
        Ers::Engine::ERS_ModelStructureWidget_Set_ShowSimulatorGroups(corePtr, value);
    }

    bool ModelStructureWidget::GetShowSimulatorSuperGroups() const
    {
        return Ers::Engine::ERS_ModelStructureWidget_Get_ShowSimulatorSuperGroups(corePtr);
    }

    void ModelStructureWidget::SetShowSimulatorSuperGroups(bool value)
    {
        Ers::Engine::ERS_ModelStructureWidget_Set_ShowSimulatorSuperGroups(corePtr, value);
    }

    ModelStructureWidget::GroupStyle ModelStructureWidget::GetSelectedGroupStyle() const
    {
        return static_cast<ModelStructureWidget::GroupStyle>(Ers::Engine::ERS_ModelStructureWidget_Get_SelectedGroupStyle(corePtr));
    }

    void ModelStructureWidget::SetSelectedGroupStyle(ModelStructureWidget::GroupStyle style)
    {
        Ers::Engine::ERS_ModelStructureWidget_Set_SelectedGroupStyle(corePtr, static_cast<int>(style));
    }

    void ModelStructureWidget::Window(ModelContainer& modelContainer, const char* name, bool* open, ImGuiWindowFlags flags)
    {
        Ers::Engine::ERS_ModelStructureWidget_Window(corePtr, modelContainer.CorePtr(), name, open, flags);
    }

    void ModelStructureWidget::Widget(ModelContainer& modelContainer, ModelStructureWidget::HeatMapMode heatMapMode)
    {
        Ers::Engine::ERS_ModelStructureWidget_Widget(corePtr, modelContainer.CorePtr(), static_cast<int>(heatMapMode));
    }
} // namespace Ers
