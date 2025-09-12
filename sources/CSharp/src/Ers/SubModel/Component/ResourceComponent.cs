using System;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    [StructLayout(LayoutKind.Sequential)]
    public struct ResourceComponent : ICoreComponent
    {
        public static nuint CoreTypeId() => ErsEngine.ERS_ResourceComponent_TypeId();

        public int GetNumInputChannels() { return (int)ErsEngine.ERS_ResourceComponent_GetNumInputChannels(CorePointer()); }

        public int GetNumOutputChannels() { return (int)ErsEngine.ERS_ResourceComponent_GetNumOutputChannels(CorePointer()); }

        public Entity GetInputChannel(int index) { return ErsEngine.ERS_ResourceComponent_GetInputChannel(CorePointer(), (nuint)index); }

        public Entity GetOutputChannel(int index) { return ErsEngine.ERS_ResourceComponent_GetOutputChannel(CorePointer(), (nuint)index); }

        public IntPtr CorePointer()
        {
            unsafe
            {
                fixed(ResourceComponent* compPtr = &this)
                {
                    return (IntPtr)compPtr;
                }
            }
        }
    }
}