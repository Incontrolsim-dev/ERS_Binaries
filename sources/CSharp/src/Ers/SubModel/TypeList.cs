using System;

namespace Ers
{
    /// <summary>
    /// Container for a list of component types.
    /// </summary>
    public class ComponentList
    {
        /// <summary>
        /// Construct a new component list from one component type.
        /// </summary>
        /// <typeparam name="T1">The component type to add to the list.</typeparam>
        /// <returns></returns>
        public static UInt32[] GetTypeArray<T1>()
            where T1 : IComponentBase
        {
            return new UInt32[] {
                ComponentTraits<T1>.GetComponentTypeId(),
            };
        }

        /// <summary>
        /// Construct a new component list from multiple component types.
        /// </summary>
        /// <typeparam name="T1">The first component type to add to the list.</typeparam>
        /// <typeparam name="T2">The second component type to add to the list.</typeparam>
        /// <returns></returns>
        public static UInt32[] GetTypeArray<T1, T2>()
            where T1 : IComponentBase
            where T2 : IComponentBase
        {
            return new UInt32[] {
                ComponentTraits<T1>.GetComponentTypeId(),
                ComponentTraits<T2>.GetComponentTypeId(),
            };
        }

        /// <summary>
        /// Construct a new component list multiple component types.
        /// </summary>
        /// <typeparam name="T1">The first component type to add to the list.</typeparam>
        /// <typeparam name="T2">The second component type to add to the list.</typeparam>
        /// <typeparam name="T3">The third component type to add to the list.</typeparam>
        /// <returns></returns>
        public static UInt32[] GetTypeArray<T1, T2, T3>()
            where T1 : IComponentBase
            where T2 : IComponentBase
            where T3 : IComponentBase
        {
            return new UInt32[] {
                ComponentTraits<T1>.GetComponentTypeId(),
                ComponentTraits<T2>.GetComponentTypeId(),
                ComponentTraits<T3>.GetComponentTypeId(),
            };
        }

        /// <summary>
        /// Construct a new component list multiple component types.
        /// </summary>
        /// <typeparam name="T1">The first component type to add to the list.</typeparam>
        /// <typeparam name="T2">The second component type to add to the list.</typeparam>
        /// <typeparam name="T3">The third component type to add to the list.</typeparam>
        /// <typeparam name="T4">The fourth component type to add to the list.</typeparam>
        /// <returns></returns>
        public static UInt32[] GetTypeArray<T1, T2, T3, T4>()
            where T1 : IComponentBase
            where T2 : IComponentBase
            where T3 : IComponentBase
            where T4 : IComponentBase
        {
            return new UInt32[] {
                ComponentTraits<T1>.GetComponentTypeId(),
                ComponentTraits<T2>.GetComponentTypeId(),
                ComponentTraits<T3>.GetComponentTypeId(),
                ComponentTraits<T4>.GetComponentTypeId(),
            };
        }

        /// <summary>
        /// Construct a new component list multiple component types.
        /// </summary>
        /// <typeparam name="T1">The first component type to add to the list.</typeparam>
        /// <typeparam name="T2">The second component type to add to the list.</typeparam>
        /// <typeparam name="T3">The third component type to add to the list.</typeparam>
        /// <typeparam name="T4">The fourth component type to add to the list.</typeparam>
        /// <typeparam name="T5">The fifth component type to add to the list.</typeparam>
        /// <returns></returns>
        public static UInt32[] GetTypeArray<T1, T2, T3, T4, T5>()
            where T1 : IComponentBase
            where T2 : IComponentBase
            where T3 : IComponentBase
            where T4 : IComponentBase
            where T5 : IComponentBase
        {
            return new UInt32[] {
                ComponentTraits<T1>.GetComponentTypeId(), ComponentTraits<T2>.GetComponentTypeId(),
                ComponentTraits<T3>.GetComponentTypeId(), ComponentTraits<T4>.GetComponentTypeId(),
                ComponentTraits<T5>.GetComponentTypeId(),
            };
        }
    }
}
