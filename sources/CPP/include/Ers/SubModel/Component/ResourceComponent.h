#pragma once

#include "Ers/SubModel/CoreComponent.h"
#include "Ers/SubModel/Entity.h"

#include <cstdint>

namespace Ers
{
    /// @brief Component for managing input and output channels of a resource.
    class ResourceComponent : public CoreComponent
    {
      public:
        ResourceComponent()                                    = default;
        ResourceComponent(const ResourceComponent&)            = delete;
        ResourceComponent(ResourceComponent&&)                 = delete;
        ResourceComponent& operator=(const ResourceComponent&) = delete;
        ResourceComponent& operator=(ResourceComponent&&)      = delete;
        ~ResourceComponent()                                   = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the number of input channels.
        /// @return The number of input channels
        [[nodiscard]] int GetNumInputChannels() const;

        /// @brief Get the number of output channels.
        /// @return The number of output channels
        [[nodiscard]] int GetNumOutputChannels() const;

        /// @brief Get an input channel by index.
        /// @param index The index of the input channel
        /// @return The entity representing the input channel
        [[nodiscard]] Entity GetInputChannel(int index) const;

        /// @brief Get an output channel by index.
        /// @param index The index of the output channel
        /// @return The entity representing the output channel
        [[nodiscard]] Entity GetOutputChannel(int index) const;
    };
} // namespace Ers
