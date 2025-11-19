#include "BasicRenderSystem.h"

#include "Ers/Api.h"

namespace Ers
{
    void BasicRenderSystem::Render2D(SubModel& subModel, Ers::RenderContext& renderContext)
    {
        ersAPIFunctionPointers.ERS_BasicRenderSystem_Render2D(subModel.Data(), renderContext.Data());
    }

    void BasicRenderSystem::Render3D(SubModel& subModel, Ers::RenderContext& renderContext)
    {
        ersAPIFunctionPointers.ERS_BasicRenderSystem_Render3D(subModel.Data(), renderContext.Data());
    }
} // namespace Ers
