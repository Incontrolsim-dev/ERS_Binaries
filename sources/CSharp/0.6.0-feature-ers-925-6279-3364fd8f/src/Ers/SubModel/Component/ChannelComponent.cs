using System;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    [StructLayout(LayoutKind.Sequential)]
    public struct ChannelComponent : ICoreComponent
    {
        public static nuint CoreTypeId() => ErsEngine.ERS_ChannelComponent_TypeId();

        public int GetType() { return ErsEngine.ERS_ChannelComponent_GetType(CorePointer()); }

        public Entity GetConnectedTo() { return ErsEngine.ERS_ChannelComponent_GetConnectedTo(CorePointer()); }

        public bool IsOpen() { return ErsEngine.ERS_ChannelComponent_IsOpen(CorePointer()); }

        public float GetLongitudonalPosition() { return ErsEngine.ERS_ChannelComponent_GetLongitudonalPosition(CorePointer()); }

        public void SetLongitudonalPosition(float position)
        {
            ErsEngine.ERS_ChannelComponent_SetLongitudonalPosition(CorePointer(), position);
        }

        internal IntPtr CorePointer()
        {
            unsafe
            {
                fixed(ChannelComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}