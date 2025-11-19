using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;

namespace Ers.Interpreter
{
    public ref struct InterpreterArgs(nint data)
    {
        private readonly nint Data = data;

        public string GetStringArgument(int index)
        {
            nint stringData = ErsEngine.ERS_InterpreterArgs_GetStringArgument(Data, index);

            if (stringData == nint.Zero)
            {
                throw new ArgumentException($"Invalid string argument at index {index}.");
            }

            return Marshal.PtrToStringAnsi(stringData);
        }

        public double GetDoubleArgument(int index) { return ErsEngine.ERS_InterpreterArgs_GetDoubleArgument(Data, index); }
        public Entity GetEntityArgument(int index) { return ErsEngine.ERS_InterpreterArgs_GetEntityArgument(Data, index); }

        public Int64 GetInt64Argument(int index) { return ErsEngine.ERS_InterpreterArgs_GetInt64Argument(Data, index); }

        public bool GetBoolArgument(int index) { return ErsEngine.ERS_InterpreterArgs_GetBoolArgument(Data, index); }

        // Method to get the number of arguments
        public int GetArgCount() { return (int)ErsEngine.ERS_InterpreterArgs_GetArgCount(Data); }

        public void SetArgument(int index, InterpreterVariable variable)
        {
            ErsEngine.ERS_InterpreterArgs_SetArgument(Data, index, variable.Data);
        }

        public void Destruct() { ErsEngine.ERS_InterpreterArgs_Destruct(Data); }

        public bool HasAttribute(InterpreterVariable obj, string functionName)
        {
            unsafe
            {
                var functionNameUtf8 = functionName.ToUtf8NullTerminated();
                fixed(byte* functionNameByte = functionNameUtf8)
                {
                    return ErsEngine.ERS_InterpreterArgs_HasAttribute(Data, obj.Data, functionNameByte);
                }
            }
        }

        public InterpreterVariable DynamicInvoke(InterpreterVariable obj, string functionName)
        {
            unsafe
            {
                var functionNameUtf8 = functionName.ToUtf8NullTerminated();
                fixed(byte* functionNameByte = functionNameUtf8)
                {
                    return new InterpreterVariable(ErsEngine.ERS_InterpreterArgs_DynamicInvoke(Data, obj.Data, functionNameByte));
                }
            }
        }

        public static InterpreterArgs Create(int count) { return new InterpreterArgs(ErsEngine.ERS_InterpreterArgs_Create(count)); }
    }
}
