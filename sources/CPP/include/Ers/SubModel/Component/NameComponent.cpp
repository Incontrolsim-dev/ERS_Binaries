#include "NameComponent.h"
#include "Ers/Api.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    uint32_t NameComponent::CoreTypeId()
    {
        return ersAPIFunctionPointers.ERS_NameComponent_TypeId();
    }

    std::string_view NameComponent::Name() const
    {
        return {ersAPIFunctionPointers.ERS_NameComponent_GetName(const_cast<NameComponent*>(this))};
    }

    void NameComponent::Name(const std::string_view& newName) const
    {
        ersAPIFunctionPointers.ERS_NameComponent_SetName(const_cast<NameComponent*>(this), newName.data(), newName.length());
    }
} // namespace Ers
