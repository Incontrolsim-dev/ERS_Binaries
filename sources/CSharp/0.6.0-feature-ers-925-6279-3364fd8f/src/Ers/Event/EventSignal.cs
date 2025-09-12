using Ers.Engine;
using System.Diagnostics;
using System.Runtime.InteropServices;

#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
namespace Ers
{
    public delegate IntPtr ConnectionFunction(IntPtr signalHandle, IntPtr callback, IntPtr obj);
    public delegate void ConnectCallbackWrapper1(IntPtr obj, Entity arg);
    public delegate void ConnectCallbackWrapper2(IntPtr obj, Entity arg1, Entity arg2);

    [Obsolete("Replaced by overridable methods (OnEntering, OnEntered, OnExiting, OnExited) on ScriptBehavior")]
    public class EventSignalBase
    {
        private readonly IntPtr signalHandle;
        private readonly ConnectionFunction connectionFunction;

        public struct Connection
        {
            private readonly IntPtr connectionHandle;

            // Store one of the callback wrappers to prevent garbage collecting them
            public ConnectCallbackWrapper1? Callback1;
            public ConnectCallbackWrapper2? Callback2;

            public Connection(IntPtr connectionHandle) { this.connectionHandle = connectionHandle; }

            public void Disconnect()
            {
                Debug.Assert(this.connectionHandle != IntPtr.Zero);
                ErsEngine.ERS_SubModel_Events_Disconnect(this.connectionHandle);
            }
        }

        public void Disconnect(Connection connection) { connection.Disconnect(); }

        protected EventSignalBase(IntPtr coreSignalHandle, ConnectionFunction connectionFunction)
        {
            signalHandle            = coreSignalHandle;
            this.connectionFunction = connectionFunction;
        }

        protected Connection Connect(IntPtr signalFunction)
        {
            IntPtr handle = connectionFunction(signalHandle, signalFunction, IntPtr.Zero);
            return new Connection(handle);
        }
    }

    [Obsolete("Replaced by overridable methods (OnEntering, OnEntered, OnExiting, OnExited) on ScriptBehavior")]
    public class EventSignal1 : EventSignalBase
    {
        public delegate void ConnectCallback(Entity arg);

        public EventSignal1(IntPtr coreSignalHandle, ConnectionFunction connectionFunction) : base(coreSignalHandle, connectionFunction) {}

        public Connection Connect(ConnectCallback callback)
        {
            ConnectCallbackWrapper1 callbackWrapper = (IntPtr objPtr, Entity arg) => callback(arg);
            IntPtr function                                                        = Marshal.GetFunctionPointerForDelegate(callbackWrapper);

            Connection connection = base.Connect(function);
            connection.Callback1  = callbackWrapper;
            return connection;
        }
    }

    [Obsolete("Replaced by overridable methods (OnEntering, OnEntered, OnExiting, OnExited) on ScriptBehavior")]
    public class EventSignal2 : EventSignalBase
    {
        public delegate void ConnectCallback(Entity arg1, Entity arg2);

        public EventSignal2(IntPtr coreSignalHandle, ConnectionFunction connectionFunction) : base(coreSignalHandle, connectionFunction) {}

        public Connection Connect(ConnectCallback callback)
        {
            ConnectCallbackWrapper2 callbackWrapper = (IntPtr objPtr, Entity arg1, Entity arg2) => callback(arg1, arg2);
            IntPtr function = Marshal.GetFunctionPointerForDelegate(callbackWrapper);

            Connection connection = base.Connect(function);
            connection.Callback2  = callbackWrapper;
            return connection;
        }
    }
}
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
