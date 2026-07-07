#include "RenderSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    void RenderSystem::Render2D(SubModel& subModel, Ers::RenderContext& renderContext)
    {
        Ers::Engine::ERS_RenderSystem_Render2D(subModel.CorePtr(), renderContext.CorePtr());
    }

    void RenderSystem::Render3D(SubModel& subModel, Ers::RenderContext& renderContext)
    {
        Ers::Engine::ERS_RenderSystem_Render3D(subModel.CorePtr(), renderContext.CorePtr());
    }
} // namespace Ers
