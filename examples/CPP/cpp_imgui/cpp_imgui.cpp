#include <format>
#include <string>

#include "Ers/Api.h"
#include "Ers/Debugging/Debugger.h"
#include "Ers/Logger.h"
#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/Model/ModelContainer.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/Entity.h"
#include "Ers/SubModel/EventScheduler.h"
#include "Ers/SubModel/PersistentEvent.h"
#include "Ers/Systems/RenderSystem.h"
#include "Ers/UI/ErsImGui.h"
#include "Ers/UI/Widgets/EventTimelineWidget.h"
#include "Ers/UI/Widgets/InspectorWidget.h"
#include "Ers/UI/Widgets/LicensingWidget.h"
#include "Ers/UI/Widgets/LogWidget.h"
#include "Ers/UI/Widgets/ModelHierarchyWidget.h"
#include "Ers/UI/Widgets/ModelProgressionWidget.h"
#include "Ers/UI/Widgets/ModelStructureWidget.h"
#include "Ers/UI/Widgets/RunControlsWidget.h"
#include "Ers/UI/Widgets/VisualizationWidget.h"
#include "Ers/UI/Widgets/WidgetTypes.h"
#include "Ers/UI/Window.h"
#include "Ers/Visualization/RenderContext.h"

#include "Ers/External/ImGuiCpp.hpp"
#include "Ers/External/ImPlotCpp.hpp"

class CustomDebugger
{
  public:
    CustomDebugger() = delete;
    CustomDebugger(ModelContainer& modelContainer_) :
        modelContainer(modelContainer_),
        window("Custom Debugger"),
        renderContext(640, 480)
    {
        StyleColorsErsLight();
    }

    void BeginDockSpace()
    {
        if (window.BeginRootDockSpace())
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGuiID rootDockSpaceID = window.GetRootDockSpaceID();

            // Optional named IDs so the nodes can be retrieved by name later
            ImGuiID topBarDockID       = ImGui::GetID("CustomDebugger_TopBarDock");
            ImGuiID mainDockID         = ImGui::GetID("CustomDebugger_MainDock");
            ImGuiID leftSidebarDockID  = ImGui::GetID("CustomDebugger_LeftSidebarDock");
            ImGuiID centerDockID       = ImGui::GetID("CustomDebugger_CenterDock");
            ImGuiID rightSidebarDockID = ImGui::GetID("CustomDebugger_RightSidebarDock");
            ImGuiID centerMainDockID   = ImGui::GetID("CustomDebugger_CenterMainDock");
            ImGuiID centerBottomDockID = ImGui::GetID("CustomDebugger_CenterBottomDock");

            // Create a full-width top bar for Run Controls, and the rest below
            ImGuiStyle& style       = ImGui::GetStyle();
            const float topHeightPx = ImGui::GetFrameHeight() + style.ItemSpacing.y + 4.0f;
            const float vpHeight    = viewport->Size.y;
            float topRatio          = topHeightPx / (vpHeight > 1.0f ? vpHeight : 800.0f);
            topRatio                = EClamp(topRatio, 0.02f, 0.08f);
            ImGui::DockBuilderSplitNode(rootDockSpaceID, ImGuiDir_Up, topRatio, &topBarDockID, &mainDockID);

            // Lock top bar (no tab bar, no split/resize/undock)
            if (ImGuiDockNode* topNode = ImGui::DockBuilderGetNode(topBarDockID))
            {
                topNode->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
                topNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingSplit;
                topNode->LocalFlags |= ImGuiDockNodeFlags_NoResize;
                topNode->LocalFlags |= ImGuiDockNodeFlags_NoDockingOverMe;
                topNode->LocalFlags |= ImGuiDockNodeFlags_NoUndocking;
            }

            // Below: left sidebar, center, right sidebar
            ImGui::DockBuilderSplitNode(mainDockID, ImGuiDir_Left, 0.10f, &leftSidebarDockID, &centerDockID);
            ImGui::DockBuilderSplitNode(centerDockID, ImGuiDir_Right, 0.10f / 0.90f, &rightSidebarDockID, &centerDockID);

            // Main
            ImGui::DockBuilderSplitNode(centerDockID, ImGuiDir_Up, 0.75f, &centerMainDockID, &centerBottomDockID);

            // Top bar
            ImGui::DockBuilderDockWindow("Run Controls", topBarDockID);
            // Left sidebar
            ImGui::DockBuilderDockWindow("Model Hierarchy", leftSidebarDockID);
            // Right sidebar
            ImGui::DockBuilderDockWindow("Inspector", rightSidebarDockID);
            // Main
            ImGui::DockBuilderDockWindow("Visualization", centerMainDockID);
            ImGui::DockBuilderDockWindow("Model Structure", centerMainDockID);
            ImGui::DockBuilderDockWindow("License Manager", centerMainDockID);
            // Main-Bottom
            ImGui::DockBuilderDockWindow("Log", centerBottomDockID);
            ImGui::DockBuilderDockWindow("Event Timeline", centerBottomDockID);
            ImGui::DockBuilderDockWindow("Model Progression", centerBottomDockID);

            ImGui::DockBuilderFinish(rootDockSpaceID);

            // Persist the generated layout once
            if (ImGui::GetIO().IniFilename && *ImGui::GetIO().IniFilename)
            {
                ImGui::SaveIniSettingsToDisk(ImGui::GetIO().IniFilename);
            }
        }
    }

    void EndDockSpace() { window.EndRootDockSpace(); }

    void CustomWidget()
    {
        ImGui::Begin("Test window");

        // ImGui
        ImGui::SeparatorText("ImGui");
        ImGui::Text("Hello World!");

        // ImPlot
        ImGui::SeparatorText("ImPlot");
        const int barData[5] = {1, 2, 3, 4, 5};

        if (ImPlot::BeginPlot("Plot1"))
        {
            ImPlot::PlotBars("Bar plot", barData, 5);
            ImPlot::EndPlot();
        }

        const bool switchResult = Ers::SwitchButton("Test SwitchButton", switchValue);
        if (switchResult)
        {
            const std::string msg = std::format("Switch: {}", switchValue);
            Ers::Logger::Warning(msg.c_str());
        }

        const bool xyzResult = Ers::DragVectorXYZ("Test DragVectorXYZ", vectorValue);
        if (xyzResult)
        {
            const std::string msg = std::format("XYZ: {}, {}, {}", vectorValue.X, vectorValue.Y, vectorValue.Z);
            Ers::Logger::Info(msg.c_str());
        }

        ImGui::End();
    }

    void Update()
    {
        window.BeginFrame();
        BeginDockSpace();
        const bool is3DMode = visualization.GetIs3DMode();
        if (is3DMode)
            renderContext.Begin3D();
        else
            renderContext.Begin2D();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    window.WantsClose(true);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        runControls.Window(modelContainer, isRunning, "Run Controls");
        logWidget.Window("Log");
        if (eventTimeline.Window(modelContainer, selectedEvent, isRunning, "Event Timeline"))
        {
            selectedType = Ers::SelectedType::Event;
        }
        modelHierarchy.Window(modelContainer, selectedSimulator, selectedSimulator, selectedEntity, selectedType, "Model Hierarchy");
        inspector.Window(selectedType, modelContainer, selectedSimulator, selectedSimulator, selectedEntity, selectedEvent, "Inspector");
        visualization.Window(renderContext, "Visualization");
        modelStructure.Window(modelContainer, "Model Structure");
        modelProgression.Window(modelContainer, "Model Progression");
        licensing.Window("Licensing Manager");

        CustomWidget();

        if (is3DMode)
            renderContext.End3D();
        else
            renderContext.End2D();
        EndDockSpace();
        window.EndFrame();
    }

    Ers::Window window;

  private:
    Ers::ModelContainer& modelContainer;
    Ers::RenderContext renderContext;

    bool isRunning                    = false;
    Ers::SelectedType selectedType    = Ers::SelectedType::None;
    Ers::Simulator* selectedSimulator = nullptr;
    EntityID selectedEntity           = Ers::Entity::InvalidEntity;
    Ers::PersistentEvent selectedEvent;

    Ers::RunControlsWidget runControls;
    Ers::LogWidget logWidget;
    Ers::EventTimelineWidget eventTimeline;
    Ers::ModelHierarchyWidget modelHierarchy;
    Ers::InspectorWidget inspector;
    Ers::VisualizationWidget visualization;
    Ers::ModelStructureWidget modelStructure;
    Ers::ModelProgressionWidget modelProgression;
    Ers::LicensingWidget licensing;

    bool switchValue         = false;
    Ers::Vector3 vectorValue = Ers::Vec3(1, 2, 3);
};

struct SomeEvent
{
    void OnEvent()
    {
        Ers::Logger::Info("Executed some event");
        Ers::EventScheduler::ScheduleLocalEvent(0, 10 * Ers::SubModel::Get().GetModelPrecision(), SomeEvent());
    }

    ERS_EVENT()
};

int main()
{
    Ers::Initialize();

    Ers::LocalEventRegistry<SomeEvent>::Register();

    Ers::ModelContainer modelContainer = Ers::ModelContainer::Create();
    Ers::Simulator sim                 = modelContainer.AddSimulator("Sim", Ers::SimulatorType::DiscreteEvent);
    sim.EnterSubModel();
    Ers::EventScheduler::ScheduleLocalEvent(0, 10 * Ers::SubModel::Get().GetModelPrecision(), SomeEvent());
    sim.ExitSubModel();

    CustomDebugger debugger(modelContainer);
    while (!debugger.window.WantsClose())
    {
        debugger.Update();
    }

    Ers::Uninitialize();
    return 0;
}
