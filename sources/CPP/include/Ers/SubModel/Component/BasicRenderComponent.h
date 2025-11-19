#pragma once

#include <cstdint>

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/CoreComponent.h"
#include "Ers/Visualization/Color.h"

namespace Ers
{
    class InstancedModel;
}

namespace Ers
{
    /// @brief A component for a quick rendering setup.
    /// Apply just a color to render a rectangle in 2D and a cube in 3D.
    /// Add an InstancedModel to set a custom 3D model.
    class BasicRenderComponent : public CoreComponent
    {
      public:
        BasicRenderComponent()                                       = default;
        BasicRenderComponent(const BasicRenderComponent&)            = delete;
        BasicRenderComponent(BasicRenderComponent&&)                 = delete;
        BasicRenderComponent& operator=(const BasicRenderComponent&) = delete;
        BasicRenderComponent& operator=(BasicRenderComponent&&)      = delete;
        ~BasicRenderComponent()                                      = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the color of the entity (RGBA).
        /// @return The color as Vector4 (RGBA, 0.0-1.0)
        [[nodiscard]] Color GetColor() const;

        /// @brief Set the color of the entity (RGBA).
        /// @param color The color to set.
        void SetColor(Ers::Color color);

        /// @brief Get the InstancedModel used for 3D rendering.
        /// @return Pointer to the InstancedModel
        [[nodiscard]] Ers::InstancedModel* GetInstancedModel();

        /// @brief Set the InstancedModel used for 3D rendering.
        /// @param model Pointer to the InstancedModel
        void SetInstancedModel(Ers::InstancedModel* model);
    };
} // namespace Ers
