#pragma once

#include <cstdint>

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/CoreComponent.h"
#include "Ers/Visualization/Color.h"
#include "Ers/Visualization/InstancedModel.h"
#include "Ers/Visualization/Texture.h"

namespace Ers
{
    /// @brief The available shapes to render using the RenderComponent.
    enum class RenderComponentShape : uint8_t
    {
        /// @brief In 2D a point that remains the same size, regardless of zoom level.
        /// In 3D a small cube of size (0.1, 0.1, 0.1).
        Point,
        /// @brief A rectangle in 2D, or a box in 3D.
        Rectangle,
        /// @brief A circle in 2D, or a sphere in 3D.
        Circle,
        /// @brief A triangle in 2D, or a pyramid in 3D.
        Triangle,
    };

    /// @brief A component for a quick rendering setup.
    ///
    /// Apply just a color to render a rectangle in 2D and a cube in 3D.
    /// Add an InstancedModel to set a custom 3D model.
    ///
    /// Requires a TransformComponent to be rendered.
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
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        /// @brief Get the shape to render.
        /// @return
        RenderComponentShape GetShape();

        /// @brief Set the shape to render.
        /// @param shape The new shape.
        void SetShape(RenderComponentShape shape);

        /// @brief Get the color of the entity.
        /// @return The color.
        [[nodiscard]] Color GetColor() const;

        /// @brief Set the color of the entity.
        /// @param color The color to set.
        void SetColor(Ers::Color color);

        /// @brief Get the current texture for the 2D shapes.
        /// @return
        [[nodiscard]] Ers::Texture* GetTexture2D();

        /// @brief Set the texture used for the 2D shapes.
        /// @param texture
        void SetTexture2D(const Ers::Texture& texture);

        /// @brief Remove the texture for 2D shapes.
        /// Shapes will then be drawn using just the given color.
        void RemoveTexture2D();

        /// @brief Get the InstancedModel used for 3D rendering.
        /// @return Pointer to the InstancedModel
        [[nodiscard]] Ers::InstancedModel* GetInstancedModel();

        /// @brief Set the InstancedModel used for 3D rendering.
        /// @param model Pointer to the InstancedModel
        void SetInstancedModel(const Ers::InstancedModel& model);
    };
} // namespace Ers
