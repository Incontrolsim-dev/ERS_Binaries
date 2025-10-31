using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// Node for serialization operations within ScriptBehavior components.
    /// Use this to save and load custom data in ScriptBehavior.Serialization() method.
    /// </summary>
    public class Serializer
    {
        private readonly nint coreHandle;

        internal Serializer(nint coreHandle) { this.coreHandle = coreHandle; }

        /// <summary>
        /// Check if this node is being used for writing (saving) or reading (loading).
        /// </summary>
        /// <returns>True if writing, false if reading.</returns>
        public bool IsWriting() { return Engine.ErsEngine.ERS_Serializer_IsWriting(coreHandle); }

        /// <summary>
        /// Serialize a UInt64 value.
        /// </summary>
        public void Serialize(string key, ref UInt64 value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(UInt64* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeUInt64(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize an Int64 value.
        /// </summary>
        public void Serialize(string key, ref Int64 value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(Int64* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeInt64(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize a UInt32 value.
        /// </summary>
        public void Serialize(string key, ref UInt32 value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(UInt32* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeUInt32(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize an Int32 value.
        /// </summary>
        public void Serialize(string key, ref Int32 value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(Int32* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeInt32(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize a double value.
        /// </summary>
        public void Serialize(string key, ref double value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(double* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeDouble(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize a bool value.
        /// </summary>
        public void Serialize(string key, ref bool value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(bool* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeBool(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize a float value.
        /// </summary>
        public void Serialize(string key, ref float value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(float* valuePtr = &value)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeFloat(coreHandle, keyByte, (nint)valuePtr);
                }
            }
        }

        /// <summary>
        /// Serialize a string value.
        /// </summary>
        public void Serialize(string key, ref string value)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8)
                {
                    if (IsWriting())
                    {
                        if (value == null)
                            return;

                        // Writing: convert string to UTF8 and pass to API
                        var valueUtf8 = value.ToUtf8NullTerminated();
                        int length    = value.Length;
                        fixed(byte* valueByte = valueUtf8)
                        {
                            Engine.ErsEngine.ERS_Serializer_SerializeString(coreHandle, keyByte, (byte*)&valueByte, (nint)(&length));
                        }
                    }
                    else
                    {
                        // Reading: API will allocate and return string
                        byte* valuePtr = null;
                        IntPtr length  = IntPtr.Zero;
                        Engine.ErsEngine.ERS_Serializer_SerializeString(coreHandle, keyByte, (byte*)&valuePtr, (IntPtr)(&length));

                        if (valuePtr != null && length.ToInt32() > 0)
                        {
                            value = System.Text.Encoding.UTF8.GetString(valuePtr, length.ToInt32());
                            // Free the memory allocated by the API using the matching API function
                            Engine.ErsEngine.ERS_STRING_DISPOSE((nint)valuePtr);
                        }
                        else
                        {
                            value = "";
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Get the size of the current array in the serialization context.
        /// </summary>
        public int GetArraySize() { return Engine.ErsEngine.ERS_Serializer_GetArraySize(coreHandle); }

        /// <summary>
        /// Push a named object onto the serialization stack.
        /// </summary>
        public void PushObject(string key)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8)
                {
                    Engine.ErsEngine.ERS_Serializer_PushObject(coreHandle, keyByte);
                }
            }
        }

        /// <summary>
        /// Pop an object from the serialization stack.
        /// </summary>
        public void PopObject() { Engine.ErsEngine.ERS_Serializer_PopObject(coreHandle); }

        /// <summary>
        /// Push a named array onto the serialization stack.
        /// When writing, size should be set to the array size before calling.
        /// When reading, size will be set to the loaded array size after calling.
        /// </summary>
        public void PushArray(string key, ref int size)
        {
            var keyUtf8 = key.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* keyByte = keyUtf8) fixed(int* sizePtr = &size)
                {
                    Engine.ErsEngine.ERS_Serializer_PushArray(coreHandle, keyByte, (nint)sizePtr);
                }
            }
        }

        /// <summary>
        /// Pop an array from the serialization stack.
        /// </summary>
        public void PopArray() { Engine.ErsEngine.ERS_Serializer_PopArray(coreHandle); }

        /// <summary>
        /// Set the current array element by index.
        /// </summary>
        public void SetObject(int index) { Engine.ErsEngine.ERS_Serializer_SetObject(coreHandle, index); }

        // ----------------- Per-type thunks (uniform signature) -----------------
        private static unsafe void Thunk_UInt64(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<ulong>((void*)p));
        private static unsafe void Thunk_Int64(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<long>((void*)p));
        private static unsafe void Thunk_UInt32(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<uint>((void*)p));

        private static unsafe void Thunk_Int32(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<int>((void*)p));

        private static unsafe void Thunk_Double(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<double>((void*)p));

        private static unsafe void Thunk_Float(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<float>((void*)p));

        private static unsafe void Thunk_Bool(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<bool>((void*)p));

        private static unsafe void Thunk_String(Serializer @this, string key, IntPtr p) =>
            @this.Serialize(key, ref Unsafe.AsRef<string>((void*)p));

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private static ulong TypeId<T>() => (ulong) typeof(T).TypeHandle.Value;

        // ----------------- Dispatch table via managed function pointers -----------------

        // Dictionary cannot contain function-pointer types; store as nint instead.
        // Key: type-id (nint), Value: function pointer as nint
        private static unsafe readonly Dictionary<ulong, nint> PrimitiveDispatchMapKey = new() {
            [TypeId<ulong>()]  = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_UInt64,
            [TypeId<long>()]   = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_Int64,
            [TypeId<uint>()]   = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_UInt32,
            [TypeId<int>()]    = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_Int32,
            [TypeId<double>()] = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_Double,
            [TypeId<float>()]  = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_Float,
            [TypeId<bool>()]   = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_Bool,
            [TypeId<string>()] = (nint)(delegate * managed<Serializer, string, nint, void>)&Thunk_String,
        };
        /// <summary>
        /// Generic serialize method that handles custom types, collections, and falls back to primitives.
        /// This method will be selected when no explicit overload matches.
        /// Note: This method should not be called for collection types - use the specific overloads instead.
        /// </summary>
        public void Serialize<T>(string key, ref T value)
        {
            Type tType = typeof(T);

            // Handle recursive collection - dispatch to specific overload
            if (tType.IsGenericType)
            {
                Type gType = tType.GetGenericTypeDefinition();
                // Only dispatch if it's a known collection type
                if (gType == typeof(List<>) || gType == typeof(Queue<>) || gType == typeof(Dictionary<, >))
                {
                    DispatchPreservingRefKey(key, ref value);
                    return;
                }
            }

            // Call Ers-Core to serialize primitive values
            unsafe
            {
                ulong typeKey = (ulong) typeof(T).TypeHandle.Value;
                if (PrimitiveDispatchMapKey.TryGetValue(typeKey, out var fpAsInt))
                {
                    var fp = (delegate * managed<Serializer, string, nint, void>)fpAsInt;
                    fixed(T* p = &value)
                    {
                        fp(this, key, (nint)p);
                    }
                    return;
                }
            }

            // Check for custom types with Serialization method
            SerializeCustomTypeKey(key, ref value);
        }

        private T DefaultOrDefaultConstruct<T>()
        {
            T value;
            Type tType = typeof(T);
            if (tType.IsValueType || tType == typeof(string))
            {
                value = default(T)!;
            }
            else
            {
                value = (T)Activator.CreateInstance(tType)!;
            }
            return value;
        }

        public static Delegate GetCustomSerializationMethod<T>()
        {
            Type tType = typeof(T);
            lock (CustomTypeSerializationCache)
            {
                if (!CustomTypeSerializationCache.TryGetValue(tType, out var actionDelegate))
                {
                    // Look for public Serialization method with Serializer parameter
                    var method = tType.GetMethod(
                        "Serialization", BindingFlags.Public | BindingFlags.Instance, null, new Type[] { typeof(Serializer) }, null);

                    // If no Serialization method found, return null
                    if (method == null)
                    {
                        return null;
                    }

                    // Validate signature: instance method with single parameter: Serializer
                    if (method.IsStatic)
                        throw new InvalidOperationException($"Custom serializer on {tType} must be an instance method.");
                    var pars = method.GetParameters();
                    if (pars.Length != 1 || pars[0].ParameterType != typeof(Serializer))
                        throw new InvalidOperationException($"Serializer method {method} must have signature 'void M(Serializer)'.");
                    if (method.ReturnType != typeof(void))
                        throw new InvalidOperationException($"Serializer method {method} must return void.");

                    // DynamicMethod:  void Thunk(ref T, Serializer)
                    var dm = new DynamicMethod(
                        name: $"RefInstanceThunk_{tType.FullName}_{method.Name}", returnType: typeof(void),
                        parameterTypes: new[] { tType.MakeByRefType(), typeof(Serializer) }, owner: method.DeclaringType!,
                        skipVisibility: true);

                    var il = dm.GetILGenerator();

                    if (tType.IsValueType)
                    {
                        // Value type path:
                        // Stack: &T, Serializer
                        il.Emit(OpCodes.Ldarg_0);      // &T
                        il.Emit(OpCodes.Ldarg_1);      // Serializer
                        il.Emit(OpCodes.Call, method); // call instance void M(Serializer)
                    }
                    else
                    {
                        // Reference type path:
                        // Need the *object reference*, not &T
                        il.Emit(OpCodes.Ldarg_0);          // &T  (managed ref to the variable holding the ref)
                        il.Emit(OpCodes.Ldind_Ref);        // T   (load the object reference from &T)
                        il.Emit(OpCodes.Ldarg_1);          // Serializer
                        il.Emit(OpCodes.Callvirt, method); // call instance void M(Serializer)
                    }

                    il.Emit(OpCodes.Ret);

                    ByRefSerializeOnCustomType<T> customDelegate =
                        (ByRefSerializeOnCustomType<T>)dm.CreateDelegate(typeof(ByRefSerializeOnCustomType<T>));
                    actionDelegate = customDelegate;
                    CustomTypeSerializationCache.Add(tType, actionDelegate);
                }
                return actionDelegate;
            }
        }

        // Dispatch methods that preserve ref semantics for custom types
        private void SerializeCustomTypeKey<T>(string key, ref T value)
        {
            if (IsWriting() && value == null)
            {
                return;
            }

            Delegate del = GetCustomSerializationMethod<T>();
            if (del == null)
            {
                return; // Custom type is not supported
            }

            // When reading, create a new instance to populate
            if (!IsWriting())
            {
                value = DefaultOrDefaultConstruct<T>();
            }

            PushObject(key);
            ((ByRefSerializeOnCustomType<T>)del)(ref value, this);
            PopObject();
        }

        private void SerializeCustomTypeIndex<T>(int index, ref T value)
        {
            if (IsWriting() && value == null)
            {
                return;
            }

            Delegate del = GetCustomSerializationMethod<T>();
            if (del == null)
            {
                return; // Custom type is not supported
            }

            // When reading, create a new instance to populate
            if (!IsWriting())
            {
                value = DefaultOrDefaultConstruct<T>();
            }

            SetObject(index);
            ((ByRefSerializeOnCustomType<T>)del)(ref value, this);
            PopObject();
        }

        // ----------------- Per-type thunks for keyless array serialization -----------------
        private static unsafe void ThunkValue_UInt64(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueUInt64(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_Int64(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueInt64(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_UInt32(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueUInt32(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_Int32(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueInt32(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_Double(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueDouble(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_Float(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueFloat(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_Bool(Serializer @this, int index, IntPtr p) =>
            Engine.ErsEngine.ERS_Serializer_SerializeValueBool(@this.coreHandle, (nuint)index, p);

        private static unsafe void ThunkValue_String(Serializer @this, int index, IntPtr p)
        {
            ref string strRef = ref Unsafe.AsRef<string>((void*)p);
            if (@this.IsWriting())
            {
                var valueUtf8 = strRef.ToUtf8NullTerminated();
                fixed(byte* valueByte = valueUtf8)
                {
                    Engine.ErsEngine.ERS_Serializer_SerializeValueString(@this.coreHandle, (nuint)index, valueByte, IntPtr.Zero);
                }
            }
            else
            {
                byte* valuePtr = null;
                IntPtr length  = IntPtr.Zero;
                Engine.ErsEngine.ERS_Serializer_SerializeValueString(@this.coreHandle, (nuint)index, (byte*)&valuePtr, (IntPtr)(&length));

                if (valuePtr != null && length.ToInt32() > 0)
                {
                    strRef = System.Text.Encoding.UTF8.GetString(valuePtr, length.ToInt32());
                    Engine.ErsEngine.ERS_STRING_DISPOSE((nint)valuePtr);
                }
                else
                {
                    strRef = "";
                }
            }
        }

        // Dispatch table for keyless array serialization
        private static unsafe readonly Dictionary<ulong, nint> PrimitiveDispatchMapIndex = new() {
            [TypeId<ulong>()]  = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_UInt64,
            [TypeId<long>()]   = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_Int64,
            [TypeId<uint>()]   = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_UInt32,
            [TypeId<int>()]    = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_Int32,
            [TypeId<double>()] = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_Double,
            [TypeId<float>()]  = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_Float,
            [TypeId<bool>()]   = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_Bool,
            [TypeId<string>()] = (nint)(delegate * managed<Serializer, int, nint, void>)&ThunkValue_String,
        };

        private delegate void ByRefActionIndex<T>(Serializer s, int index, ref T arg);
        private delegate void ByRefActionKey<T>(Serializer s, string index, ref T arg);
        public delegate void ByRefSerializeOnCustomType<T>(ref T value, Serializer s);

        // Cache index and key based generic dispatch methods
        private static readonly Dictionary<Type, Delegate> GenericDispatchMapIndex = new();
        private static readonly Dictionary<Type, Delegate> GenericDispatchMapKey   = new();

        // Cache for custom type serialization methods
        private static readonly Dictionary<Type, Delegate> CustomTypeSerializationCache = new();

        private void DispatchPreservingRefIndex<T>(int index, ref T value)
        {
            // T is known (at this callsite) to be List<T>
            var constructedT = typeof(T);
            Type gType       = constructedT.GetGenericTypeDefinition();

            ByRefActionIndex<T> storedDelegate;

            lock (GenericDispatchMapIndex)
            {
                if (!GenericDispatchMapIndex.TryGetValue(constructedT, out var del))
                {
                    if (gType == typeof(List<>))
                    {
                        // Extract TElem from List<T>
                        var elemType = constructedT.GetGenericArguments()[0];

                        // Close DispatchListCore<T, T>
                        var closed = typeof(Serializer)
                                         .GetMethod(
                                             nameof(DispatchSerializeListIndex),
                                             BindingFlags.Instance | BindingFlags.NonPublic)!.MakeGenericMethod(constructedT, elemType);

                        var delType                           = typeof(ByRefActionIndex<>).MakeGenericType(constructedT);
                        del                                   = closed.CreateDelegate(delType);
                        GenericDispatchMapIndex[constructedT] = del;
                    }
                    else if (gType == typeof(Queue<>))
                    {
                        // Extract TElem from List<T>
                        var elemType = constructedT.GetGenericArguments()[0];

                        // Close DispatchListCore<T, T>
                        var closed = typeof(Serializer)
                                         .GetMethod(
                                             nameof(DispatchSerializeQueueIndex),
                                             BindingFlags.Instance | BindingFlags.NonPublic)!.MakeGenericMethod(constructedT, elemType);

                        var delType                           = typeof(ByRefActionIndex<>).MakeGenericType(constructedT);
                        del                                   = closed.CreateDelegate(delType);
                        GenericDispatchMapIndex[constructedT] = del;
                    }
                    else if (gType == typeof(Dictionary<, >))
                    {
                        // Extract TElem from List<T>
                        var elemType  = constructedT.GetGenericArguments()[0];
                        var elemType2 = constructedT.GetGenericArguments()[1];

                        var closed =
                            typeof(Serializer)
                                .GetMethod(
                                    nameof(DispatchSerializeDictionaryIndex),
                                    BindingFlags.Instance | BindingFlags.NonPublic)!.MakeGenericMethod(constructedT, elemType, elemType2);

                        var delType                           = typeof(ByRefActionIndex<>).MakeGenericType(constructedT);
                        del                                   = closed.CreateDelegate(delType);
                        GenericDispatchMapIndex[constructedT] = del;
                    }
                    else
                    {
                        throw new InvalidOperationException($"Unsupported generic collection type: {constructedT}");
                    }
                }

                storedDelegate = (ByRefActionIndex<T>)del;
            }

            // Invoke with true ref semantics
            storedDelegate(this, index, ref value);
        }

        private void DispatchPreservingRefKey<T>(string key, ref T value)
        {
            // T is known (at this callsite) to be List<T>
            var constructedT = typeof(T);
            Type gType       = constructedT.GetGenericTypeDefinition();

            ByRefActionKey<T> storedDelegate;

            lock (GenericDispatchMapKey)
            {
                if (!GenericDispatchMapKey.TryGetValue(constructedT, out var del))
                {
                    if (gType == typeof(List<>))
                    {
                        // Extract TElem from List<T>
                        var elemType = constructedT.GetGenericArguments()[0];

                        // Close DispatchListCore<T, T>
                        var closed = typeof(Serializer)
                                         .GetMethod(
                                             nameof(DispatchSerializeListKey),
                                             BindingFlags.Instance | BindingFlags.NonPublic)!.MakeGenericMethod(constructedT, elemType);

                        var delType                         = typeof(ByRefActionKey<>).MakeGenericType(constructedT);
                        del                                 = closed.CreateDelegate(delType);
                        GenericDispatchMapKey[constructedT] = del;
                    }
                    else if (gType == typeof(Queue<>))
                    {
                        // Extract TElem from List<T>
                        var elemType = constructedT.GetGenericArguments()[0];

                        // Close DispatchListCore<T, T>
                        var closed = typeof(Serializer)
                                         .GetMethod(
                                             nameof(DispatchSerializeQueueKey),
                                             BindingFlags.Instance | BindingFlags.NonPublic)!.MakeGenericMethod(constructedT, elemType);

                        var delType                         = typeof(ByRefActionKey<>).MakeGenericType(constructedT);
                        del                                 = closed.CreateDelegate(delType);
                        GenericDispatchMapKey[constructedT] = del;
                    }
                    else if (gType == typeof(Dictionary<, >))
                    {
                        // Extract TElem from List<T>
                        var elemType  = constructedT.GetGenericArguments()[0];
                        var elemType2 = constructedT.GetGenericArguments()[1];

                        var closed =
                            typeof(Serializer)
                                .GetMethod(
                                    nameof(DispatchSerializeDictionaryKey),
                                    BindingFlags.Instance | BindingFlags.NonPublic)!.MakeGenericMethod(constructedT, elemType, elemType2);

                        var delType                         = typeof(ByRefActionKey<>).MakeGenericType(constructedT);
                        del                                 = closed.CreateDelegate(delType);
                        GenericDispatchMapKey[constructedT] = del;
                    }
                    else
                    {
                        throw new InvalidOperationException($"Unsupported generic collection type: {constructedT}");
                    }
                }
                storedDelegate = (ByRefActionKey<T>)del;
            }

            // Invoke with true ref semantics
            storedDelegate(this, key, ref value);
        }

        // This method runs with T == List<TElem>, so the ref cast is identity.
        private void DispatchSerializeListIndex<T, TElem>(int index, ref T value) =>
            Serialize(index, ref Unsafe.As<T, List<TElem>>(ref value));

        // This method runs with T == List<TElem>, so the ref cast is identity.
        private void DispatchSerializeListKey<T, TElem>(string key, ref T value) =>
            Serialize(key, ref Unsafe.As<T, List<TElem>>(ref value));

        // This method runs with T == Queue<TElem>, so the ref cast is identity.
        private void DispatchSerializeQueueIndex<T, TElem>(int index, ref T value) =>
            Serialize(index, ref Unsafe.As<T, Queue<TElem>>(ref value));

        // This method runs with T == Queue<TElem>, so the ref cast is identity.
        private void DispatchSerializeQueueKey<T, TElem>(string key, ref T value) =>
            Serialize(key, ref Unsafe.As<T, Queue<TElem>>(ref value));

        // This method runs with T == Dictionary<TElem, Elem2>, so the ref cast is identity.
        private void DispatchSerializeDictionaryIndex<T, TElem, Elem2>(int index, ref T value) =>
            Serialize(index, ref Unsafe.As<T, Dictionary<TElem, Elem2>>(ref value));

        // This method runs with T == Dictionary<TElem, Elem2>, so the ref cast is identity.
        private void DispatchSerializeDictionaryKey<T, TElem, Elem2>(string key, ref T value) =>
            Serialize(key, ref Unsafe.As<T, Dictionary<TElem, Elem2>>(ref value));

        // Private helper method for serializing array elements without keys
        private void Serialize<T>(int index, ref T value)
        {
            // Try keyless serialization for primitives using dispatch table
            unsafe
            {
                ulong typeKey = (ulong) typeof(T).TypeHandle.Value;
                if (PrimitiveDispatchMapIndex.TryGetValue(typeKey, out var fpAsInt))
                {
                    var fp = (delegate * managed<Serializer, int, nint, void>)fpAsInt;
                    fixed(T* p = &value)
                    {
                        fp(this, index, (nint)p);
                    }
                    return;
                }
            }

            // Handle arrays inline (can't dispatch to array overload due to C# generic constraints)
            Type tType = typeof(T);

            // Handle generic collections
            if (tType.IsGenericType)
            {
                DispatchPreservingRefIndex(index, ref value);
                return;
            }

            // Check for custom types with Serialization method
            SerializeCustomTypeIndex(index, ref value);
        }

        private void Serialize<T>(int index, ref List<T> list)
        {
            int size = IsWriting() ? list?.Count ?? 0 : 0;
            // Always push array element when in nested context (even if empty) to maintain structure
            unsafe
            {
                Engine.ErsEngine.ERS_Serializer_PushArrayElement(coreHandle, (nuint)index, (nint)(void*)&size);
            }

            if (!IsWriting())
            {
                if (list == null)
                    list = new List<T>();
                list.Clear();
            }

            for (int i = 0; i < size; i++)
            {
                if (IsWriting())
                    Serialize(i, ref CollectionsMarshal.AsSpan(list)[i]);
                else
                {
                    // For reference types (including arrays), start with null - Serialize will create proper instance
                    // For value types, need default instance
                    Type tType = typeof(T);
                    T value    = tType.IsValueType ? (T)Activator.CreateInstance(tType)! : default(T)!;
                    Serialize(i, ref value);
                    list.Add(value);
                }
            }

            PopArray();
        }

        private void Serialize<T>(int index, ref Queue<T> queue)
        {
            int size = IsWriting() ? queue?.Count ?? 0 : 0;
            // Always push array element when in nested context (even if empty) to maintain structure
            unsafe
            {
                Engine.ErsEngine.ERS_Serializer_PushArrayElement(coreHandle, (nuint)index, (nint)(void*)&size);
            }

            if (IsWriting())
            {
                Queue<T> queueCopy = new Queue<T>(queue);
                for (int i = 0; i < size; i++)
                {
                    T element = queueCopy.Dequeue();
                    Serialize(i, ref element);
                }
            }
            else
            {
                if (queue == null)
                    queue = new Queue<T>();
                queue.Clear();
                for (int i = 0; i < size; i++)
                {
                    // For reference types (including arrays), start with null - Serialize will create proper instance
                    // For value types, need default instance
                    Type tType = typeof(T);
                    T value    = tType.IsValueType ? (T)Activator.CreateInstance(tType)! : default(T)!;
                    Serialize(i, ref value);
                    queue.Enqueue(value);
                }
            }

            PopArray();
        }

        private void Serialize<TKey, TValue>(int index, ref Dictionary<TKey, TValue> dictionary)
        {
            int size = IsWriting() ? dictionary?.Count ?? 0 : 0;
            // Always push array element when in nested context (even if empty) to maintain structure
            unsafe
            {
                Engine.ErsEngine.ERS_Serializer_PushArrayElement(coreHandle, (nuint)index, (nint)(void*)&size);
            }

            if (IsWriting())
            {
                int i = 0;
                foreach (var kvp in dictionary)
                {
                    Engine.ErsEngine.ERS_Serializer_PushObjectElement(coreHandle, (nuint)i);
                    TKey dictKey     = kvp.Key;
                    TValue dictValue = kvp.Value;
                    Serialize("key", ref dictKey);
                    Serialize("value", ref dictValue);
                    PopObject();
                    i++;
                }
            }
            else
            {
                if (dictionary == null)
                    dictionary = new Dictionary<TKey, TValue>();
                dictionary.Clear();
                for (int i = 0; i < size; i++)
                {
                    Engine.ErsEngine.ERS_Serializer_PushObjectElement(coreHandle, (nuint)i);

                    // For reference types (including arrays), start with null - Serialize will create proper instance
                    // For value types, need default instance
                    Type keyType = typeof(TKey);
                    Type valType = typeof(TValue);
                    TKey k       = keyType.IsValueType ? (TKey)Activator.CreateInstance(keyType)! : default(TKey)!;
                    TValue v     = valType.IsValueType ? (TValue)Activator.CreateInstance(valType)! : default(TValue)!;

                    Serialize("key", ref k);
                    Serialize("value", ref v);
                    dictionary[k] = v;
                    PopObject();
                }
            }

            PopArray();
        }

        /// <summary>
        /// Serialize a List using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections.
        /// If the list is null or empty during writing, nothing is written.
        /// </summary>
        public void Serialize<T>(string key, ref List<T> list)
        {
            if (IsWriting() && (list == null || list.Count == 0))
            {
                // Skip writing null or empty lists
                return;
            }

            int size = IsWriting() ? list.Count : 0;
            PushArray(key, ref size);

            if (!IsWriting())
            {
                if (list == null)
                    list = DefaultOrDefaultConstruct<List<T>>();

                list.Clear();
            }

            for (int i = 0; i < size; i++)
            {
                if (IsWriting())
                {
                    Serialize(i, ref CollectionsMarshal.AsSpan(list)[i]);
                }
                else
                {
                    // For reference types (including arrays), start with null - Serialize will create proper instance
                    // For value types, need default instance
                    Type tType = typeof(T);
                    T value    = tType.IsValueType ? (T)Activator.CreateInstance(tType)! : default(T)!;
                    Serialize(i, ref value);
                    list.Add(value);
                }
            }

            PopArray();
        }

        /// <summary>
        /// Serialize a Queue using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections.
        /// If the queue is null or empty during writing, nothing is written.
        /// </summary>
        public void Serialize<T>(string key, ref Queue<T> queue)
        {
            if (IsWriting() && (queue == null || queue.Count == 0))
            {
                // Skip writing null or empty queues
                return;
            }

            int size = IsWriting() ? queue.Count : 0;
            PushArray(key, ref size);

            if (IsWriting())
            {
                Queue<T> queueCopy = new Queue<T>(queue);
                for (int i = 0; i < size; i++)
                {
                    T element = queueCopy.Dequeue();
                    Serialize(i, ref element);
                }
            }
            else
            {
                if (queue == null)
                    queue = DefaultOrDefaultConstruct<Queue<T>>();

                queue.Clear();
                for (int i = 0; i < size; i++)
                {
                    // For reference types (including arrays), start with null - Serialize will create proper instance
                    // For value types, need default instance
                    Type tType = typeof(T);
                    T value    = tType.IsValueType ? (T)Activator.CreateInstance(tType)! : default(T)!;
                    Serialize(i, ref value);
                    queue.Enqueue(value);
                }
            }

            PopArray();
        }

        /// <summary>
        /// Serialize a Dictionary using built-in array support. Handles both reading and writing automatically.
        /// Supports recursive serialization of nested collections as keys or values.
        /// If the dictionary is null or empty during writing, nothing is written.
        /// </summary>
        public void Serialize<TKey, TValue>(string key, ref Dictionary<TKey, TValue> dictionary)
        {
            if (IsWriting() && (dictionary == null || dictionary.Count == 0))
            {
                // Skip writing null or empty dictionaries
                return;
            }

            int size = IsWriting() ? dictionary.Count : 0;
            PushArray(key, ref size);

            if (IsWriting())
            {
                int i = 0;
                foreach (var kvp in dictionary)
                {
                    SetObject(i);

                    TKey dictKey     = kvp.Key;
                    TValue dictValue = kvp.Value;

                    Serialize("key", ref dictKey);
                    Serialize("value", ref dictValue);
                    PopObject();
                    i++;
                }
            }
            else
            {
                if (dictionary == null)
                    dictionary = DefaultOrDefaultConstruct<Dictionary<TKey, TValue>>();

                dictionary.Clear();
                for (int i = 0; i < size; i++)
                {
                    SetObject(i);

                    // For reference types (including arrays), start with null - Serialize will create proper instance
                    // For value types, need default instance
                    Type keyType = typeof(TKey);
                    Type valType = typeof(TValue);
                    TKey k       = keyType.IsValueType ? (TKey)Activator.CreateInstance(keyType)! : default(TKey)!;
                    TValue v     = valType.IsValueType ? (TValue)Activator.CreateInstance(valType)! : default(TValue)!;

                    Serialize("key", ref k);
                    Serialize("value", ref v);
                    dictionary[k] = v;
                    PopObject();
                }
            }

            PopArray();
        }

        /// <summary>
        /// Save a ModelContainer to a folder with separate files for each simulator.
        /// </summary>
        /// <param name="modelContainer">The ModelContainer to save.</param>
        /// <param name="folderPath">The path to the folder where files will be saved.</param>
        public static void SaveToFolder(ModelContainer modelContainer, string folderPath)
        {
            var folderPathUtf8 = folderPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* folderPathByte = folderPathUtf8)
                {
                    Engine.ErsEngine.ERS_Serializer_SaveToFolder(modelContainer.Data, folderPathByte);
                }
            }
        }

        /// <summary>
        /// Load a ModelContainer from a folder with separate files.
        /// </summary>
        /// <param name="folderPath">The path to the folder to load from.</param>
        /// <returns>A new ModelContainer instance loaded from the folder.</returns>
        public static ModelContainer LoadFromFolder(string folderPath)
        {
            var folderPathUtf8 = folderPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* folderPathByte = folderPathUtf8)
                {
                    IntPtr ptr            = Engine.ErsEngine.ERS_Serializer_LoadFromFolder(folderPathByte);
                    ModelContainer output = new ModelContainer(ptr);
                    Engine.ErsEngine.ERS_ModelContainer_Release(ptr);
                    return output;
                }
            }
        }

        // Compressed Archive  files)

        /// <summary>
        /// Save a ModelContainer to a compressed archive file.
        /// </summary>
        /// <param name="modelContainer">The ModelContainer to save.</param>
        /// <param name="archivePath">The path to the archive file.</param>
        /// <param name="compressionLevel">Zstd compression level (1-22, default 3).</param>
        public static void SaveToArchive(ModelContainer modelContainer, string archivePath, int compressionLevel = 3)
        {
            var archivePathUtf8 = archivePath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* archivePathByte = archivePathUtf8)
                {
                    Engine.ErsEngine.ERS_Serializer_SaveToArchive(modelContainer.Data, archivePathByte, compressionLevel);
                }
            }
        }

        /// <summary>
        /// Load a ModelContainer from a compressed archive file.
        /// </summary>
        /// <param name="archivePath">The path to the archive file to load.</param>
        /// <param name="useCache">If true, cache decompressed files for faster repeated loading (useful for parallel loading of same
        /// model).</param> <returns>A new ModelContainer instance loaded from the archive.</returns>
        public static ModelContainer LoadFromArchive(string archivePath, bool useCache = false)
        {
            var archivePathUtf8 = archivePath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* archivePathByte = archivePathUtf8)
                {
                    IntPtr ptr            = Engine.ErsEngine.ERS_Serializer_LoadFromArchive(archivePathByte, useCache);
                    ModelContainer output = new ModelContainer(ptr);
                    Engine.ErsEngine.ERS_ModelContainer_Release(ptr);
                    return output;
                }
            }
        }

        /// <summary>
        /// Clear the cached decompressed files for an archive.
        /// </summary>
        /// <param name="archivePath">The path to the archive whose cache should be cleared.</param>
        public static void ClearArchiveCache(string archivePath)
        {
            var archivePathUtf8 = archivePath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* archivePathByte = archivePathUtf8)
                {
                    Engine.ErsEngine.ERS_Serializer_ClearArchiveCache(archivePathByte);
                }
            }
        }
    }
}
