#pragma once

#include "Ers/SubModel/CoreComponent.h"
#include "Ers/SubModel/Entity.h"

#include <cstdint>

namespace Ers
{
    enum class ChannelType
    {
        Input  = 0,
        Output = 1,
    };

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
        [[nodiscard]] ChannelType GetType() const;

        /// @brief Get the entity this channel is connected to.
        /// @return The connected entity
        [[nodiscard]] Entity GetConnectedTo() const;

        /// @brief Check if the channel is open.
        /// @return True if the channel is open
        [[nodiscard]] bool IsOpen() const;

        /// @brief Check if the channel is open.
        /// @return True if the channel is open
        [[nodiscard]] static bool IsOpen(EntityID channel);

        /// @brief Send a child entity through the channel.
        /// @param channelFrom The channel to send from
        /// @param child The entity to send
        /// @return True if the child entity was succesfully sent, false otherwise
        static bool Send(Entity channelFrom, Entity child);

        /// @brief Open a channel.
        /// @param channel The channel entity
        static void Open(Entity channel);

        /// @brief Close a channel.
        /// @param channel The channel entity
        static void Close(Entity channel);

        /// @brief Check if a channel is ready.
        /// @param channel The channel entity
        /// @return True if the channel is ready
        [[nodiscard]] static bool IsReady(Entity channel);

        /// @brief Connect two channels.
        /// @param input Input channel entity
        /// @param output Output channel entity
        static void Connect(Entity input, Entity output);

        /// @brief Add a ChannelComponent to an entity and register it on its parent's ResourceComponent.
        /// @param channel The entity to add the ChannelComponent to
        /// @param type The type of the channel
        /// @param resource The parent entity with a ResourceComponent to register the channel to
        static void AddChannelComponent(Entity channel, ChannelType type, Entity resource);
    };
} // namespace Ers
