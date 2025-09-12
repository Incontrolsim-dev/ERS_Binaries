using System.Collections;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Component defining hierarchical relations between entities.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct RelationComponent : ICoreComponent, IEnumerable<Entity>
    {
        /// <summary>
        /// Get the ID of the parent.
        /// </summary>
        /// <returns></returns>
        public Entity Parent() { return ErsEngine.ERS_RelationComponent_GetParent(CorePointer()); }

        /// <summary>
        /// Get the ID of the first child.
        /// </summary>
        /// <returns></returns>
        public Entity First() { return ErsEngine.ERS_RelationComponent_GetFirst(CorePointer()); }

        /// <summary>
        /// Get the ID of the last child.
        /// </summary>
        /// <returns></returns>
        public Entity Last() { return ErsEngine.ERS_RelationComponent_GetLast(CorePointer()); }

        /// <summary>
        /// Get the ID of the previous sibling. Moves the sibling iterator.
        /// </summary>
        /// <returns></returns>
        public Entity Previous() { return ErsEngine.ERS_RelationComponent_GetPrevious(CorePointer()); }

        /// <summary>
        /// Get the ID of the next sibling. Moves the sibling iterator.
        /// </summary>
        /// <returns></returns>
        public Entity Next() { return ErsEngine.ERS_RelationComponent_GetNext(CorePointer()); }

        /// <summary>
        /// Get the number of children.
        /// </summary>
        /// <returns></returns>
        public UInt64 ChildCount() { return ErsEngine.ERS_RelationComponent_GetChildCount(CorePointer()); }

        /// <summary>
        /// The type ID of the component in the ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() { return ErsEngine.ERS_RelationComponent_TypeId(); }

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed(RelationComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }

        /// <summary>
        /// Child indexer.
        /// </summary>
        /// <param name="index">The index of the child to retrieve.</param>
        /// <returns>The child</returns>
        /// <exception cref="ArgumentOutOfRangeException">The requested child is out of range.</exception>
        public Entity this[ulong index]
        {
            get
            {
                ArgumentOutOfRangeException.ThrowIfGreaterThanOrEqual(index, ChildCount());

                Entity child = First();
                for (ulong i = 0; i < index; i++)
                    child = child.GetComponent<RelationComponent>().Value.Next();
                return child;
            }
        }

        public IEnumerator<Entity> GetEnumerator() => new ChildEnumerator(First());

        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

        /// <summary>
        /// Allows for the enumeration over children of a parent entity. Becomes invalid once the makeup of the parent's child entities
        /// change.
        /// </summary>
        /// <param name="c">The first child entity of the parent.</param>
        public class ChildEnumerator(Entity c) : IEnumerator<Entity>
        {
            /// <summary>
            /// The parent entity for whose children to iterate over.
            /// </summary>
            private readonly Entity first = c;

            /// <summary>
            /// The current child entity.
            /// </summary>
            private Entity current = CEntity.InvalidEntity();

            /// <summary>
            /// Indicates whether we want to reset the enumerator.
            /// </summary>
            private bool reset = true;

            public bool MoveNext()
            {
                if (reset)
                {
                    current = first;
                    reset   = false;
                }
                else
                {
                    current = current.GetComponent<RelationComponent>().Value.Next();
                }
                return current != CEntity.InvalidEntity();
            }

            public void Reset()
            {
                reset   = true;
                current = CEntity.InvalidEntity();
            }

            object IEnumerator.Current => current;

            public Entity Current => current != CEntity.InvalidEntity() ? current : throw new InvalidOperationException();

            public void Dispose() {}
        }
    }
}
