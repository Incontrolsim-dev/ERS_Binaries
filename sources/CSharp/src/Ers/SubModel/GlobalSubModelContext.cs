using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    using SubModelContextTypeIndex = uint;

    internal struct RegisteredSubModelContext
    {
        public static SubModelContextTypeIndex InvalidSubModelContextTypeIndex
        {
            get => SubModelContextTypeIndex.MaxValue;
        }
        internal static SubModelContextTypeIndex SubModelContextTypeCounter = 0;

        public static SubModelContextTypeIndex GetSubModelContextTypeIndex<T>()
        {
            SubModelContextTypeIndex idx = RegisteredSubModelContext<T>.Index;
            return idx;
        }

        public static SubModelContextTypeIndex RegisterSubModelContextTypeIndex<T>()
        {
            // Only register if it wasn't registed before
            if (RegisteredSubModelContext<T>.Index == InvalidSubModelContextTypeIndex)
            {
                RegisteredSubModelContext<T>.Index = ErsEngine.ERS_SubModel_RegisterSubModelContext();
            }
            return RegisteredSubModelContext<T>.Index;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct RegisteredSubModelContext<T>
    {

        static RegisteredSubModelContext() { Index = RegisteredSubModelContext.InvalidSubModelContextTypeIndex; }

        public static uint Index;
    }
}
