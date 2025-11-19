#include "BasicRenderComponent.h"
#include "Ers/Api.h"
#include "Ers/Visualization/InstancedModel.h"

namespace Ers
{
    uint32_t BasicRenderComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_BasicRenderComponent_TypeId();
    }

    Color BasicRenderComponent::GetColor() const
    {
        return Color::FromInt(ersAPIFunctionPointers.ERS_BasicRenderComponent_GetColor(const_cast<BasicRenderComponent*>(this)));
    }

    void BasicRenderComponent::SetColor(Ers::Color color)
    {
        ersAPIFunctionPointers.ERS_BasicRenderComponent_SetColor(this, color.Value);
    }

    Ers::InstancedModel* BasicRenderComponent::GetInstancedModel()
    {
        void* ptr = ersAPIFunctionPointers.ERS_BasicRenderComponent_GetInstancedModel(this);
        return static_cast<Ers::InstancedModel*>(ptr);
    }

    void BasicRenderComponent::SetInstancedModel(Ers::InstancedModel* model)
    {
        ersAPIFunctionPointers.ERS_BasicRenderComponent_SetInstancedModel(this, model);
    }
} // namespace Ers
