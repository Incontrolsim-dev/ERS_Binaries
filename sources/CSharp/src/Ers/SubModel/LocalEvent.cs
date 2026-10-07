using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ers
{
    public interface ILocalEvent<T>
        where T : struct, ILocalEvent<T> {

        public abstract void OnEvent();

        public void Serialization(Serializer serializer)
        {
            // Use Unsafe.Unbox to get a ref to the data inside the boxed struct
            // This allows both reading and writing to the actual stored data
            ref T self = ref Unsafe.Unbox<T>((object)this);
            LocalEventSerializationHelper<T>.SerializeFields(ref self, serializer);
        }
    }

    /// <summary>
    /// Helper class that generates and caches field serialization logic for ILocalEvent types.
    /// Uses reflection once per type to build efficient serialization delegates.
    /// </summary>
    internal static class LocalEventSerializationHelper<T>
        where T : struct, ILocalEvent<T>
    {
        private delegate void SerializeFieldsRef(ref T value, Serializer serializer);
        private static readonly SerializeFieldsRef? _serializeFieldsRefDelegate;

        static LocalEventSerializationHelper() { _serializeFieldsRefDelegate = BuildSerializeFieldsDelegate(); }

        private static SerializeFieldsRef? BuildSerializeFieldsDelegate()
        {
            Type tType = typeof(T);
            var fields = tType.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);

            if (fields.Length == 0)
                return null;

            // Build a DynamicMethod that serializes all fields
            var dm = new DynamicMethod(
                name: $"SerializeFields_{tType.FullName}", returnType: typeof(void),
                parameterTypes: new[] { tType.MakeByRefType(), typeof(Serializer) }, owner: typeof(LocalEventSerializationHelper<T>),
                skipVisibility: true);

            var il = dm.GetILGenerator();

            // Get the generic Serialize<TField> method from Serializer
            var serializeMethod =
                typeof(Serializer)
                    .GetMethods(BindingFlags.Public | BindingFlags.Instance)
                    .FirstOrDefault(
                        m => m.Name == "Serialize" && m.IsGenericMethodDefinition && m.GetParameters().Length == 2 &&
                             m.GetParameters()[0].ParameterType == typeof(string) && m.GetParameters()[1].ParameterType.IsByRef);

            if (serializeMethod == null)
                throw new InvalidOperationException("Could not find Serialize<T>(string, ref T) method on Serializer.");

            foreach (var field in fields)
            {
                // Skip backing fields for auto-properties and compiler-generated fields
                if (field.Name.StartsWith("<") || field.GetCustomAttribute<CompilerGeneratedAttribute>() != null)
                    continue;

                // Get the specific Serialize<FieldType> method
                var fieldSerializeMethod = serializeMethod.MakeGenericMethod(field.FieldType);

                // Load serializer (arg 1)
                il.Emit(OpCodes.Ldarg_1);

                // Load field name as string
                il.Emit(OpCodes.Ldstr, field.Name);

                // Load address of the field from ref T (arg 0)
                il.Emit(OpCodes.Ldarg_0);
                il.Emit(OpCodes.Ldflda, field);

                // Call serializer.Serialize<FieldType>(fieldName, ref fieldValue)
                il.Emit(OpCodes.Callvirt, fieldSerializeMethod);
            }

            il.Emit(OpCodes.Ret);

            return (SerializeFieldsRef)dm.CreateDelegate(typeof(SerializeFieldsRef));
        }

        public static void SerializeFields(ref T value, Serializer serializer)
        {
            _serializeFieldsRefDelegate?.Invoke(ref value, serializer);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct LocalEventNativeData
    {
        public delegate* unmanaged[Cdecl]<nint, void> Callback;
        public delegate* unmanaged[Cdecl]<nint, void> Destructor;
        public delegate* unmanaged[Cdecl]<nint, nint, void> Serialize;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct LocalEventNative
    {
        public IntPtr ContextHandle;
        public LocalEventNativeData* NativeDataPtr;
    }
}