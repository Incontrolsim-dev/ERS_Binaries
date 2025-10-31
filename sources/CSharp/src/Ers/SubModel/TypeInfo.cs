using System;
using System.Numerics;
using System.Reflection;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Mark a component to have available type information.
    /// </summary>
    /// <param name="name">The name to give to the component.</param>
    [AttributeUsage(AttributeTargets.Struct, Inherited = false)]
    public sealed class TypeInfoAttribute(string name) : Attribute
    {
        /// <summary>
        /// The name of the component.
        /// </summary>
        public readonly string Name = name;
    }

    /// <summary>
    /// Mark a field to have available field information.
    /// </summary>
    [AttributeUsage(AttributeTargets.Field, Inherited = true, AllowMultiple = false)]
    public sealed class FieldInfoAttribute : Attribute
    {
        /// <summary>
        /// The name of the field.
        /// </summary>
        public readonly string? Name;
        /// <summary>
        /// The type ID of the field, see <see cref="FieldType"/>.
        /// </summary>
        public readonly UInt32? Type;

        /// <summary>
        /// Mark a field to have available field information.
        ///
        /// <para>NOTE: Entities will be seen as UInt64 unless explicitly defining them as Entity.</para>
        /// </summary>
        public FieldInfoAttribute()
        {
            Name = null;
            Type = null;
        }

        /// <summary>
        /// Mark a field to have available field information.
        ///
        /// <para>NOTE: Entities will be seen as UInt64 unless explicitly defining them as Entity.</para>
        /// </summary>
        /// <param name="name">The name of the field.</param>
        public FieldInfoAttribute(string? name)
        {
            Name = name;
            Type = null;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="type">The type ID of the field, see <see cref="FieldType"/></param>
        public FieldInfoAttribute(FieldType type)
        {
            Name = null;
            Type = (UInt32?)type;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="type">The type ID of the field, see <see cref="FieldType"/></param>
        public FieldInfoAttribute(UInt32 type)
        {
            Name = null;
            Type = type;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="name">The name of the field.</param>
        /// <param name="type">The type ID of the field, see <see cref="FieldType"/></param>
        public FieldInfoAttribute(string name, FieldType type)
        {
            Name = name;
            Type = (UInt32?)type;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="name">The name of the field.</param>
        /// <param name="type">The type ID of the field, see <see cref="FieldType"/></param>
        public FieldInfoAttribute(string name, UInt32 type)
        {
            Name = name;
            Type = type;
        }
    }

    /// <summary>
    /// The type of the field.
    ///
    /// <para>Used by ERS to know how to interpret the component's fields data.</para>
    /// </summary>
    public enum FieldType : uint
    {
        /// <summary>
        /// A 32-bit float (<see cref="float"/>).
        /// </summary>
        Float32 = 0,
        /// <summary>
        /// A boolean (<see cref="bool"/>).
        /// </summary>
        Bool = 1,
        /// <summary>
        /// A 32-bit signed integer (<see cref="int"/>).
        /// </summary>
        Int32 = 2,
        /// <summary>
        /// A 32-bit unsigned integer (<see cref="System.UInt32"/>).
        /// </summary>
        UInt32 = 3,
        /// <summary>
        /// A 64-bit signed integer (<see cref="System.Int64"/>).
        /// </summary>
        Int64 = 4,
        /// <summary>
        /// A 64-bit unsigned integer (<see cref="System.UInt64"/>).
        /// </summary>
        UInt64 = 5,
        /// <summary>
        /// An ERS Entity.
        /// </summary>
        Entity = 6,
        /// <summary>
        /// A list of any known registered type.
        /// </summary>
        List = 7,
        /// <summary>
        /// A string.
        /// </summary>
        String = 8,
        /// <summary>
        /// A 2D vector.
        /// </summary>
        Vector2 = 9,
        /// <summary>
        /// A 3D vector.
        /// </summary>
        Vector3 = 10,
        /// <summary>
        /// A 4D vector.
        /// </summary>
        Vector4 = 11,
    }

    internal static class TypeInfoRegister
    {
        /// <summary>
        /// Attempt to register type and field information.
        /// </summary>
        /// <param name="type">The type to register the type and field information of.</param>
        /// <returns>A pointer to the TypeInfo in the core, or IntPtr.Zero if on failure.</returns>
        internal static IntPtr RegisterType(Type type)
        {
            var typeInfo = type.GetCustomAttribute<TypeInfoAttribute>();
            var ti       = type.GetTypeInfo();

            var layout = ti.StructLayoutAttribute;
            if (layout == null || layout.Value == LayoutKind.Auto)
            {
                // StructLayout needs to be explicitly defined
                return IntPtr.Zero;
            }

            string typeName = typeInfo != null ? typeInfo.Name : type.Name;

            IntPtr typeInfoPtr;
            unsafe
            {
                var nameUtf8 = typeName.ToUtf8NullTerminated();
                fixed(byte* nameByte = nameUtf8)
                {
                    typeInfoPtr = ErsEngine.ERS_TypeInfo_RegisterStruct(nameByte);
                }
            }
            AddFields(ti, typeInfoPtr);
            return typeInfoPtr;
        }

        private static void AddFields(System.Reflection.TypeInfo type, IntPtr typeInfoPtr)
        {
            foreach (FieldInfo field in type.GetFields())
            {
                UInt32 offset = GetOffset(type, field);
                var fieldInfo = field.GetCustomAttribute<FieldInfoAttribute>();
                if (fieldInfo == null)
                    continue;

                unsafe
                {
                    string name    = fieldInfo.Name ?? field.Name;
                    UInt32 typeInt = GetFieldType(field, fieldInfo.Type);
                    fixed(byte* nameByte = name.ToUtf8NullTerminated())
                    {
                        ErsEngine.ERS_TypeInfo_AddField(typeInfoPtr, nameByte, typeInt, offset);
                    }
                }
            }
        }

        private static UInt32 GetFieldType(FieldInfo field, UInt32? typeInt)
        {
            if (typeInt != null)
                return (UInt32)typeInt.Value;

            return field.FieldType switch {
                Type t when t == typeof(float)   => (UInt32)FieldType.Float32,
                Type t when t == typeof(bool)    => (UInt32)FieldType.Bool,
                Type t when t == typeof(Int32)   => (UInt32)FieldType.Int32,
                Type t when t == typeof(UInt32)  => (UInt32)FieldType.UInt32,
                Type t when t == typeof(Int64)   => (UInt32)FieldType.Int64,
                Type t when t == typeof(UInt64)  => (UInt32)FieldType.UInt64,
                Type t when t == typeof(Entity)  => (UInt32)FieldType.Entity,
                Type t when t == typeof(string)  => (UInt32)FieldType.String,
                Type t when t == typeof(Vector2) => (UInt32)FieldType.Vector2,
                Type t when t == typeof(Vector3) => (UInt32)FieldType.Vector3,
                Type t when t == typeof(Vector4) => (UInt32)FieldType.Vector4,
                _                                => throw new NotSupportedException(),
            };
        }

        private static UInt32 GetOffset(System.Reflection.TypeInfo type, FieldInfo field)
        {
            UInt32 offset;
            var offsetAtt = field.GetCustomAttribute<FieldOffsetAttribute>();
            if (offsetAtt != null)
            {
                offset = (UInt32)offsetAtt.Value;
            }
            else
            {
                offset = (UInt32)Marshal.OffsetOf(type, field.Name);
            }
            return offset;
        }
    }
}
