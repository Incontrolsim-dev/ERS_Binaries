#include "RenderComponent.h"

#include "Ers/Api.h"

namespace Ers
{
    uint32_t RenderComponent::CoreTypeId()
    {
        return Ers::Engine::ERS_RenderComponent_TypeId();
    }

    RenderComponentShape RenderComponent::GetShape()
    {
        return static_cast<RenderComponentShape>(Ers::Engine::ERS_RenderComponent_GetShape(this));
    }

    void RenderComponent::SetShape(RenderComponentShape shape)
    {
        Ers::Engine::ERS_RenderComponent_SetShape(this, static_cast<uint8_t>(shape));
    }

    Color RenderComponent::GetColor() const
    {
        return Color::FromInt(Ers::Engine::ERS_RenderComponent_GetColor(const_cast<RenderComponent*>(this)));
    }

    void RenderComponent::SetColor(Ers::Color color)
    {
        Ers::Engine::ERS_RenderComponent_SetColor(this, color.Value);
    }

    Ers::Texture* RenderComponent::GetTexture2D()
    {
        return static_cast<Ers::Texture*>(Ers::Engine::ERS_RenderComponent_GetTexture2D(this));
    }

    void RenderComponent::SetTexture2D(const Ers::Texture& texture)
    {
        Ers::Engine::ERS_RenderComponent_SetTexture2D(this, const_cast<void*>(texture.CorePtr()));
    }

    void RenderComponent::RemoveTexture2D()
    {
        Ers::Engine::ERS_RenderComponent_RemoveTexture2D(this);
    }

    Ers::InstancedModel* RenderComponent::GetInstancedModel()
    {
        void* ptr = Ers::Engine::ERS_RenderComponent_GetInstancedModel(this);
        return static_cast<Ers::InstancedModel*>(ptr);
    }

    void RenderComponent::SetInstancedModel(const Ers::InstancedModel& model)
    {
        Ers::Engine::ERS_RenderComponent_SetInstancedModel(this, const_cast<void*>(model.CorePtr()));
    }
} // namespace Ers
