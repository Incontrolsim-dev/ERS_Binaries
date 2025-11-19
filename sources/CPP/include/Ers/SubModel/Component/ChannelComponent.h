#pragma once

#include "Ers/SubModel/CoreComponent.h"
#include "Ers/SubModel/Entity.h"

#include <cstdint>

namespace Ers
{
    /// @brief Component representing a channel connection between entities.
    class ChannelComponent : public CoreComponent
    {
      public:
        ChannelComponent()                                   = default;
        ChannelComponent(const ChannelComponent&)            = delete;
        ChannelComponent(ChannelComponent&&)                 = delete;
        ChannelComponent& operator=(const ChannelComponent&) = delete;
        ChannelComponent& operator=(ChannelComponent&&)      = delete;
        ~ChannelComponent()                                  = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the type of the channel.
        /// @return The channel type
        [[nodiscard]] int GetType() const;

        /// @brief Get the entity this channel is connected to.
        /// @return The connected entity
        [[nodiscard]] Entity GetConnectedTo() const;

        /// @brief Check if the channel is open.
        /// @return True if the channel is open
        [[nodiscard]] bool IsOpen() const;

        /// @brief Get the longitudinal position.
        /// @return The longitudinal position
        [[nodiscard]] float GetLongitudinalPosition() const;

        /// @brief Set the longitudinal position.
        /// @param position The new longitudinal position
        void SetLongitudinalPosition(float position);
    };
} // namespace Ers
