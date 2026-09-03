using System.Diagnostics;
using System.Numerics;
using System.Reflection;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Registry where types in ERS are stored (see <see cref="Ers.TypeInfo"/>).
    /// </summary>
    public static class TypeRegistry
    {
        /// <summary>
        /// Get a <see cref="Ers.TypeInfo"/> by its type ID (via <see cref="BuiltinType"/>).
        /// </summary>
        /// <param name="type">The type ID (via <see cref="BuiltinType"/>).</param>
        /// <returns></returns>
        public static TypeInfo GetTypeInfo(BuiltinType type) => new(ErsEngine.ERS_TypeRegistry_GetTypeById((uint)type));

        /// <summary>
        /// Get a <see cref="Ers.TypeInfo"/> by its type ID.
        /// </summary>
        /// <param name="typeId">The type ID.</param>
        /// <returns>The <see cref="Ers.TypeInfo"/> when found, null when not found.</returns>
        public static TypeInfo? GetTypeInfo(uint typeId)
        {
            IntPtr typeInfoPtr = ErsEngine.ERS_TypeRegistry_GetTypeById(typeId);
            if (typeInfoPtr == IntPtr.Zero)
                return null;

            return new(typeInfoPtr);
        }

        /// <summary>
        /// Get a <see cref="Ers.TypeInfo"/> by its name.
        /// </summary>
        /// <param name="typeName">The name of the type.</param>
        /// <returns>The <see cref="Ers.TypeInfo"/> when found, null when not found.</returns>
        public static TypeInfo? GetTypeInfo(string typeName)
        {
            var typeNameUtf8 = typeName.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* typeNameByte = typeNameUtf8)
                {
                    IntPtr typeInfoPtr = ErsEngine.ERS_TypeRegistry_GetTypeByName(typeNameByte);
                    if (typeInfoPtr == IntPtr.Zero)
                        return null;

                    return new(typeInfoPtr);
                }
            }
        }

        /// <summary>
        /// Attempt to register struct and field information.
        /// </summary>
        /// <param name="type">The type to register the type and field information of.</param>
        /// <returns>A pointer to the TypeInfo in the core, or IntPtr.Zero if on failure.</returns>
        internal static IntPtr TryRegisterStruct(Type type)
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
                    typeInfoPtr = ErsEngine.ERS_TypeRegistry_RegisterStruct(nameByte);
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
                    UInt32 typeInt = GetBuiltinType(field, fieldInfo.Type);
                    fixed(byte* nameByte = name.ToUtf8NullTerminated())
                    {
                        ErsEngine.ERS_TypeInfo_AddField(typeInfoPtr, nameByte, typeInt, offset, fieldInfo.ReadOnly);
                    }
                }
            }
        }

        private static UInt32 GetBuiltinType(FieldInfo field, UInt32? typeInt)
        {
            if (typeInt != null)
                return (UInt32)typeInt.Value;

            return field.FieldType switch {
                Type t when t == typeof(float)     => (UInt32)BuiltinType.Float32,
                Type t when t == typeof(bool)      => (UInt32)BuiltinType.Bool,
                Type t when t == typeof(byte)      => (UInt32)BuiltinType.UInt8,
                Type t when t == typeof(Int32)     => (UInt32)BuiltinType.Int32,
                Type t when t == typeof(UInt32)    => (UInt32)BuiltinType.UInt32,
                Type t when t == typeof(Int64)     => (UInt32)BuiltinType.Int64,
                Type t when t == typeof(UInt64)    => (UInt32)BuiltinType.UInt64,
                Type t when t == typeof(Entity)    => (UInt32)BuiltinType.Entity,
                Type t when t == typeof(string)    => (UInt32)BuiltinType.String,
                Type t when t == typeof(Vector2)   => (UInt32)BuiltinType.Vector2,
                Type t when t == typeof(Vector3)   => (UInt32)BuiltinType.Vector3,
                Type t when t == typeof(Vector4)   => (UInt32)BuiltinType.Vector4,
                Type t when t == typeof(Ers.Color) => (UInt32)BuiltinType.Color,
                _ => throw new NotSupportedException($"Field of type ${field.FieldType.Name} is not supported"),
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

    /// <summary>
    /// Type information of a type in ERS.
    /// </summary>
    public readonly struct TypeInfo
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal TypeInfo(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// The name of the type.
        /// </summary>
        public readonly string Name
        {
            get {
                string? result = Marshal.PtrToStringAnsi(ErsEngine.ERS_TypeInfo_Get_Name(CorePtr));
                Debug.Assert(result != null);
                return result;
            }
        }

        /// <summary>
        /// The ID of the type.
        /// </summary>
        public readonly uint ID => ErsEngine.ERS_TypeInfo_Get_ID(CorePtr);

        /// <summary>
        /// The size of the type in bytes.
        /// </summary>
        public readonly nuint Size => ErsEngine.ERS_TypeInfo_Get_Size(CorePtr);

        /// <summary>
        /// The number of fields in the type.
        /// </summary>
        public readonly nuint FieldCount => ErsEngine.ERS_TypeInfo_Fields_Count(CorePtr);

        /// <summary>
        /// Get a <see cref="Field"/> of the type by its index.
        /// </summary>
        /// <param name="index">The index of the field.</param>
        /// <returns></returns>
        public readonly Field GetField(nuint index) { return new(ErsEngine.ERS_TypeInfo_Get_Field(CorePtr, index)); }

        /// <summary>
        /// Get a list of all fields of the type.
        /// </summary>
        /// <returns></returns>
        public readonly Field[] GetFields()
        {
            Field[] fields = new Field[FieldCount];
            for (nuint i = 0; i < (nuint)fields.Length; i++)
            {
                IntPtr ptr = ErsEngine.ERS_TypeInfo_Get_Field(CorePtr, i);
                fields[i]  = new Field(ptr);
            }
            return fields;
        }
    }

    /// <summary>
    /// Field information about fields in <see cref="Ers.TypeInfo"/>.
    /// </summary>
    public readonly struct Field
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal Field(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// The byte offset of the field.
        /// </summary>
        public readonly nuint Offset => ErsEngine.ERS_TypeInfo_Field_Get_Offset(CorePtr);

        /// <summary>
        /// The type of the field.
        /// </summary>
        public readonly Ers.TypeInfo TypeInfo => new(ErsEngine.ERS_TypeInfo_Field_Get_TypeInfo(CorePtr));

        /// <summary>
        /// The name of the field.
        /// </summary>
        public readonly string Name
        {
            get {
                string? result = Marshal.PtrToStringAnsi(ErsEngine.ERS_TypeInfo_Field_Get_Name(CorePtr));
                Debug.Assert(result != null);
                return result;
            }
        }

        /// <summary>
        /// Whether the field is read-only.
        /// </summary>
        public readonly bool IsReadOnly => ErsEngine.ERS_TypeInfo_Field_Get_ReadOnly(CorePtr);
    }

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
        /// The type ID of the field, see <see cref="BuiltinType"/>.
        /// </summary>
        public readonly UInt32? Type;
        /// <summary>
        /// Whether the field is read-only.
        /// </summary>
        public readonly bool ReadOnly;

        /// <summary>
        /// Mark a field to have available field information.
        ///
        /// <para>NOTE: Entities will be seen as UInt64 unless explicitly defining them as Entity.</para>
        /// </summary>
        public FieldInfoAttribute()
        {
            Name     = null;
            Type     = null;
            ReadOnly = false;
        }

        /// <summary>
        /// Mark a field to have available field information.
        ///
        /// <para>NOTE: Entities will be seen as UInt64 unless explicitly defining them as Entity.</para>
        /// </summary>
        /// <param name="name">The name of the field.</param>
        /// <param name="readOnly">Whether the field is read-only.</param>
        public FieldInfoAttribute(string? name, bool readOnly = false)
        {
            Name     = name;
            Type     = null;
            ReadOnly = readOnly;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="type">The type ID of the field, see <see cref="BuiltinType"/></param>
        /// <param name="readOnly">Whether the field is read-only.</param>
        public FieldInfoAttribute(BuiltinType type, bool readOnly = false)
        {
            Name     = null;
            Type = (UInt32?)type;
            ReadOnly = readOnly;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="type">The type ID of the field, see <see cref="BuiltinType"/></param>
        /// <param name="readOnly">Whether the field is read-only.</param>
        public FieldInfoAttribute(UInt32 type, bool readOnly = false)
        {
            Name     = null;
            Type     = type;
            ReadOnly = readOnly;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="name">The name of the field.</param>
        /// <param name="type">The type ID of the field, see <see cref="BuiltinType"/></param>
        /// <param name="readOnly">Whether the field is read-only.</param>
        public FieldInfoAttribute(string name, BuiltinType type, bool readOnly = false)
        {
            Name     = name;
            Type = (UInt32?)type;
            ReadOnly = readOnly;
        }

        /// <summary>
        /// Mark a field to have available field information.
        /// </summary>
        /// <param name="name">The name of the field.</param>
        /// <param name="type">The type ID of the field, see <see cref="BuiltinType"/></param>
        /// <param name="readOnly">Whether the field is read-only.</param>
        public FieldInfoAttribute(string name, UInt32 type, bool readOnly = false)
        {
            Name     = name;
            Type     = type;
            ReadOnly = readOnly;
        }
    }

    /// <summary>
    /// <see cref="Ers.TypeInfo"/> types that are built into ERS.
    /// </summary>
    public enum BuiltinType : uint
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
        /// An 8-bit unsigned integer (<see cref="byte"/>).
        /// </summary>
        UInt8 = 2,
        /// <summary>
        /// A 32-bit signed integer (<see cref="int"/>).
        /// </summary>
        Int32 = 3,
        /// <summary>
        /// A 32-bit unsigned integer (<see cref="System.UInt32"/>).
        /// </summary>
        UInt32 = 4,
        /// <summary>
        /// A 64-bit signed integer (<see cref="System.Int64"/>).
        /// </summary>
        Int64 = 5,
        /// <summary>
        /// A 64-bit unsigned integer (<see cref="System.UInt64"/>).
        /// </summary>
        UInt64 = 6,
        /// <summary>
        /// An ERS Entity.
        /// </summary>
        Entity = 7,
        /// <summary>
        /// A list of any known registered type.
        /// </summary>
        List = 8,
        /// <summary>
        /// A string.
        /// </summary>
        String = 9,
        /// <summary>
        /// A 2D vector.
        /// </summary>
        Vector2 = 10,
        /// <summary>
        /// A 3D vector.
        /// </summary>
        Vector3 = 11,
        /// <summary>
        /// A 4D vector.
        /// </summary>
        Vector4 = 12,
        /// <summary>
        /// An RGBA color (<see cref="Ers.Color"/>).
        /// </summary>
        Color = 13,
    }
}
