#include "RelationComponent.h"
#include "Ers/Api.h"
#include "Ers/SubModel/SubModel.h"

namespace Ers
{
    EntityID Ers::RelationComponent::Parent() const
    {
        return ersAPIFunctionPointers.ERS_RelationComponent_GetParent(const_cast<RelationComponent*>(this));
    }

    EntityID Ers::RelationComponent::First() const
    {
        return ersAPIFunctionPointers.ERS_RelationComponent_GetFirst(const_cast<RelationComponent*>(this));
    }

    EntityID Ers::RelationComponent::Last() const
    {
        return ersAPIFunctionPointers.ERS_RelationComponent_GetLast(const_cast<RelationComponent*>(this));
    }

    EntityID Ers::RelationComponent::Previous() const
    {
        return ersAPIFunctionPointers.ERS_RelationComponent_GetPrevious(const_cast<RelationComponent*>(this));
    }

    EntityID Ers::RelationComponent::Next() const
    {
        return ersAPIFunctionPointers.ERS_RelationComponent_GetNext(const_cast<RelationComponent*>(this));
    }

    uint64_t Ers::RelationComponent::ChildCount() const
    {
        return ersAPIFunctionPointers.ERS_RelationComponent_GetChildCount(const_cast<RelationComponent*>(this));
    }

    EntityID Ers::RelationComponent::operator[](uint64_t index) const
    {
        Ers::SubModel& submodel = Ers::GetSubModel();

        EntityID child = First();
        for (uint64_t i = 0; i < index; i++)
            child = submodel.GetComponent<RelationComponent>(child)->Next();
        return child;
    }

    Ers::RelationComponent::ChildEnumerator Ers::RelationComponent::begin() const
    {
        return ChildEnumerator(First());
    }

    Ers::RelationComponent::ChildEnumerator Ers::RelationComponent::end() const
    {
        return ChildEnumerator(Ers::Entity::InvalidEntity);
    }

    EntityID Ers::RelationComponent::ChildEnumerator::operator*() const
    {
        return current;
    }

    Ers::RelationComponent::ChildEnumerator& Ers::RelationComponent::ChildEnumerator::operator++()
    {
        if (current != Ers::Entity::InvalidEntity)
        {
            auto& submodel = Ers::GetSubModel();
            auto component = submodel.GetComponent<RelationComponent>(current);
            current        = component ? component->Next() : Ers::Entity::InvalidEntity;
        }
        return *this;
    }

    bool Ers::RelationComponent::ChildEnumerator::operator==(const ChildEnumerator& other) const
    {
        return current == other.current;
    }

    bool Ers::RelationComponent::ChildEnumerator::operator!=(const ChildEnumerator& other) const
    {
        return current != other.current;
    }
} // namespace Ers
