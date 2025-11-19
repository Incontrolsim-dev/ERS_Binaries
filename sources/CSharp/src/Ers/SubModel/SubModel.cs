using Ers.Engine;
using Ers;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Ers.Interpreter;
using System.Reflection;

namespace Ers
{
    /// <summary>
    /// A part of the model that contains the data and never runs in parallel.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct SubModel
    {
        /// <summary>
        /// The pointer to the core instance of this SubModel.
        /// </summary>
        public readonly IntPtr Data;

        /// <summary>
        /// The precision set in the ModelContainer where this SubModel is part of.
        /// </summary>
        public readonly ulong ModelPrecision => ErsEngine.ERS_SubModel_GetModelPrecision(Data);

        internal SubModel(IntPtr data) { Data = data; }

        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        private static void AddSubModelContext_FreeContext(nint data) { GCHandle.FromIntPtr(data).Free(); }

        /// <summary>
        /// Attach a data to the submodel.
        ///
        /// <para>
        /// This can be used as a useful optimization with sync events.
        /// Data can be attached to a submodel to easily access it during the event without needing to search for resources (e.g. getting an
        /// entity via <see cref="FindEntity(string)"/>).
        /// </para>
        /// </summary>
        /// <typeparam name="T">The type of component to attach to the submodel.</typeparam>
        /// <returns></returns>
        public T AddSubModelContext<T>()
            where T : class, new()
        {
            // Ensure it is registered
            RegisteredSubModelContext.RegisterSubModelContextTypeIndex<T>();

            T context       = new T();
            GCHandle handle = GCHandle.Alloc(context, GCHandleType.Normal);

            unsafe
            {

                var typeNameUtf8 = nameof(T).ToUtf8NullTerminated();
                fixed(byte* typeNameByte = typeNameUtf8)
                {
                    ErsEngine.ERS_SubModel_AddSubModelContext(
                        Data, RegisteredSubModelContext.GetSubModelContextTypeIndex<T>(), typeNameByte, (nint)handle,
                        &AddSubModelContext_FreeContext);
                }
            }

            return context;
        }

        /// <summary>
        /// Get a data attached to the submodel.
        /// If the context doesn't exist yet, it will be created automatically.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public readonly T GetSubModelContext<T>()
            where T : class, new()
        {
            // Ensure it is registered globally
            RegisteredSubModelContext.RegisterSubModelContextTypeIndex<T>();

            // Try to get existing context
            nint ptr = ErsEngine.ERS_SubModel_GetContext(Data, RegisteredSubModelContext.GetSubModelContextTypeIndex<T>());

            // If it doesn't exist (ptr is 0), create it
            if (ptr == IntPtr.Zero)
            {
                return AddSubModelContext<T>();
            }

            return (T)GCHandle.FromIntPtr(ptr).Target!;
        }

        public void AddInterpreterScriptComponentType() => ErsEngine.ERS_SubModel_AddInterpreterScriptComponentType(Data);

        public InterpreterVariable AddInterpreterScriptComponent(Entity entity)
        {
            return new InterpreterVariable(ErsEngine.ERS_SubModel_AddInterpreterScriptComponent(Data, entity));
        }

        public InterpreterVariable GetInterpreterScriptComponent(Entity entity)
        {
            return new InterpreterVariable(ErsEngine.ERS_SubModel_GetInterpreterScriptComponent(Data, entity));
        }

        public bool HasInterpreterScriptComponent(Entity entity)
        {
            return ErsEngine.ERS_SubModel_HasInterpreterScriptComponent(Data, entity);
        }

        /// <summary>
        /// Finds the entity with given entity name among the entities associated with the given submodel instance and return its Entity.
        /// <br/>
        /// If no Entity is found with the given name InvalidEntity Entity is returned.
        ///
        /// </summary>
        /// <param name="entityName">The name of the entity to search for.</param>
        /// <returns>The ID of the found entity.</returns>
        public readonly Entity FindEntity(string entityName)
        {
            var entityNameUtf8 = entityName.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* entityNameByte = entityNameUtf8)
                {
                    return ErsEngine.ERS_SubModel_FindEntity(Data, entityNameByte);
                }
            }
        }

        /// <summary>
        ///
        /// </summary>
        /// <param name="parent"></param>
        /// <param name="entityName"></param>
        /// <param name="root"></param>
        /// <returns></returns>
        public readonly Entity FindEntity(string entityName, Entity root)
        {
            var entityNameUtf8 = entityName.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* entityNameByte = entityNameUtf8)
                {
                    return ErsEngine.ERS_SubModel_FindEntity_Parent(Data, entityNameByte, root);
                }
            }
        }

        /// <summary>
        /// Create an entity.
        /// </summary>
        /// <param name="name">The name of the entity.</param>
        /// <returns>The ID of the created entity.</returns>
        public Entity CreateEntity(string name)
        {
            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    return ErsEngine.ERS_SubModel_Entity_Create_Name(Data, nameByte);
                }
            }
        }

        /// <summary>
        /// Create an entity with an attached parent.
        /// </summary>
        /// <param name="parentEntity">The ID of the parent entity.</param>
        /// <returns>The ID of the created entity.</returns>
        public Entity CreateEntity(Entity parentEntity)
        {
            Entity entity = ErsEngine.ERS_SubModel_Entity_Create(Data);
            ErsEngine.ERS_SubModel_Entity_Relation_Update_Parent(Data, entity, parentEntity);
            return entity;
        }

        /// <summary>
        /// Create an entity with an attached parent.
        /// </summary>
        /// <param name="parentEntity">The ID of the parent entity.</param>
        /// <param name="name">The name of the entity to create.</param>
        /// <returns>The ID of the created entity.</returns>
        public Entity CreateEntity(Entity parentEntity, string name)
        {
            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    return ErsEngine.ERS_SubModel_Entity_Create_Name_Parent(Data, nameByte, parentEntity);
                }
            }
        }

        /// <summary>
        /// Create an entity.
        /// </summary>
        /// <returns>The ID of the created entity.</returns>
        public Entity CreateEntity() => ErsEngine.ERS_SubModel_Entity_Create(Data);

        /// <summary>
        /// Check if the given entity exists.
        /// </summary>
        /// <param name="entity">The ID of the entity.</param>
        /// <returns>Whether the entity exists.</returns>
        public readonly bool EntityExists(Entity entity) => ErsEngine.ERS_SubModel_Entity_Exists(Data, entity);

        /// <summary>
        /// Destroys an entity and all the attached components.
        /// </summary>
        /// <param name="entity">The ID of the entity.</param>
        public void DestroyEntity(Entity entity) => ErsEngine.ERS_SubModel_Entity_Destroy(Data, entity);

        /// <summary>
        /// Modify the parent of an entity.
        /// </summary>
        /// <param name="entity">The ID of the entity to modify the parent of.</param>
        /// <param name="parent">The ID of the new parent.</param>
        public void UpdateParentOnEntity(Entity entity, Entity parent)
        {
            ErsEngine.ERS_SubModel_Entity_Relation_Update_Parent(Data, entity, parent);
        }

        /// <summary>
        /// Add a core or SDK component of the provided type to an entity.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        /// <param name="entity">The ID of the entity to add the component to.</param>
        /// <returns>The added component.</returns>
        /// <exception cref="ArgumentException">Thrown when trying to add a script behavior component to the entity.</exception>
        public Ref<T> AddComponent<T>(Entity entity)
            where T : unmanaged, IDACComponent
        {
            if (ComponentTraits<T>.IsScriptBehavior())
            {
                throw new ArgumentException("Script behaviors have to be added through AddScriptBehavior");
            }

            UInt32 typeId       = ComponentTraits<T>.GetComponentTypeId();
            IntPtr componentPtr = ErsEngine.ERS_SubModel_AddDataComponent(Data, entity, typeId);
            Ref<T> value        = ComponentUtil.CreateComponentRef<T>(componentPtr);
            value.Value         = new T();
            return value;
        }

        /// <summary>
        /// Add a ScriptBehavior component of the provided type to an entity.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        /// <param name="entity">The ID of the entity.</param>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <returns>The added component.</returns>
        public T AddComponent<T>(Entity entity, bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            UInt32 componentId = ComponentTraits<T>.GetComponentTypeId();
            T t                = new T() { ConnectedEntity = entity };
            GCHandle handle    = GCHandle.Alloc(t, GCHandleType.Normal);
            IntPtr handlePtr   = GCHandle.ToIntPtr(handle);
            ErsEngine.ERS_SubModel_AddScriptBehavior(Data, entity, componentId, handlePtr);
            return t;
        }

        /// <summary>
        /// Remove a component of the provided type from the entity.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        /// <param name="entity">The ID of the entity.</param>
        public void RemoveComponent<T>(Entity entity)
            where T : IComponentBase
        {
            UInt32 componentID = ComponentTraits<T>.GetComponentTypeId();
            if (ComponentTraits<T>.IsScriptBehavior())
            {
                GCHandle handle = GCHandle.FromIntPtr(ErsEngine.ERS_SubModel_RemoveScriptBehavior(Data, entity, componentID));
                handle.Free();
            }
            else
            {
                ErsEngine.ERS_SubModel_RemoveDataComponent(Data, entity, ComponentTraits<T>.GetComponentTypeId());
            }
        }

        /// <summary>
        /// Send an entity to simulator, used in sync events.
        /// </summary>
        /// <param name="toSimulator">The ID of the simulator to which to send the entity.</param>
        /// <param name="entity">The entity to send.</param>
        /// <returns>A <see cref="SentEntity"/>, which will need to be converted to a regular entity.</returns>
        public SentEntity SendEntity(Int32 toSimulator, Entity entity)
        {
            return new SentEntity(ErsEngine.ERS_SubModel_SendEntityTo(Data, toSimulator, entity));
        }

        /// <summary>
        /// Receive an entity from a simulator, used in sync events.
        /// </summary>
        /// <param name="fromSimulator">The ID of the simulator from which to receive the entity.</param>
        /// <param name="sent"></param>
        /// <returns>The <see cref="SentEntity"/>, transformed back into an entity in the receiving SubModel.</returns>
        public Entity ReceiveEntity(Int32 fromSimulator, SentEntity sent)
        {
            return ErsEngine.ERS_SubModel_ReceiveEntityFrom(Data, fromSimulator, sent.id);
        }

        /// <summary>
        /// Get a core or SDK component of the provided type from an entity.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        /// <param name="entity">The ID of the entity.</param>
        /// <returns>The component attached to the entity.</returns>
        public readonly Ref<T> GetComponent<T>(Entity entity)
            where T : IDACComponent
        {
            UInt32 typeId       = ComponentTraits<T>.GetComponentTypeId();
            IntPtr componentPtr = ErsEngine.ERS_SubModel_GetComponent(Data, entity, typeId);
            return ComponentUtil.CreateComponentRef<T>(componentPtr);
        }

        /// <summary>
        /// Get a script behavior component of the provided type from an entity.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        /// <param name="entity">The ID of the entity.</param>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <returns>The component attached to the entity.</returns>
        public readonly T GetComponent<T>(Entity entity, bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent
        {
            UInt32 typeId    = ComponentTraits<T>.GetComponentTypeId();
            IntPtr handlePtr = ErsEngine.ERS_SubModel_GetScriptBehavior(Data, entity, typeId);
            return ComponentUtil.GetScriptBehavior<T>(handlePtr);
        }

        /// <summary>
        /// Check if an entity has a component type.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        /// <param name="entity">The ID of the entity.</param>
        /// <returns>Whether the entity has the component.</returns>
        public readonly bool HasComponent<T>(Entity entity)
            where T : IComponentBase
        {
            UInt32 componentId = ComponentTraits<T>.GetComponentTypeId(); // ComponentTrait asserts T is a known component type
            return ErsEngine.ERS_SubModel_HasComponent(Data, entity, componentId);
        }

        private IntPtr AddComponent(Entity entity, UInt32 componentType)
        {
            return ErsEngine.ERS_SubModel_AddDataComponent(Data, entity, componentType);
        }

        /// <summary>
        /// Sent metadata about a component type to ERS to set up support.
        /// </summary>
        /// <typeparam name="T">The type of the component.</typeparam>
        public void AddComponentType<T>()
            where T : IComponentBase
        {
            if (!ComponentTraits<T>.IsRegistered())
            {
                ComponentTraits<T>.RegisterType();
                RegisteredComponentTypes.AddType(this, typeof(T));
            }

            UInt32 type = ComponentTraits<T>.GetComponentTypeId();
            ErsEngine.ERS_SubModel_AddComponentType(Data, type);
        }

        /// <summary>
        /// Get the random properties of this submodel.
        /// </summary>
        /// <returns>The random properties instance of this submodel.</returns>
        public SubModelRandomProperties GetRandomProperties() => new SubModelRandomProperties(Data);

        /// <summary>
        /// Get the events associated to this submodel.
        /// </summary>
        /// <returns>A submodel signals instance.</returns>
        [Obsolete("Replaced by overridable methods (OnEntering, OnEntered, OnExiting, OnExited) on ScriptBehavior")]
        public SubModelSignals Events() => new SubModelSignals(Data);

        public void CreateInterpreter() { ErsEngine.ERS_SubModel_CreateInterpreter(Data); }

        public void RunSimpleString(string code)
        {
            var codeUtf8 = code.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* codeByte = codeUtf8)
                {
                    ErsEngine.ERS_SubModel_RunSimpleString(Data, codeByte);
                }
            }
        }

        public void LoadPythonModuleFromFile(string filePath)
        {
            var path = filePath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* filePathByte = path)
                {
                    ErsEngine.ERS_SubModel_LoadPythonModuleFromFile(Data, filePathByte);
                }
            }
        }

        public void LoadPythonPackage(string packageFolderPath)
        {
            var path = packageFolderPath.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* filePathByte = path)
                {
                    ErsEngine.ERS_SubModel_LoadPythonPackage(Data, filePathByte);
                }
            }
        }

        /// <summary>
        /// Get the simulator associated with this submodel.
        /// </summary>
        /// <returns>A sync manager instance.</returns>
        public Simulator GetSimulator()
        {
            IntPtr simulatorPtr = ErsEngine.ERS_SubModel_GetSimulator(Data);
            return new Simulator(simulatorPtr);
        }

        /// <summary>
        /// Get the currently active submodel.
        /// </summary>
        /// <returns>A submodel instance.</returns>
        public static SubModel GetSubModel() => new SubModel(ErsEngine.ERS_ThreadLocal_GetSubModel());

        /// <summary>
        /// Apply the model's precision to a given value.
        /// </summary>
        /// <param name="simTime">The value to apply the precision to.</param>
        /// <returns></returns>
        public readonly SimulationTime ApplyModelPrecision(SimulationTime simTime) =>
            simTime * ErsEngine.ERS_SubModel_GetModelPrecision(Data);

        /// <summary>
        /// Get the ID of the root entity of the SubModel.
        /// </summary>
        /// <returns></returns>
        public readonly Entity RootEntityID() => ErsEngine.ERS_SubModel_RootEntityID(Data);

        public void PrintGCStats() { ErsEngine.ERS_SubModel_PrintInterpreterGCStats(Data); }

        /// <summary>
        /// Assign a <see cref="RenderContext"/> to the interpreter attached to this submodel.
        /// </summary>
        /// <param name="context">The render context to assign.</param>
        public void BeginInterpreterRenderContext(RenderContext context)
        {
            ErsEngine.ERS_SubModel_BeginInterpreterRenderContext(Data, context.GetCoreInstance());
        }

        /// <summary>
        /// Unassign the <see cref="RenderContext"/> from the interpreter attached to this submodel.
        /// </summary>
        public void EndInterpreterRenderContext() => ErsEngine.ERS_SubModel_EndInterpreterRenderContext(Data);

        /// <summary>
        /// Get the <see cref="RenderContext"/> currently assigned to the interpreter attached to this submodel.
        /// </summary>
        /// <returns></returns>
        public RenderContext GetInterpreterRenderContext() => new RenderContext(ErsEngine.ERS_SubModel_GetInterpreterRenderContext(Data));

        /// <summary>
        /// Get a view to efficiently iterate over all entities that have a certain component.
        /// </summary>
        /// <typeparam name="T">The component the entities must have.</typeparam>
        /// <param name="excludedTypes">A list of components that the entities are not allowed to have.</param>
        /// <returns></returns>
        public View<T> GetView<T>(UInt32[] excludedTypes)
            where T : IComponentBase
        {
            var view = new View<T>(Data, excludedTypes);
            return view;
        }

        /// <summary>
        /// Get a view to efficiently iterate over all entities that contain certain components.
        /// </summary>
        /// <typeparam name="T1">The first component all entities must have.</typeparam>
        /// <typeparam name="T2">The second component all entities must have.</typeparam>
        /// <param name="excludedTypes">A list of components that the entities are not allowed to have.</param>
        /// <returns></returns>
        public View<T1, T2> GetView<T1, T2>(UInt32[] excludedTypes)
            where T1 : IComponentBase
            where T2 : IComponentBase
        {
            var view = new View<T1, T2>(Data, excludedTypes);
            return view;
        }

        /// <summary>
        /// Get a view to efficiently iterate over all entities that contain certain components.
        /// </summary>
        /// <typeparam name="T1">The first component all entities must have.</typeparam>
        /// <typeparam name="T2">The second component all entities must have.</typeparam>
        /// <typeparam name="T3">The third component all entities must have.</typeparam>
        /// <param name="excludedTypes">A list of components that the entities are not allowed to have.</param>
        /// <returns></returns>
        public View<T1, T2, T3> GetView<T1, T2, T3>(UInt32[] excludedTypes)
            where T1 : IComponentBase
            where T2 : IComponentBase
            where T3 : IComponentBase
        {
            var view = new View<T1, T2, T3>(Data, excludedTypes);
            return view;
        }

        /// <summary>
        /// Get a view to efficiently iterate over all entities that contain certain components.
        /// </summary>
        /// <typeparam name="T1">The first component all entities must have.</typeparam>
        /// <typeparam name="T2">The second component all entities must have.</typeparam>
        /// <typeparam name="T3">The third component all entities must have.</typeparam>
        /// <typeparam name="T4">The fourth component all entities must have.</typeparam>
        /// <param name="excludedTypes">A list of components that the entities are not allowed to have.</param>
        /// <returns></returns>
        public View<T1, T2, T3, T4> GetView<T1, T2, T3, T4>(UInt32[] excludedTypes)
            where T1 : IComponentBase
            where T2 : IComponentBase
            where T3 : IComponentBase
            where T4 : IComponentBase
        {
            var view = new View<T1, T2, T3, T4>(Data, excludedTypes);
            return view;
        }

        /// <summary>
        /// Get a view to efficiently iterate over all entities that contain certain components.
        /// </summary>
        /// <typeparam name="T1">The first component all entities must have.</typeparam>
        /// <typeparam name="T2">The second component all entities must have.</typeparam>
        /// <typeparam name="T3">The third component all entities must have.</typeparam>
        /// <typeparam name="T4">The fourth component all entities must have.</typeparam>
        /// <typeparam name="T5">The fifth component all entities must have.</typeparam>
        /// <param name="excludedTypes">A list of components that the entities are not allowed to have.</param>
        /// <returns></returns>
        public View<T1, T2, T3, T4, T5> GetView<T1, T2, T3, T4, T5>(UInt32[] excludedTypes)
            where T1 : IComponentBase
            where T2 : IComponentBase
            where T3 : IComponentBase
            where T4 : IComponentBase
            where T5 : IComponentBase
        {
            var view = new View<T1, T2, T3, T4, T5>(Data, excludedTypes);
            return view;
        }

        /// <summary>
        /// Shorthand for GetRandomProperties().GetRandomNumberGenerator().Reset().
        /// </summary>
        public void ResetRandomGenerator() { GetRandomProperties().GetRandomNumberGenerator().Reset(); }

        /// <summary>
        /// Shorthand for GetRandomProperties().GetRandomNumberGenerator().SetSeed(seed).
        /// </summary>
        /// <param name="seed">The new seed.</param>
        public void SetRandomGeneratorSeed(nuint seed) { GetRandomProperties().GetRandomNumberGenerator().SetSeed(seed); }

        /// <summary>
        /// Shorthand for GetRandomProperties().GetRandomNumberGenerator().Sample().
        /// </summary>
        /// <returns></returns>
        public double SampleRandomGenerator() { return GetRandomProperties().GetRandomNumberGenerator().Sample(); }
    }
}
