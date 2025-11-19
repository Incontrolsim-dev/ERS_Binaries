#include "ResourceComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t ResourceComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_ResourceComponent_TypeId();
    }

    int ResourceComponent::GetNumInputChannels() const
    {
        return static_cast<int>(ersAPIFunctionPointers.ERS_ResourceComponent_GetNumInputChannels(const_cast<ResourceComponent*>(this)));
    }

    int ResourceComponent::GetNumOutputChannels() const
    {
        return static_cast<int>(ersAPIFunctionPointers.ERS_ResourceComponent_GetNumOutputChannels(const_cast<ResourceComponent*>(this)));
    }

    Entity ResourceComponent::GetInputChannel(int index) const
    {
        return ersAPIFunctionPointers.ERS_ResourceComponent_GetInputChannel(
            const_cast<ResourceComponent*>(this), static_cast<size_t>(index));
    }

    Entity ResourceComponent::GetOutputChannel(int index) const
    {
        return ersAPIFunctionPointers.ERS_ResourceComponent_GetOutputChannel(
            const_cast<ResourceComponent*>(this), static_cast<size_t>(index));
    }
} // namespace Ers
