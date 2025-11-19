#include "RenderComponent.h"
#include "Ers/Api.h"
#include "Ers/Visualization/InstancedModel.h"

namespace Ers
{
    uint32_t RenderComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_BasicRenderComponent_TypeId();
    }

    Ers::Color RenderComponent::GetColor() const
    {
        return Ers::Color::FromInt(ersAPIFunctionPointers.ERS_BasicRenderComponent_GetColor(const_cast<RenderComponent*>(this)));
    }

    void RenderComponent::SetColor(Ers::Color color)
    {
        ersAPIFunctionPointers.ERS_BasicRenderComponent_SetColor(this, color.Value);
    }

    Ers::InstancedModel* RenderComponent::GetInstancedModel()
    {
        void* ptr = ersAPIFunctionPointers.ERS_BasicRenderComponent_GetInstancedModel(this);
        return static_cast<Ers::InstancedModel*>(ptr);
    }

    void RenderComponent::SetInstancedModel(Ers::InstancedModel* model)
    {
        ersAPIFunctionPointers.ERS_BasicRenderComponent_SetInstancedModel(this, model);
    }
} // namespace Ers
