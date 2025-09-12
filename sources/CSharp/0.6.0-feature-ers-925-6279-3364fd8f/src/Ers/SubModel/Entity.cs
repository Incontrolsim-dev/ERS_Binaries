using Ers.Engine;
using Ers.Interpreter;

namespace Ers
{
    /// <summary>
    /// Used to send an entity from one submodel to another.
    ///
    /// <para>
    /// Entities sent between submodels are temporary transformed into a SentEntity to safely exchange them.
    /// Once an entity is received in a submodel, it may have a different ID than before.
    /// See also <see cref="SubModel.SendEntity(int, ulong)"/> and <see cref="SubModel.ReceiveEntity(int, SentEntity)"/>.
    /// </para>
    /// </summary>
    public readonly struct SentEntity
    {
        internal readonly UInt64 id;
        internal SentEntity(UInt64 id_) { id = id_; }
    };

    /// <summary>
    /// Static Entity class to perform Entity operations without needing to get a SubModel.
    /// The currently entered SubModel will be used automatically.
    /// </summary>
    public static class CEntity
    {
        /// <summary>
        /// Retrieve ERS' definition of an invalid entity.
        /// </summary>
        /// <returns>Invalid entity</returns>
        public static Entity InvalidEntity() { return ErsEngine.ERS_Entity_Invalid(); }

        /// <summary>
        /// Create an entity in the currently entered SubModel.
        /// </summary>
        /// <returns>The ID of the newly created entity.</returns>
        public static Entity Create()
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.CreateEntity();
        }

        /// <summary>
        /// Create a new entity with a given name in the currently entered SubModel.
        /// </summary>
        /// <param name="name">The name for the new entity.</param>
        /// <returns>The ID of the newly created entity.</returns>
        public static Entity Create(string name)
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.CreateEntity(name);
        }

        /// <summary>
        /// Find an entity by its name in the currently entered SubModel.
        /// </summary>
        /// <param name="name">The name to search for.</param>
        /// <returns>The ID of the found entity. If no entity is found, the <see cref="CEntity.InvalidEntity()"/> ID is returned.</returns>
        public static Entity Find(string name)
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.FindEntity(name);
        }
    }

    /// <summary>
    /// Extensions for Entities of ERS, optimize performance by using a primitive type for built-in optimizations and to prevent allocations
    /// with a custom struct
    /// </summary>
    public static class EntityExtensions
    {
        /// <summary>
        /// Extension function to check if an Entity is valid
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <returns></returns>
        public static bool IsValid(this Entity id)
        {
            bool validID = id != ErsEngine.ERS_Entity_Invalid();
            return validID ? SubModel.GetSubModel().EntityExists(id) : false;
        }

        /// <summary>
        /// Extension function to Get a DataComponent from an entity
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <returns></returns>
        public static Ref<T> GetComponent<T>(this Entity id)
            where T : IDACComponent
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.GetComponent<T>(id);
        }

        /// <summary>
        /// Extension function to add a DataComponent to an Entity
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>S
        /// <param name="id"></param>
        /// <returns></returns>
        public static Ref<T> AddComponent<T>(this Entity id)
            where T : unmanaged, IDACComponent
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.AddComponent<T>(id);
        }

        /// <summary>
        /// Extension function to remove a component from an entity
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <returns></returns>
        public static void RemoveComponent<T>(this Entity id)
            where T : IComponentBase
        {
            SubModel subModel = SubModel.GetSubModel();
            subModel.RemoveComponent<T>(id);
        }

        /// <summary>
        /// Extension function to check if an Entity has a specific component
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <returns></returns>
        public static bool HasComponent<T>(this Entity id)
            where T : IComponentBase
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.HasComponent<T>(id);
        }

        /// <summary>
        /// Extension function to add a ScriptBehavior component to an entity
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <param name="scriptBehavior">(Ignore this, it is used only internally)</param>
        /// <returns></returns>
        public static T AddComponent<T>(this Entity id, bool scriptBehavior = true)
            where T : ScriptBehaviorComponent, new()
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.AddComponent<T>(id);
        }

        /// <summary>
        /// Extension function to get a ScriptBehavior component from an entity
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <param name="scriptBehavior">(Ignore this, it is used only internally)</param>
        /// <returns></returns>
        public static T GetComponent<T>(this Entity id, bool scriptBehavior = true)
            where T : ScriptBehaviorComponent
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.GetComponent<T>(id);
        }

        /// <summary>
        /// Extension function to check if an Entity has a scriptbehavior
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <param name="scriptBehavior">(Ignore this, it is used only internally)</param>
        /// <returns></returns>
        public static bool HasComponent<T>(this Entity id, bool scriptBehavior = true)
            where T : ScriptBehaviorComponent
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.HasComponent<T>(id);
        }

        /// <summary>
        /// Extension function to get the name stored in the NameComponent on an entity
        /// </summary>
        /// <remarks>Note: specific to ERS.</remarks>
        /// <param name="id"></param>
        /// <returns></returns>
        public static string GetName(this Entity id)
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.GetComponent<NameComponent>(id).Value.Name;
        }

        public static InterpreterVariable AddInterpreterScriptComponent(this Entity id)
        {
            SubModel subModel = SubModel.GetSubModel();
            return subModel.AddInterpreterScriptComponent(id);
        }
    }
}
