#pragma once

#include "Ers/SubModel/CoreComponent.h"
#include "Ers/Utility/Util.h"

namespace Ers
{
    class TransformComponent : public CoreComponent
    {
      public:
        TransformComponent()                                     = default;
        TransformComponent(const TransformComponent&)            = delete;
        TransformComponent(TransformComponent&&)                 = delete;
        TransformComponent& operator=(const TransformComponent&) = delete;
        TransformComponent& operator=(TransformComponent&&)      = delete;
        ~TransformComponent()                                    = default;

        uint32_t TypeId();
        void* CreateCallback();
        void RegisterType(void* submodelInstance);

        /// @brief Retrieve Position X value
        [[nodiscard]] float PositionX() const;

        /// @brief Set Position X value
        void PositionX(float x);

        /// @brief Retrieve Position Y value
        [[nodiscard]] float PositionY() const;

        /// @brief Set Position Y value
        void PositionY(float y);

        /// @brief Retrieve Position Z value
        [[nodiscard]] float PositionZ() const;

        /// @brief Set Position Z value
        void PositionZ(float z);

        /// @brief Retrieve Rotation X value
        [[nodiscard]] float RotationX() const;

        /// @brief Set Rotation X value
        void RotationX(float x);

        /// @brief Retrieve Rotation Y value
        [[nodiscard]] float RotationY() const;

        /// @brief Set Rotation Y value
        void RotationY(float y);

        /// @brief Retrieve Rotation Z value
        [[nodiscard]] float RotationZ() const;

        /// @brief Set Rotation Z value
        void RotationZ(float z);

        void RotateX(float radians);
        void RotateY(float radians);
        void RotateZ(float radians);

        /// @brief Retrieve Scale X value
        [[nodiscard]] float ScaleX() const;

        /// @brief Set Scale X value
        void ScaleX(float x);

        /// @brief Retrieve Scale Y value
        [[nodiscard]] float ScaleY() const;

        /// @brief Set Scale Y value
        void ScaleY(float y);

        /// @brief Retrieve Scale Z value
        [[nodiscard]] float ScaleZ() const;

        /// @brief Set Scale Z value
        void ScaleZ(float z);

        /// @brief Set the scale in all axes to the same value.
        void Scale(float scale);

        void Position(float x, float y, float z);
        void Scale(float x, float y, float z);
        void RotationEuler(float x, float y, float z);
        void SetQuaternion(float x, float y, float z, float w);

        /// @brief Get the global X-position.
        [[nodiscard]] float GlobalPositionX() const;

        /// @brief Get the global Y-position.
        [[nodiscard]] float GlobalPositionY() const;

        /// @brief Get the global Z-position.
        [[nodiscard]] float GlobalPositionZ() const;

        /// @brief Get the global X-scale.
        [[nodiscard]] float GlobalScaleX() const;

        /// @brief Get the global Y-scale.
        [[nodiscard]] float GlobalScaleY() const;

        /// @brief Get the global Z-scale.
        [[nodiscard]] float GlobalScaleZ() const;

        /// @brief Get the global rotation around X-axis.
        [[nodiscard]] float GlobalRotationX() const;

        /// @brief Get the global rotation around Y-axis.
        [[nodiscard]] float GlobalRotationY() const;

        /// @brief Get the global rotation around Z-axis.
        [[nodiscard]] float GlobalRotationZ() const;
    };
} // namespace Ers
