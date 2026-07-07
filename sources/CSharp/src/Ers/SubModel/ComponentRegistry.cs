namespace Ers
{
    /// <summary>
    /// Static registration of component types - templated per component type.
    /// Each unique component type gets its own registration.
    /// Similar to LocalEventRegistry for event types.
    /// </summary>
    /// <typeparam name="T">The component type to register.</typeparam>
    public static class ComponentRegistry<T>
        where T : IComponentBase
    {
        /// <summary>
        /// Register a component type globally.
        /// Registration is idempotent - calling multiple times is safe and results in a no-op.
        /// </summary>
        public static void Register()
        {
            if (ComponentTraits<T>.IsRegistered())
                return;

            ComponentTraits<T>.RegisterType();
        }
    }
}
