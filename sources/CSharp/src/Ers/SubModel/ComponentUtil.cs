using Ers.Engine;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Ers
{
    internal class ComponentUtil
    {
        public static unsafe Ref<T> CreateComponentRef<T>(IntPtr componentPtr)
        {
            void* ptr = (void*)componentPtr;
#pragma warning disable CS8500
            return new Ref<T>(ref * (T*)ptr);
#pragma warning restore CS8500
        }

        public static T GetScriptBehavior<T>(IntPtr handlePtr)
        {
            var handle = GCHandle.FromIntPtr(handlePtr);
            object? o  = handle.Target;
            Debug.Assert(o != null);
            return (T)o;
        }
    }
}
