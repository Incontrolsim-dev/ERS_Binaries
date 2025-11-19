#pragma once

#include <cstdint>

#include "Ers/Math/HMM/VectorMath.h"
#include "Ers/SubModel/CoreComponent.h"
#include "Ers/Utility/Util.h"

namespace Ers
{
    /// @brief Component defining the position, rotation, and scale of an entity.
    class TransformComponent : public CoreComponent
    {
      public:
        TransformComponent()                                     = default;
        TransformComponent(const TransformComponent&)            = delete;
        TransformComponent(TransformComponent&&)                 = delete;
        TransformComponent& operator=(const TransformComponent&) = delete;
        TransformComponent& operator=(TransformComponent&&)      = delete;
        ~TransformComponent()                                    = default;

        /// @brief Get the core type ID for this component
        /// @return The component type ID from ers-core
        static uint32_t CoreTypeId();

        uint32_t TypeId();
        void RegisterType(void* submodelInstance);

        /// @brief Get the local position.
        /// @return
        [[nodiscard]] Vector3 GetPosition() const;
        /// @brief Set the local position.
        /// @param pos
        void SetPosition(Vector3 pos);
        /// @brief Get the global position.
        /// @return
        [[nodiscard]] Vector3 GetGlobalPosition() const;

        /// @brief Get the local rotation as Euler angles.
        /// @return
        [[nodiscard]] Vector3 GetRotation() const;
        /// @brief Set the local rotation as Euler angles.
        /// @param rotation
        void SetRotation(Vector3 rotation);
        /// @brief Get the global rotation as Euler angles.
        /// @return
        [[nodiscard]] Vector3 GetGlobalRotation() const;

        /// @brief Get the local scale.
        /// @return
        [[nodiscard]] Vector3 GetScale() const;
        /// @brief Set the local scale.
        /// @param scale
        void SetScale(Vector3 scale);
        /// @brief Get the global scale.
        /// @return
        [[nodiscard]] Vector3 GetGlobalScale() const;

        /// @brief Rotate counterclockwise around the X-axis by a given angle.
        /// @param radians The angle in turns (1 turn = 360 degrees).
        void RotateX(float radians);
        /// @brief Rotate counterclockwise around the Y-axis by a given angle.
        /// @param radians The angle in turns (1 turn = 360 degrees).
        void RotateY(float radians);
        /// @brief Rotate counterclockwise around the Z-axis by a given angle.
        /// @param radians The angle in turns (1 turn = 360 degrees).
        void RotateZ(float radians);

        /// @brief Set the local rotation in Euler angles.
        /// @param x The angle around the X-axis in turns (1 turn = 360 degrees).
        /// @param y The angle around the Y-axis in turns (1 turn = 360 degrees).
        /// @param z The angle around the Z-axis in turns (1 turn = 360 degrees).
        void SetRotationEuler(float x, float y, float z);
        /// @brief Set the rotation by a given quaternion.
        /// @param x The X-component of the quaternion.
        /// @param y The Y-component of the quaternion.
        /// @param z The Z-component of the quaternion.
        /// @param w The W-component of the quaternion.
        void SetQuaternion(float x, float y, float z, float w);
    };
} // namespace Ers
