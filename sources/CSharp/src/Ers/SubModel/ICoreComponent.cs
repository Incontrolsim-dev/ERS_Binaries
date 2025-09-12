namespace Ers
{
    /// <summary>
    /// Components that are built-in to ERS.
    ///
    /// <para>
    /// This component type is used for components such as <see cref="TransformComponent"/> and <see cref="RelationComponent"/>.
    /// Use <see cref="IDataComponent"/> or <see cref="ScriptBehaviorComponent"/> instead.
    /// </para>
    /// </summary>
    public interface ICoreComponent : IDACComponent
    {
        /// <summary>
        /// The type ID of the component in ERS.
        /// </summary>
        /// <returns></returns>
        abstract static nuint CoreTypeId();
    }
}
