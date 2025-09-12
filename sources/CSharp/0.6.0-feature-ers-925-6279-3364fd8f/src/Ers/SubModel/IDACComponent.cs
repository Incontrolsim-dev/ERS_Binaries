namespace Ers
{
    /// <summary>
    /// Data- and Core component.
    ///
    /// <para>
    /// Internally used to identify components as either <see cref="ICoreComponent"/> or <see cref="IDataComponent"/>.
    /// Extend <see cref="IDataComponent"/> or <see cref="ScriptBehaviorComponent"/> instead.
    /// </para>
    /// </summary>
    public interface IDACComponent : IComponentBase
    {
    }
}
