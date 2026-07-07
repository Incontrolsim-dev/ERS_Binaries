#include "ChannelComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t ChannelComponent::CoreTypeId()
    {
        return Ers::Engine::ERS_ChannelComponent_TypeId();
    }

    ChannelType ChannelComponent::GetType() const
    {
        return static_cast<ChannelType>(Ers::Engine::ERS_ChannelComponent_GetType(const_cast<ChannelComponent*>(this)));
    }

    Entity ChannelComponent::GetConnectedTo() const
    {
        return Ers::Engine::ERS_ChannelComponent_GetConnectedTo(const_cast<ChannelComponent*>(this));
    }

    bool ChannelComponent::IsOpen() const
    {
        return Ers::Engine::ERS_ChannelComponent_IsOpen(const_cast<ChannelComponent*>(this));
    }

    bool ChannelComponent::IsOpen(EntityID channel)
    {
        return Ers::Engine::ERS_ChannelComponent_IsOpenStatic(channel);
    }

    bool ChannelComponent::Send(Entity channelFrom, Entity child)
    {
        return Ers::Engine::ERS_Channel_Send(channelFrom, child);
    }

    void ChannelComponent::Open(Entity channel)
    {
        Ers::Engine::ERS_Channel_Open(channel);
    }

    void ChannelComponent::Close(Entity channel)
    {
        Ers::Engine::ERS_Channel_Close(channel);
    }

    bool ChannelComponent::IsReady(Entity channel)
    {
        return Ers::Engine::ERS_Channel_IsReady(channel);
    }

    void ChannelComponent::Connect(Entity input, Entity output)
    {
        Ers::Engine::ERS_Channel_Connect(input, output);
    }

    void ChannelComponent::AddChannelComponent(Entity channel, ChannelType type, Entity resource)
    {
        Ers::Engine::ERS_Channel_AddChannelComponent(channel, static_cast<int>(type), resource);
    }
} // namespace Ers
