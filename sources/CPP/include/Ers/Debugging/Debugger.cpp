#include "Debugger.h"

#include "Ers/Api.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"
#include "Ers/Systems/PathAnimationSystem.h"
#include "Ers/Systems/RenderSystem.h"
#include "Ers/Systems/TransformSystem.h"

namespace Ers
{
    Debugger::Debugger(Ers::ModelContainer& modelContainer)
    {
        corePtr = Ers::Engine::ERS_Debugger_Create(modelContainer.CorePtr());
    }

    Debugger::Debugger(ModelContainer& modelContainer, Window& window)
    {
        corePtr = Ers::Engine::ERS_Debugger_Create_Window(modelContainer.CorePtr(), window.CorePtr());
    }

    Debugger::~Debugger()
    {
        Ers::Engine::ERS_Debugger_Destroy(corePtr);
    }

    Window Debugger::GetWindow()
    {
        return Window(Ers::Engine::ERS_Debugger_GetWindow(corePtr));
    }

    Ers::RenderContext Debugger::GetRenderContext()
    {
        return Ers::RenderContext(Ers::Engine::ERS_Debugger_GetRenderContext(corePtr));
    }

    bool Debugger::IsRunning() const
    {
        return Ers::Engine::ERS_Debugger_Get_IsRunning(corePtr);
    }

    void Debugger::IsRunning(bool value)
    {
        Ers::Engine::ERS_Debugger_Set_IsRunning(corePtr, value);
    }

    bool Debugger::Is3DMode() const
    {
        return Ers::Engine::ERS_Debugger_Is3DMode(corePtr);
    }

    void Debugger::BeginUpdate()
    {
        Ers::Engine::ERS_Debugger_BeginUpdate(corePtr);
    }

    void Debugger::EndUpdate()
    {
        Ers::Engine::ERS_Debugger_EndUpdate(corePtr);
    }

    void Debugger::Open()
    {
        if (!runWindow)
            runWindow = new Window(windowTitle);
    }

    void Debugger::Run(
        ModelContainer& modelContainer,
        const std::function<void(Ers::Debugger&, Ers::Simulator&)>& render2D,
        const std::function<void(Ers::Debugger&, Ers::Simulator&)>& render3D,
        const std::function<void(Ers::Debugger&)>& renderUI)
    {
        if (runWindow == nullptr)
            runWindow = new Window(windowTitle);

        Debugger debugger(modelContainer, *runWindow);
        Window window = debugger.GetWindow();

        while (!window.WantsClose())
        {
            window.BeginFrame();
            debugger.BeginUpdate();

            Ers::RenderContext renderContext = debugger.GetRenderContext();

            if (debugger.Is3DMode())
            {
                renderContext.Begin3D();
            }
            else
            {
                renderContext.Begin2D();
            }

            for (size_t i = 0; i < modelContainer.SimulatorCount(); i++)
            {
                Simulator simulator = modelContainer.GetSimulatorByIndex(i);

                simulator.EnterSubModel();
                PathAnimationSystem::Update(simulator.CurrentTime());
                TransformSystem::UpdateGlobals(SubModel::Get());
                simulator.ExitSubModel();

                if (debugger.Is3DMode())
                {
                    // 3D rendering
                    simulator.EnterSubModel();
                    SubModel& subModel3D = SubModel::Get();

                    if (render3D != nullptr)
                        render3D(debugger, simulator);
                    else
                        RenderSystem::Render3D(subModel3D, renderContext);

                    simulator.ExitSubModel();
                }
                else
                {
                    // 2D rendering
                    simulator.EnterSubModel();
                    SubModel& subModel2D = SubModel::Get();

                    if (render2D != nullptr)
                        render2D(debugger, simulator);
                    else
                        RenderSystem::Render2D(subModel2D, renderContext);

                    simulator.ExitSubModel();
                }
            }

            if (debugger.Is3DMode())
                renderContext.End3D();
            else
                renderContext.End2D();

            if (renderUI)
                renderUI(debugger);

            debugger.EndUpdate();
            window.EndFrame();
        }
    }
} // namespace Ers
