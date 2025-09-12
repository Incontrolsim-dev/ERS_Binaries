using System;
using System.Runtime.InteropServices;

#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
namespace Ers
{
    [Obsolete("Replaced by overridable methods (OnEntering, OnEntered, OnExiting, OnExited) on ScriptBehavior")]
    [StructLayout(LayoutKind.Sequential)]
    public ref struct SubModelSignals
    {
        public RelationEvents Relation;

        public SubModelSignals(IntPtr subModel) { Relation = new RelationEvents(subModel); }
    }
}
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
