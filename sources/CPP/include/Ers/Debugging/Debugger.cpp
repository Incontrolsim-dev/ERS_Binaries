#include "Debugger.h"

#include "Ers/Api.h"
#include "Ers/Debugging/Platform.h"
#include "Ers/Model/Simulator/Simulator.h"
#include "Ers/SubModel/SubModel.h"
#include "Ers/Systems/BasicRenderSystem.h"
#include "Ers/Systems/PathAnimationSystem.h"
#include "Ers/Systems/TransformSystem.h"

namespace Ers
{
    Debugger::Debugger(Ers::ModelContainer& modelContainer)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Debugger_Create(modelContainer.Data());
    }

    Debugger::~Debugger()
    {
        ersAPIFunctionPointers.ERS_Debugger_Destroy(coreInstance);
    }

    Ers::Visualization::RenderContext Debugger::GetRenderContext()
    {
        return Ers::Visualization::RenderContext(ersAPIFunctionPointers.ERS_Debugger_GetRenderContext(coreInstance));
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

    void Debugger::Run(
        ModelContainer& modelContainer,
        const std::function<void(Ers::Visualization::RenderContext&)>& render2D,
        const std::function<void(Ers::Visualization::RenderContext&)>& render3D)
    {
        Platform platform;
        Debugger debugger(modelContainer);

        Simulator simulator = modelContainer.GetSimulatorByIndex(0);

        while (!platform.WantsClose())
        {
            platform.BeginFrame();

            simulator.EnterSubModel();
            PathAnimationSystem::Update(simulator.CurrentTime());
            TransformSystem::UpdateGlobals(GetSubModel());
            simulator.ExitSubModel();

            Ers::Visualization::RenderContext renderContext = debugger.GetRenderContext();
            if (debugger.Is3DMode())
            {
                // 3D rendering
                simulator.EnterSubModel();
                SubModel& subModel3D = GetSubModel();
                renderContext.Begin3D();

                if (debugger.ShowBackgroundGrid())
                {
                    renderContext.DrawInfiniteGrid3D(0.8f, 0.8f, 0.8f);
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
                    renderContext.DrawInfiniteGrid2D(0.8f, 0.8f, 0.8f);
                }
                if (render2D != nullptr)
                    render2D(renderContext);
                else
                    BasicRenderSystem::Render2D(subModel2D, renderContext);

                renderContext.End2D();
                simulator.ExitSubModel();
            }

            platform.EndFrame();
        }
    }
} // namespace Ers
