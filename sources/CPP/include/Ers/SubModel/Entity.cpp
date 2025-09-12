#include "Entity.h"
#include "Ers/Api.h"

#include "Ers/SubModel/SubModel.h"

namespace Ers
{

    Entity::Entity(EntityID id) :
        Id(id)
    {
    }

    [[nodiscard]] Entity Entity::GetParent() const
    {
        return ersAPIFunctionPointers.ERS_Entity_GetParent(Id);
    }

    uint64_t Entity::GetChildCount() const
    {
        return ersAPIFunctionPointers.ERS_Entity_GetChildCount(Id);
    }

    [[nodiscard]] Entity Entity::GetFirstChild() const
    {
        return ersAPIFunctionPointers.ERS_Entity_GetFirstChild(Id);
    }
    [[nodiscard]] Entity Entity::GetLastChild() const
    {
        return ersAPIFunctionPointers.ERS_Entity_GetLastChild(Id);
    }

    [[nodiscard]] Entity Entity::GetPreviousSibling() const
    {
        return ersAPIFunctionPointers.ERS_Entity_GetPreviousSibling(Id);
    }
    [[nodiscard]] Entity Entity::GetNextSibling() const
    {
        return ersAPIFunctionPointers.ERS_Entity_GetNextSibling(Id);
    }

    [[nodiscard]] bool Entity::IsValid() const
    {
        return ersAPIFunctionPointers.ERS_Entity_IsValid(Id);
    }

    [[nodiscard]] std::string_view Entity::GetName() const
    {
        return GetSubModel().GetComponent<NameComponent>(Id)->Name();
    }
} // namespace Ers
