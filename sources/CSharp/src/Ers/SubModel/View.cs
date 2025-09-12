using Ers.Engine;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// Views allow for efficient iteration over all entities that have certain components.
    /// </summary>
    /// <typeparam name="T1">The component the entities must have.</typeparam>
    /// <param name="subModel">A pointer to the SubModel in the ERS core.</param>
    /// <param name="excluded">The IDs of the components that the entities must not have.</param>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct View<T1>(IntPtr subModel, UInt32[] excluded)
        where T1 : IComponentBase
    {
        /// <summary>
        /// Move to the next entity in the view.
        /// </summary>
        /// <returns>Whether there was a next entity.</returns>
        public readonly bool Next() => ErsEngine.ERS_Submodel_View_Next(Base.Instance);

        internal IntPtr GetComponent(int typeIndex) => ErsEngine.ERS_Submodel_View_GetComponent(Base.Instance, (nuint)typeIndex);

        internal readonly int FindTypeIdx(UInt32 findType)
        {
            for (int i = 0; i < Base.IncludedTypeIdArray.Length; i++)
            {
                UInt32 componentType = Base.IncludedTypeIdArray[i];
                if (componentType == findType)
                {
                    return i;
                }
            }

            // Type not found.
            return -1;
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public T GetComponent<T>(bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.GetScriptBehavior<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public Ref<T> GetComponent<T>()
            where T : IDACComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.CreateComponentRef<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get the current entity.
        /// </summary>
        /// <returns>The ID of the current entity.</returns>
        public Entity GetEntity() => Base.GetEntity();

        public void Dispose() { Base.Dispose(); }

        private BaseView Base = new BaseView(subModel, ComponentList.GetTypeArray<T1>(), excluded);
    }

    /// <summary>
    /// Views allow for efficient iteration over all entities that have certain components.
    /// </summary>
    /// <typeparam name="T1">The first component the entities must have.</typeparam>
    /// <typeparam name="T2">The second component the entities must have.</typeparam>
    /// <param name="subModel">A pointer to the SubModel in the ERS core.</param>
    /// <param name="excluded">The IDs of the components that the entities must not have.</param>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct View<T1, T2>(IntPtr subModel, UInt32[] excluded)
        where T1 : IComponentBase
        where T2 : IComponentBase
    {
        /// <summary>
        /// Move to the next entity in the view.
        /// </summary>
        /// <returns>Whether there was a next entity.</returns>
        public readonly bool Next() => ErsEngine.ERS_Submodel_View_Next(Base.Instance);

        internal IntPtr GetComponent(int typeIndex) => ErsEngine.ERS_Submodel_View_GetComponent(Base.Instance, (nuint)typeIndex);

        internal readonly int FindTypeIdx(UInt32 findType)
        {
            for (int i = 0; i < Base.IncludedTypeIdArray.Length; i++)
            {
                UInt32 componentType = Base.IncludedTypeIdArray[i];
                if (componentType == findType)
                {
                    return i;
                }
            }

            // Type not found.
            return -1;
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public T GetComponent<T>(bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.GetScriptBehavior<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public Ref<T> GetComponent<T>()
            where T : IDACComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.CreateComponentRef<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get the current entity.
        /// </summary>
        /// <returns>The ID of the current entity.</returns>
        public Entity GetEntity() => Base.GetEntity();
        public void Dispose() { Base.Dispose(); }

        private BaseView Base = new BaseView(subModel, ComponentList.GetTypeArray<T1, T2>(), excluded);
    }

    /// <summary>
    /// Views allow for efficient iteration over all entities that have certain components.
    /// </summary>
    /// <typeparam name="T1">The first component the entities must have.</typeparam>
    /// <typeparam name="T2">The second component the entities must have.</typeparam>
    /// <typeparam name="T3">The third component the entities must have.</typeparam>
    /// <param name="subModel">A pointer to the SubModel in the ERS core.</param>
    /// <param name="excluded">The IDs of the components that the entities must not have.</param>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct View<T1, T2, T3>(IntPtr subModel, UInt32[] excluded)
        where T1 : IComponentBase
        where T2 : IComponentBase
        where T3 : IComponentBase
    {
        /// <summary>
        /// Move to the next entity in the view.
        /// </summary>
        /// <returns>Whether there was a next entity.</returns>
        public readonly bool Next() => ErsEngine.ERS_Submodel_View_Next(Base.Instance);

        internal IntPtr GetComponent(int typeIndex) => ErsEngine.ERS_Submodel_View_GetComponent(Base.Instance, (nuint)typeIndex);

        internal readonly int FindTypeIdx(UInt32 findType)
        {
            for (int i = 0; i < Base.IncludedTypeIdArray.Length; i++)
            {
                UInt32 componentType = Base.IncludedTypeIdArray[i];
                if (componentType == findType)
                {
                    return i;
                }
            }

            // Type not found.
            return -1;
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public T GetComponent<T>(bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.GetScriptBehavior<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public Ref<T> GetComponent<T>()
            where T : IDACComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.CreateComponentRef<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get the current entity.
        /// </summary>
        /// <returns>The ID of the current entity.</returns>
        public Entity GetEntity() => Base.GetEntity();
        public void Dispose() { Base.Dispose(); }

        private BaseView Base = new BaseView(subModel, ComponentList.GetTypeArray<T1, T2, T3>(), excluded);
    }

    /// <summary>
    /// Views allow for efficient iteration over all entities that have certain components.
    /// </summary>
    /// <typeparam name="T1">The first component the entities must have.</typeparam>
    /// <typeparam name="T2">The second component the entities must have.</typeparam>
    /// <typeparam name="T3">The third component the entities must have.</typeparam>
    /// <typeparam name="T4">The fourth component the entities must have.</typeparam>
    /// <param name="subModel">A pointer to the SubModel in the ERS core.</param>
    /// <param name="excluded">The IDs of the components that the entities must not have.</param>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct View<T1, T2, T3, T4>(IntPtr subModel, UInt32[] excluded)
        where T1 : IComponentBase
        where T2 : IComponentBase
        where T3 : IComponentBase
        where T4 : IComponentBase
    {

        /// <summary>
        /// Move to the next entity in the view.
        /// </summary>
        /// <returns>Whether there was a next entity.</returns>
        public readonly bool Next() => ErsEngine.ERS_Submodel_View_Next(Base.Instance);

        internal IntPtr GetComponent(int typeIndex) => ErsEngine.ERS_Submodel_View_GetComponent(Base.Instance, (nuint)typeIndex);

        internal readonly int FindTypeIdx(UInt32 findType)
        {
            for (int i = 0; i < Base.IncludedTypeIdArray.Length; i++)
            {
                UInt32 componentType = Base.IncludedTypeIdArray[i];
                if (componentType == findType)
                {
                    return i;
                }
            }

            // Type not found.
            return -1;
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public T GetComponent<T>(bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.GetScriptBehavior<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public Ref<T> GetComponent<T>()
            where T : IDACComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.CreateComponentRef<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get the current entity.
        /// </summary>
        /// <returns>The ID of the current entity.</returns>
        public Entity GetEntity() => Base.GetEntity();
        public void Dispose() { Base.Dispose(); }

        private BaseView Base = new BaseView(subModel, ComponentList.GetTypeArray<T1, T2, T3, T4>(), excluded);
    }

    /// <summary>
    /// Views allow for efficient iteration over all entities that have certain components.
    /// </summary>
    /// <typeparam name="T1">The first component the entities must have.</typeparam>
    /// <typeparam name="T2">The second component the entities must have.</typeparam>
    /// <typeparam name="T3">The third component the entities must have.</typeparam>
    /// <typeparam name="T4">The fourth component the entities must have.</typeparam>
    /// <typeparam name="T5">The fifth component the entities must have.</typeparam>
    /// <param name="subModel">A pointer to the SubModel in the ERS core.</param>
    /// <param name="excluded">The IDs of the components that the entities must not have.</param>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct View<T1, T2, T3, T4, T5>(IntPtr subModel, UInt32[] excluded)
        where T1 : IComponentBase
        where T2 : IComponentBase
        where T3 : IComponentBase
        where T4 : IComponentBase
        where T5 : IComponentBase
    {
        /// <summary>
        /// Move to the next entity in the view.
        /// </summary>
        /// <returns>Whether there was a next entity.</returns>
        public readonly bool Next() => ErsEngine.ERS_Submodel_View_Next(Base.Instance);

        internal IntPtr GetComponent(int typeIndex) => ErsEngine.ERS_Submodel_View_GetComponent(Base.Instance, (nuint)typeIndex);

        internal readonly int FindTypeIdx(UInt32 findType)
        {
            for (int i = 0; i < Base.IncludedTypeIdArray.Length; i++)
            {
                UInt32 componentType = Base.IncludedTypeIdArray[i];
                if (componentType == findType)
                {
                    return i;
                }
            }

            // Type not found.
            return -1;
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <param name="isScriptBehavior">(Ignore this, it is used only internally)</param>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public T GetComponent<T>(bool isScriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.GetScriptBehavior<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get a component on the current entity.
        /// </summary>
        /// <typeparam name="T">The type of component to get.</typeparam>
        /// <exception cref="ArgumentException">When a component of the given type does not exist on the entity.</exception>
        public Ref<T> GetComponent<T>()
            where T : IDACComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.CreateComponentRef<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }

        /// <summary>
        /// Get the current entity.
        /// </summary>
        /// <returns>The ID of the current entity.</returns>
        public Entity GetEntity() => Base.GetEntity();
        public void Dispose() { Base.Dispose(); }

        private BaseView Base = new BaseView(subModel, ComponentList.GetTypeArray<T1, T2, T3, T4, T5>(), excluded);
    }
}
