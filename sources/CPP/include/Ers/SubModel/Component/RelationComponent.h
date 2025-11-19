#pragma once
#include "Ers/SubModel/CoreComponent.h"
#include "Ers/Utility/Util.h"

#include <cstdint>

namespace Ers
{
    class RelationComponent : public CoreComponent
    {
      public:
        RelationComponent()                                    = default;
        RelationComponent(const RelationComponent&)            = delete;
        RelationComponent(RelationComponent&&)                 = delete;
        RelationComponent& operator=(const RelationComponent&) = delete;
        RelationComponent& operator=(RelationComponent&&)      = delete;
        ~RelationComponent()                                   = delete;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief get parent entity
        /// @return
        [[nodiscard]] EntityID Parent() const;
        /// @brief get first child entity
        /// @return
        [[nodiscard]] EntityID First() const;
        /// @brief get last child entity
        /// @return
        [[nodiscard]] EntityID Last() const;
        /// @brief
        /// @return
        [[nodiscard]] EntityID Previous() const;
        /// @brief get next sibbling entity
        /// @return
        [[nodiscard]] EntityID Next() const;

        [[nodiscard]] uint64_t ChildCount() const;

        /// @brief Child indexer
        /// @param index The index of the child to retrieve.
        /// @return The child
        EntityID operator[](uint64_t index) const;

        class ChildEnumerator;

        ChildEnumerator begin() const;

        ChildEnumerator end() const;
    };

    /// @brief Allows for the enumeration over children of a parent entity. Becomes invalid once the makeup of the parent's child
    /// entities change.
    class RelationComponent::ChildEnumerator
    {
      public:
        ChildEnumerator(EntityID c) :
            current(c)
        {
        }

        EntityID operator*() const;

        ChildEnumerator& operator++();

        bool operator==(const ChildEnumerator& other) const;

        bool operator!=(const ChildEnumerator& other) const;

      private:
        EntityID current;
    };
} // namespace Ers
