#pragma once

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/CoreComponent.h"
#include "Ers/Visualization/Color.h"

#include <cstdint>

namespace Ers
{
    class InstancedModel;
}

namespace Ers
{
    /// @brief A component for rendering entities with color and mesh information.
    /// The component should also have a TransformComponent.
    class RenderComponent : public CoreComponent
    {
      public:
        RenderComponent()                                  = default;
        RenderComponent(const RenderComponent&)            = delete;
        RenderComponent(RenderComponent&&)                 = delete;
        RenderComponent& operator=(const RenderComponent&) = delete;
        RenderComponent& operator=(RenderComponent&&)      = delete;
        ~RenderComponent()                                 = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core (same as BasicRenderComponent)
        static uint32_t CoreTypeId();

        /// @brief Get the color of the rendered object.
        /// @return The color as Vector4 (RGBA, 0.0-1.0)
        [[nodiscard]] Ers::Color GetColor() const;

        /// @brief Set the color of the rendered object.
        /// @param color The color to set.
        void SetColor(Ers::Color color);

        /// @brief Get the InstancedModel used for rendering.
        /// @return Pointer to the InstancedModel
        [[nodiscard]] Ers::InstancedModel* GetInstancedModel();

        /// @brief Set the InstancedModel used for rendering.
        /// @param model Pointer to the InstancedModel
        void SetInstancedModel(Ers::InstancedModel* model);
    };
} // namespace Ers
