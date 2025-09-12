using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;

namespace Ers.Interpreter
{
    public readonly ref struct InterpreterVariable
    (nint data)
    {
        public readonly nint Data = data;

        /// <summary>
        /// Creates a entity in the script environment.
        /// </summary>
        /// <param name="entity"></param>
        /// <returns></returns>
        public static InterpreterVariable CreateEntity(Entity entity)
        {
            nint scriptEntity = ErsEngine.ERS_InterpreterVariable_CreateEntity(entity);
            var result        = new InterpreterVariable(scriptEntity);
            return result;
        }

        /// <summary>
        /// Creates a double in the script environment.
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static InterpreterVariable CreateDouble(double value)
        {
            nint scriptDouble = ErsEngine.ERS_InterpreterVariable_CreateDouble(value);
            var result        = new InterpreterVariable(scriptDouble);
            return result;
        }

        /// <summary>
        /// Creates a string in the script environment.
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static InterpreterVariable CreateString(string value)
        {
            var valueUtf8 = value.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* valueByte = valueUtf8)
                {
                    nint scriptString = ErsEngine.ERS_InterpreterVariable_CreateString(valueByte);
                    var result        = new InterpreterVariable(scriptString);
                    return result;
                }
            }
        }

        /// <summary>
        /// Creates a uint64 in the script environment.
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static InterpreterVariable CreateUInt64(UInt64 value)
        {
            nint scriptUInt64 = ErsEngine.ERS_InterpreterVariable_CreateUInt64(value);
            var result        = new InterpreterVariable(scriptUInt64);
            return result;
        }

        /// <summary>
        /// Creates a boolean in the script environment.
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public static InterpreterVariable CreateBool(bool value)
        {
            nint scriptBool = ErsEngine.ERS_InterpreterVariable_CreateBool(value);
            var result      = new InterpreterVariable(scriptBool);
            return result;
        }

        /// <summary>
        /// Returns a None variable.
        /// </summary>
        /// <returns></returns>
        public static InterpreterVariable None()
        {
            return new InterpreterVariable(ErsEngine.ERS_InterpreterVariable_None());
        }
    }
}
