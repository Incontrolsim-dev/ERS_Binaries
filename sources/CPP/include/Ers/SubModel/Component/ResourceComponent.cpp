#include "ResourceComponent.h"
#include "Ers/Api.h"
#include "Ers/SubModel/Component/ChannelComponent.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    uint32_t ResourceComponent::CoreTypeId()
    {
        return Ers::Engine::ERS_ResourceComponent_TypeId();
    }

    int ResourceComponent::GetNumInputChannels() const
    {
        return static_cast<int>(Ers::Engine::ERS_ResourceComponent_GetNumInputChannels(const_cast<ResourceComponent*>(this)));
    }

    int ResourceComponent::GetNumOutputChannels() const
    {
        return static_cast<int>(Ers::Engine::ERS_ResourceComponent_GetNumOutputChannels(const_cast<ResourceComponent*>(this)));
    }

    Entity ResourceComponent::GetInputChannel(int index) const
    {
        return Ers::Engine::ERS_ResourceComponent_GetInputChannel(const_cast<ResourceComponent*>(this), static_cast<size_t>(index));
    }

    Entity ResourceComponent::GetOutputChannel(int index) const
    {
        return Ers::Engine::ERS_ResourceComponent_GetOutputChannel(const_cast<ResourceComponent*>(this), static_cast<size_t>(index));
    }

    void ResourceComponent::CloseAllInput() const
    {
        Ers::Engine::ERS_ResourceComponent_CloseAllInput(const_cast<ResourceComponent*>(this));
    }

    void ResourceComponent::OpenAllInput() const
    {
        Ers::Engine::ERS_ResourceComponent_OpenAllInput(const_cast<ResourceComponent*>(this));
    }

    void ResourceComponent::CloseAllOuput() const
    {
        Ers::Engine::ERS_ResourceComponent_CloseAllOutput(const_cast<ResourceComponent*>(this));
    }

    void ResourceComponent::OpenAllOutput() const
    {
        Ers::Engine::ERS_ResourceComponent_OpenAllOutput(const_cast<ResourceComponent*>(this));
    }

    ResourceComponent::ChannelRange ResourceComponent::InputChannels(EntityID resourceEntity)
    {
        Ers::SubModel& subModel      = Ers::SubModel::Get();
        ResourceComponent* component = subModel.GetComponent<ResourceComponent>(resourceEntity);
        const int channelCount       = component ? component->GetNumInputChannels() : 0;
        return ChannelRange(resourceEntity, false, channelCount);
    }

    ResourceComponent::ChannelRange ResourceComponent::OutputChannels(EntityID resourceEntity)
    {
        Ers::SubModel& subModel      = Ers::SubModel::Get();
        ResourceComponent* component = subModel.GetComponent<ResourceComponent>(resourceEntity);
        const int channelCount       = component ? component->GetNumOutputChannels() : 0;
        return ChannelRange(resourceEntity, true, channelCount);
    }

    ResourceComponent::ChannelEnumerator ResourceComponent::ChannelRange::begin() const
    {
        return ChannelEnumerator(resourceEntity, 0, isOutputChannel);
    }

    ResourceComponent::ChannelEnumerator ResourceComponent::ChannelRange::end() const
    {
        return ChannelEnumerator(resourceEntity, channelCount, isOutputChannel);
    }

    EntityID ResourceComponent::ChannelEnumerator::operator*() const
    {
        Ers::SubModel& subModel      = Ers::SubModel::Get();
        ResourceComponent* component = subModel.GetComponent<ResourceComponent>(resourceEntity);

        return isOutputChannel ? component->GetOutputChannel(index) : component->GetInputChannel(index);
    }

    ResourceComponent::ChannelEnumerator& ResourceComponent::ChannelEnumerator::operator++()
    {
        ++index;
        return *this;
    }

    bool ResourceComponent::ChannelEnumerator::operator==(const ChannelEnumerator& other) const
    {
        return resourceEntity == other.resourceEntity && index == other.index && isOutputChannel == other.isOutputChannel;
    }

    bool ResourceComponent::ChannelEnumerator::operator!=(const ChannelEnumerator& other) const
    {
        return !(*this == other);
    }
} // namespace Ers
