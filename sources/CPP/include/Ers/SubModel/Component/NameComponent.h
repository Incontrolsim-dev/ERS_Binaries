#pragma once
#include "Ers/SubModel/CoreComponent.h"

#include <cstdint>
#include <string>

namespace Ers
{
    class NameComponent : public CoreComponent
    {

      public:
        NameComponent()                                = default;
        NameComponent(const NameComponent&)            = delete;
        NameComponent(NameComponent&&)                 = delete;
        NameComponent& operator=(const NameComponent&) = delete;
        NameComponent& operator=(NameComponent&&)      = delete;
        ~NameComponent()                               = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get name
        /// @return
        [[nodiscard]] std::string_view Name() const;
        /// @brief Set name
        /// @param newName
        void Name(const std::string_view& newName) const;
    };
} // namespace Ers
