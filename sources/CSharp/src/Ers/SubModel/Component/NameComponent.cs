using Ers.Engine;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// Component defining the name of an entity.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct NameComponent : ICoreComponent
    {
        /// <summary>
        /// The name of the entity.
        /// </summary>
        [Category("Name")]
        [Description("The name of the entity.")]
        public string Name
        {
            get {
                string? result = Marshal.PtrToStringAnsi(ErsEngine.ERS_NameComponent_GetName(CorePointer()));
                Debug.Assert(result != null);
                return result;
            }
            set {
                var valueUtf8 = value.ToUtf8NullTerminated();
                unsafe
                {
                    fixed(byte* valueByte = valueUtf8)
                    {
                        ErsEngine.ERS_NameComponent_SetName(CorePointer(), valueByte, value.Length);
                    }
                }
            }
        }

        /// <summary>
        /// The type ID of the component in the ERS core.
        /// </summary>
        /// <returns></returns>
        public static nuint CoreTypeId() => ErsEngine.ERS_NameComponent_TypeId();

        private IntPtr CorePointer()
        {
            unsafe
            {
                fixed(NameComponent* ptr = &this)
                {
                    return (IntPtr)ptr;
                }
            }
        }
    }
}
