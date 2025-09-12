using System.ComponentModel;
using System.Numerics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Component defining the position, rotation, and scale of an entity.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct TransformComponent : ICoreComponent
    {
        /// <summary>
        /// The local position as Vector3
        /// </summary>
        [Category("Transform")]
        [Description("The position of the entity.")]
        public Vector3 Position
        {
            get => GetPosition3D();
            set => SetPosition(value);
        }

        /// <summary>
        /// The local rotation as euler angles.
        /// </summary>
        [Category("Transform")]
        [Description("The rotation of the entity.")]
        public Vector3 Rotation
        {
            get => new Vector3(GetRotationX(), GetRotationY(), GetRotationZ());
            set {
                SetRotationEuler(value.X, value.Y, value.Z);
            }
        }

        /// <summary>
        /// The local scale of this transformation.
        /// </summary>
        [Category("Transform")]
        [Description("The scale of the entity.")]
        public Vector3 Scale
        {
            get => GetScale3D();
            set => SetScale(value.X, value.Y, value.Z);
        }

        public float GetPositionX() => ErsEngine.ERS_TransformComponent_Position_X(CorePointer());
        public void SetPositionX(float newValue) => ErsEngine.ERS_TransformComponent_SetPosition_X(CorePointer(), newValue);

        public float GetPositionY() => ErsEngine.ERS_TransformComponent_Position_Y(CorePointer());
        public void SetPositionY(float newValue) => ErsEngine.ERS_TransformComponent_SetPosition_Y(CorePointer(), newValue);

        public float GetPositionZ() => ErsEngine.ERS_TransformComponent_Position_Z(CorePointer());
        public void SetPositionZ(float newValue) => ErsEngine.ERS_TransformComponent_SetPosition_Z(CorePointer(), newValue);

        public void SetPosition(Vector3 pos) => ErsEngine.ERS_TransformComponent_SetPosition(CorePointer(), pos.X, pos.Y, pos.Z);

        public float GetRotationX() => ErsEngine.ERS_TransformComponent_Rotation_X(CorePointer());
        public void SetRotationX(float newValue) => ErsEngine.ERS_TransformComponent_SetRotation_X(CorePointer(), newValue);

        public float GetRotationY() => ErsEngine.ERS_TransformComponent_Rotation_Y(CorePointer());
        public void SetRotationY(float newValue) => ErsEngine.ERS_TransformComponent_SetRotation_Y(CorePointer(), newValue);

        public float GetRotationZ() => ErsEngine.ERS_TransformComponent_Rotation_Z(CorePointer());
        public void SetRotationZ(float newValue) => ErsEngine.ERS_TransformComponent_SetRotation_Z(CorePointer(), newValue);

        public void RotateX(float angle) => ErsEngine.ERS_TransformComponent_Rotate_X(CorePointer(), angle);
        public void RotateY(float angle) => ErsEngine.ERS_TransformComponent_Rotate_Y(CorePointer(), angle);
        public void RotateZ(float angle) => ErsEngine.ERS_TransformComponent_Rotate_Z(CorePointer(), angle);

        public void SetRotationEuler(float x, float y, float z) => ErsEngine.ERS_TransformComponent_SetRotationEuler(CorePointer(), x, y, z);
        public void SetQuaternion(float x, float y, float z, float w) => ErsEngine.ERS_TransformComponent_SetQuaternion(CorePointer(), x, y, z, w);

        public float GetScaleX() => ErsEngine.ERS_TransformComponent_Scale_X(CorePointer());
        public void SetScaleX(float newValue) => ErsEngine.ERS_TransformComponent_SetScale_X(CorePointer(), newValue);

        public float GetScaleY() => ErsEngine.ERS_TransformComponent_Scale_Y(CorePointer());
        public void SetScaleY(float newValue) => ErsEngine.ERS_TransformComponent_SetScale_Y(CorePointer(), newValue);

        public float GetScaleZ() => ErsEngine.ERS_TransformComponent_Scale_Z(CorePointer());
        public void SetScaleZ(float newValue) => ErsEngine.ERS_TransformComponent_SetScale_Z(CorePointer(), newValue);

        public void SetScale(float x, float y, float z) => ErsEngine.ERS_TransformComponent_SetScale(CorePointer(), x, y, z);

        public float GlobalPositionX() => ErsEngine.ERS_TransformComponent_GlobalPosition_X(CorePointer());
        public float GlobalPositionY() => ErsEngine.ERS_TransformComponent_GlobalPosition_Y(CorePointer());
        public float GlobalPositionZ() => ErsEngine.ERS_TransformComponent_GlobalPosition_Z(CorePointer());

        public float GlobalScaleX() => ErsEngine.ERS_TransformComponent_GlobalScale_X(CorePointer());
        public float GlobalScaleY() => ErsEngine.ERS_TransformComponent_GlobalScale_Y(CorePointer());
        public float GlobalScaleZ() => ErsEngine.ERS_TransformComponent_GlobalScale_Z(CorePointer());

        public float GlobalRotationX() => ErsEngine.ERS_TransformComponent_GlobalRotation_X(CorePointer());
        public float GlobalRotationY() => ErsEngine.ERS_TransformComponent_GlobalRotation_Y(CorePointer());
        public float GlobalRotationZ() => ErsEngine.ERS_TransformComponent_GlobalRotation_Z(CorePointer());

        public Vector2 GetPosition2D() => new Vector2(GetPositionX(), GetPositionY());
        public Vector3 GetPosition3D() => new Vector3(GetPositionX(), GetPositionY(), GetPositionZ());
        public Vector2 GetGlobalPosition2D() => new Vector2(GlobalPositionX(), GlobalPositionY());
        public Vector3 GetGlobalPosition3D() => new Vector3(GlobalPositionX(), GlobalPositionY(), GlobalPositionZ());
        public Vector3 GetGlobalRotation3D() => new Vector3(GlobalRotationX(), GlobalRotationY(), GlobalRotationZ());

        /// <summary>
        /// Scale (X, Y) as Vector2
        /// </summary>
        /// <returns></returns>
        public Vector2 GetScale2D() => new Vector2(GetScaleX(), GetScaleY());

        /// <summary>
        /// Scale (X, Y, Z) as Vector3
        /// </summary>
        /// <returns></returns>
        public Vector3 GetScale3D() => new Vector3(GetScaleX(), GetScaleY(), GetScaleZ());

        /// <summary>
        /// Returns the component ID
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_TransformComponent_TypeId();

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed (TransformComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }

}
