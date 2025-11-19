#include "Debugger.h"

#include "Ers/Api.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"
#include "Ers/Systems/BasicRenderSystem.h"
#include "Ers/Systems/PathAnimationSystem.h"
#include "Ers/Systems/TransformSystem.h"

namespace Ers
{
    Platform* Debugger::platform = nullptr;

    Debugger::Debugger(Ers::ModelContainer& modelContainer)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Debugger_Create(modelContainer.Data());
    }

    Debugger::~Debugger()
    {
        ersAPIFunctionPointers.ERS_Debugger_Destroy(coreInstance);
    }

    Ers::RenderContext Debugger::GetRenderContext()
    {
        return Ers::RenderContext(ersAPIFunctionPointers.ERS_Debugger_GetRenderContext(coreInstance));
    }

    bool Debugger::Is3DMode() const
    {
        return ersAPIFunctionPointers.ERS_Debugger_Is3DMode(coreInstance);
    }

    bool Debugger::ShowBackgroundGrid() const
    {
        return ersAPIFunctionPointers.ERS_Debugger_ShowBackgroundGrid(coreInstance);
    }

    void Debugger::Update()
    {
        ersAPIFunctionPointers.ERS_Debugger_Update(coreInstance);
    }

    void Debugger::Open()
    {
        platform = new Platform();
    }

    void Debugger::Run(
        ModelContainer& modelContainer,
        const std::function<void(Ers::RenderContext&)>& render2D,
        const std::function<void(Ers::RenderContext&)>& render3D)
    {
        if (platform == nullptr)
            platform = new Platform();

        Debugger debugger(modelContainer);

        Simulator simulator = modelContainer.GetSimulatorByIndex(0);

        Color gridColor = Ers::Color::FromFloats(0.8f, 0.8f, 0.8f);
        while (!platform->WantsClose())
        {
            platform->BeginFrame();

            simulator.EnterSubModel();
            PathAnimationSystem::Update(simulator.CurrentTime());
            TransformSystem::UpdateGlobals(GetSubModel());
            simulator.ExitSubModel();

            Ers::RenderContext renderContext = debugger.GetRenderContext();
            if (debugger.Is3DMode())
            {
                // 3D rendering
                simulator.EnterSubModel();
                SubModel& subModel3D = GetSubModel();
                renderContext.Begin3D();

                if (debugger.ShowBackgroundGrid())
                {
                    renderContext.DrawInfiniteGrid3D(gridColor);
                }
                if (render3D != nullptr)
                    render3D(renderContext);
                else
                    BasicRenderSystem::Render3D(subModel3D, renderContext);

                renderContext.End3D();
                simulator.ExitSubModel();
            }
            else
            {
                // 2D rendering
                simulator.EnterSubModel();
                SubModel& subModel2D = GetSubModel();
                renderContext.Begin2D();

                if (debugger.ShowBackgroundGrid())
                {
                    renderContext.DrawInfiniteGrid2D(gridColor);
                }
                if (render2D != nullptr)
                    render2D(renderContext);
                else
                    BasicRenderSystem::Render2D(subModel2D, renderContext);

                renderContext.End2D();
                simulator.ExitSubModel();
            }

            debugger.Update();
            platform->EndFrame();
        }
    }
} // namespace Ers
