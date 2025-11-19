#include "ChannelComponent.h"
#include "Ers/Api.h"

namespace Ers
{
    uint32_t ChannelComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_ChannelComponent_TypeId();
    }

    int ChannelComponent::GetType() const
    {
        return ersAPIFunctionPointers.ERS_ChannelComponent_GetType(const_cast<ChannelComponent*>(this));
    }

    Entity ChannelComponent::GetConnectedTo() const
    {
        return ersAPIFunctionPointers.ERS_ChannelComponent_GetConnectedTo(const_cast<ChannelComponent*>(this));
    }

    bool ChannelComponent::IsOpen() const
    {
        return ersAPIFunctionPointers.ERS_ChannelComponent_IsOpen(const_cast<ChannelComponent*>(this));
    }

    float ChannelComponent::GetLongitudinalPosition() const
    {
        return ersAPIFunctionPointers.ERS_ChannelComponent_GetlongitudinalPosition(const_cast<ChannelComponent*>(this));
    }

    void ChannelComponent::SetLongitudinalPosition(float position)
    {
        ersAPIFunctionPointers.ERS_ChannelComponent_SetlongitudinalPosition(this, position);
    }
} // namespace Ers
