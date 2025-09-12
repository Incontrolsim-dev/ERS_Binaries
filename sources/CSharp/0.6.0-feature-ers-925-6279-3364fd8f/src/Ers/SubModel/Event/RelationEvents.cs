using Ers.Engine;
using System.Runtime.InteropServices;

#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
namespace Ers
{
    [Obsolete("Replaced by overridable methods (OnEntering, OnEntered, OnExiting, OnExited) on ScriptBehavior")]
    [StructLayout(LayoutKind.Sequential)]
    public ref struct RelationEvents
    {
        // Default events
        public EventSignal1 OnAwake =>
            new EventSignal1(ErsEngine.ERS_SubModel_RelationEvents_OnAwake(), ErsEngine.ERS_SubModel_RelationEvents_OnAwake_Connect);
        public EventSignal1 OnStart =>
            new EventSignal1(ErsEngine.ERS_SubModel_RelationEvents_OnStart(), ErsEngine.ERS_SubModel_RelationEvents_OnStart_Connect);

        public EventSignal1 OnCreate =>
            new EventSignal1(ErsEngine.ERS_SubModel_RelationEvents_OnCreate(), ErsEngine.ERS_SubModel_RelationEvents_OnCreate_Connect);
        public EventSignal1 OnDestroy =>
            new EventSignal1(ErsEngine.ERS_SubModel_RelationEvents_OnDestroy(), ErsEngine.ERS_SubModel_RelationEvents_OnDestroy_Connect);

        public EventSignal1 OnEntering =>
            new EventSignal1(ErsEngine.ERS_SubModel_RelationEvents_OnEntering(), ErsEngine.ERS_SubModel_RelationEvents_OnEntering_Connect);
        public EventSignal2 OnEntered =>
            new EventSignal2(ErsEngine.ERS_SubModel_RelationEvents_OnEntered(), ErsEngine.ERS_SubModel_RelationEvents_OnEntered_Connect);

        public EventSignal1 OnExiting =>
            new EventSignal1(ErsEngine.ERS_SubModel_RelationEvents_OnExiting(), ErsEngine.ERS_SubModel_RelationEvents_OnExiting_Connect);
        public EventSignal2 OnExited =>
            new EventSignal2(ErsEngine.ERS_SubModel_RelationEvents_OnExited(), ErsEngine.ERS_SubModel_RelationEvents_OnExited_Connect);

        private readonly IntPtr SubmodelPtr;

        internal RelationEvents(IntPtr subModel) { SubmodelPtr = subModel; }
    }
}
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
