#pragma once

#include <string>

#include "Ers/Utility/Util.h"

namespace Ers
{

    /// @brief This Entity class provides an interface to use components that are attached to it as well as interface with higher level
    /// abstractions provided by the core, such as a hierarchy
    class Entity
    {

      public:
        Entity() = delete;
        Entity(EntityID id);
        Entity(const Entity&)            = default;
        Entity(Entity&&)                 = default;
        Entity& operator=(const Entity&) = default;
        Entity& operator=(Entity&&)      = default;
        operator EntityID() const { return Id; } // Support implicit conversion/assignment into EntityID
        constexpr bool operator==(Entity& other) { return other.Id == Id; }
        constexpr bool operator!=(Entity& other) { return other.Id != Id; }

        [[nodiscard]] Entity GetParent() const;
        uint64_t GetChildCount() const;

        [[nodiscard]] Entity GetFirstChild() const;
        [[nodiscard]] Entity GetLastChild() const;

        [[nodiscard]] Entity GetPreviousSibling() const;
        [[nodiscard]] Entity GetNextSibling() const;

        /// @brief Get a component from an entity
        /// @tparam T
        /// @param entity
        /// @return
        template <class T> T* GetComponent() const;

        template <class T> [[nodiscard]] bool HasComponent() const;

        /// @brief Add a component to an entity
        /// NOTE* if component does already exist function will do nothing
        /// @tparam T
        /// @param entity
        /// @return
        template <class T> T* AddComponent() const;

        template <class T> void RemoveComponent() const;

        [[nodiscard]] bool IsValid() const;

        EntityID Id;

        static constexpr EntityID InvalidEntity = 0;

        [[nodiscard]] std::string_view GetName() const;
    };

} // namespace Ers
