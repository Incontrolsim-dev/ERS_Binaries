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
        /// The local position.
        /// </summary>
        public Vector3 Position
        {
            get => new Vector3(
                ErsEngine.ERS_TransformComponent_Position_X(CorePtr),
                ErsEngine.ERS_TransformComponent_Position_Y(CorePtr),
                ErsEngine.ERS_TransformComponent_Position_Z(CorePtr));
            set => ErsEngine.ERS_TransformComponent_SetPosition(CorePtr, value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The global position.
        /// </summary>
        public Vector3 GlobalPosition
        {
            get => new Vector3(
                ErsEngine.ERS_TransformComponent_GlobalPosition_X(CorePtr),
                ErsEngine.ERS_TransformComponent_GlobalPosition_Y(CorePtr),
                ErsEngine.ERS_TransformComponent_GlobalPosition_Z(CorePtr));
        }

        /// <summary>
        /// The local rotation as Euler angles.
        /// </summary>
        public Vector3 Rotation
        {
            get => new Vector3(
                ErsEngine.ERS_TransformComponent_Rotation_X(CorePtr),
                ErsEngine.ERS_TransformComponent_Rotation_Y(CorePtr),
                ErsEngine.ERS_TransformComponent_Rotation_Z(CorePtr));
            set => SetRotationEuler(value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The global rotation as Euler angles.
        /// </summary>
        public Vector3 GlobalRotation
        {
            get => new Vector3(
                ErsEngine.ERS_TransformComponent_GlobalRotation_X(CorePtr),
                ErsEngine.ERS_TransformComponent_GlobalRotation_Y(CorePtr),
                ErsEngine.ERS_TransformComponent_GlobalRotation_Z(CorePtr));
        }

        /// <summary>
        /// The local scale.
        /// </summary>
        public Vector3 Scale
        {
            get => new Vector3(
                ErsEngine.ERS_TransformComponent_Scale_X(CorePtr),
                ErsEngine.ERS_TransformComponent_Scale_Y(CorePtr),
                ErsEngine.ERS_TransformComponent_Scale_Z(CorePtr));
            set => ErsEngine.ERS_TransformComponent_SetScale(CorePtr, value.X, value.Y, value.Z);
        }

        /// <summary>
        /// The
        /// </summary>
        public Vector3 GlobalScale
        {
            get => new Vector3(
                ErsEngine.ERS_TransformComponent_GlobalScale_X(CorePtr),
                ErsEngine.ERS_TransformComponent_GlobalScale_Y(CorePtr),
                ErsEngine.ERS_TransformComponent_GlobalScale_Z(CorePtr));
        }

        /// <summary>
        /// Rotate counterclockwise around the X-axis by a given angle.
        /// </summary>
        /// <param name="angle">The angle in turns (1 turn = 360 degrees).</param>
        public void RotateX(float angle) => ErsEngine.ERS_TransformComponent_Rotate_X(CorePtr, angle);
        /// <summary>
        /// Rotate counterclockwise around the Y-axis by a given angle.
        /// </summary>
        /// <param name="angle">The angle in turns (1 turn = 360 degrees).</param>
        public void RotateY(float angle) => ErsEngine.ERS_TransformComponent_Rotate_Y(CorePtr, angle);
        /// <summary>
        /// Rotate counterclockwise around the Z-axis by a given angle.
        /// </summary>
        /// <param name="angle">The angle in turns (1 turn = 360 degrees).</param>
        public void RotateZ(float angle) => ErsEngine.ERS_TransformComponent_Rotate_Z(CorePtr, angle);

        /// <summary>
        /// Set the rotation in Euler angles.
        /// </summary>
        /// <param name="x">The angle around the X-axis in turns (1 turn = 360 degrees).</param>
        /// <param name="y">The angle around the Y-axis in turns (1 turn = 360 degrees).</param>
        /// <param name="z">The angle around the Z-axis in turns (1 turn = 360 degrees).</param>
        public void SetRotationEuler(float x, float y, float z) => ErsEngine.ERS_TransformComponent_SetRotationEuler(CorePtr, x, y, z);
        /// <summary>
        /// Set the rotation by a given quaternion.
        /// </summary>
        /// <param name="x">The X-component of the quaternion.</param>
        /// <param name="y">The Y-component of the quaternion.</param>
        /// <param name="z">The Z-component of the quaternion.</param>
        /// <param name="w">The W-component of the quaternion.</param>
        public void SetQuaternion(float x, float y, float z, float w) =>
            ErsEngine.ERS_TransformComponent_SetQuaternion(CorePtr, x, y, z, w);

        /// <summary>
        /// Returns the component ID
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_TransformComponent_TypeId();

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr
        {
            get {
                unsafe
                {
                    fixed(TransformComponent* ptr = &this)
                    {
                        return (IntPtr)ptr;
                    }
                }
            }
        }
    }

}
