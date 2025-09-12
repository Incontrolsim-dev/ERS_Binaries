using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers.Interpreter
{
    /// <summary>
    /// Manages functions registered with the interpreter.
    /// </summary>
    public class Interpreter
    {
        public delegate InterpreterVariable InterpreterFunctionCallback(InterpreterArgs args);

        // Unmanaged callback function
        [MethodImpl(MethodImplOptions.AggressiveOptimization)]
        [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
        static IntPtr InterpreterFunctionUnmanaged(IntPtr delegateHandlePtr, IntPtr scriptArgumentsPtr)
        {
            GCHandle delegateHandle         = GCHandle.FromIntPtr(delegateHandlePtr);
            var cb                          = (InterpreterFunctionCallback)delegateHandle.Target!;
            InterpreterArgs interpreterArgs = new(scriptArgumentsPtr);
            var result                      = cb(interpreterArgs);
            return result.Data;
        }

        /// <summary>
        /// Registers a C# function to be used in the interpreter. Function can
        /// now be called from the interpreted environment. Make sure to
        /// register all functions before starting any scripting environment.
        /// </summary>
        /// <param name="functionName"></param>
        /// <param name="function"></param>
        public static void RegisterInterpreterFunction(string functionName, InterpreterFunctionCallback function)
        {
            var handle = GCHandle.Alloc(function, GCHandleType.Normal);
            unsafe
            {
                var intPtrValue = GCHandle.ToIntPtr(handle);

                // clang-format off
                fixed (byte* noDocs = "no docs"u8)
                {
                    // clang-format on

                    var functionNameUtf8 = functionName.ToUtf8NullTerminated();
                    fixed(byte* functionNameByte = functionNameUtf8)
                    {
                        ErsEngine.ERS_Interpreter_RegisterFunction(functionNameByte, intPtrValue, &InterpreterFunctionUnmanaged, noDocs);
                    }
                }
            }
        }
    }
}
