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
        /// Called after an input channel is ready, given that this script's entity has a <see cref="ResourceComponent"/>.
        /// </summary>
        /// <param name="inputChannel">The entity with the input channel that is ready.</param>
        public virtual void OnInputChannelReady(Entity inputChannel) {}
        /// <summary>
        /// Called after an output channel is ready, given that this script's entity has a <see cref="ResourceComponent"/>.
        /// </summary>
        /// <param name="outputChannel">The entity with the output channel that is ready.</param>
        public virtual void OnOutputChannelReady(Entity outputChannel) {}
        /// <summary>
        /// Called after an entity is passed by a <see cref="ResourceComponent"/>. It will be added as a child.
        /// </summary>
        /// <param name="inputChannel">The entity with the input channel that received the child.</param>
        /// <param name="child">The child that has been passed.</param>
        public virtual void OnReceive(Entity inputChannel, Entity child) {}

        /// <summary>
        /// Called during Serialization, during load and save operation.
        /// Use this function to save all state of the script behavior into a string, it is then included in the ERS Save file.
        /// Likewise you can read entries in the saved string to fill a newly created script behavior during the load operation
        /// </summary>
        /// <param name="node"></param>
        public virtual void Serialization(Serializer node) {}

        /// <summary>
        /// Called when an entity is moved between submodels.
        /// Use this function to rebuild information that is invalid after the move, for example child entity ID's referenced by this
        /// script behavior
        /// </summary>
        /// <param name="node"></param>
        public virtual void OnSubModelMove(Entity newEntityId) {}
    }
}
