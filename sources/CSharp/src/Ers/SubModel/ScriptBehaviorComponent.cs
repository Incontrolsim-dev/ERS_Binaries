using System;

namespace Ers
{
    /// <summary>
    /// A component that can hold data and logic.
    /// </summary>
    public class ScriptBehaviorComponent : IComponentBase
    {
        /// <summary>
        /// The entity to which this instance of the component belongs.
        /// </summary>
        public Entity ConnectedEntity;

        /// <summary>
        /// Called just after the component is created.
        /// </summary>
        public virtual void OnCreation() {}
        /// <summary>
        /// Called once just before the component is destroyed.
        /// </summary>
        public virtual void OnDestroy() {}
        /// <summary>
        /// Called once just before OnStart.
        /// </summary>
        public virtual void OnAwake() {}
        /// <summary>
        /// Called once when the submodel has started.
        /// </summary>
        public virtual void OnStart() {}
        /// <summary>
        /// Called on every update of the submodel.
        /// </summary>
        public virtual void OnUpdate() {}
        /// <summary>
        /// Called just after the OnUpdate function.
        /// </summary>
        public virtual void OnLateUpdate() {}

        /// <summary>
        /// Called before the ConnectedEntity is added to a parent.
        ///
        /// <para>Is called on the child.</para>
        /// </summary>
        /// <param name="newParent">The parent entity the ConnectedEntity is about to enter.</param>
        public virtual void OnEntering(Entity newParent) {}
        /// <summary>
        /// Called after a new child entity is added to a parent.
        ///
        /// <para>Is called on the parent.</para>
        /// </summary>
        /// <param name="newChild">The newly added child.</param>
        public virtual void OnEntered(Entity newChild) {}
        /// <summary>
        /// Called before the ConnectedEntity is removed from a parent.
        ///
        /// <para>Is called on the child.</para>
        /// </summary>
        /// <param name="oldParent">The parent entity the ConnectedEntity is about to leave.</param>
        public virtual void OnExiting(Entity oldParent) {}
        /// <summary>
        /// Called after a child entity is removed from a parent.
        ///
        /// <para>Is called on the parent.</para>
        /// </summary>
        /// <param name="oldChild">The previously present child.</param>
        public virtual void OnExited(Entity oldChild) {}

        /// <summary>
        /// Called during Serialization, during load and save operation.
        /// Use this function to save all state of the script behavior into a string, it is then included in the ERS Save file.
        /// Likewise you can read entries in the saved string to fill a newly created scriptbehavior during the load operation
        /// </summary>
        /// <param name="node"></param>
        public virtual void Serialization(Serialization node) {}

        /// <summary>
        /// Called when an entity is moved between submodels.
        /// Use this function to rebuild information that is invalid after the move, for example child entity ID's referenced by this
        /// scriptbehavior
        /// </summary>
        /// <param name="node"></param>
        public virtual void OnSubModelMove(Entity newEntityId) {}
    }
}
