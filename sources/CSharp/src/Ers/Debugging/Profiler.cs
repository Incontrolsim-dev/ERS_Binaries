using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;

namespace Ers
{
    public class Profiler
    {
        /// <summary>
        /// This resets all profiling values. Starts a new sesion.
        /// </summary>
        public static void StartSession() { ErsEngine.ERS_Profiler_StartSession(); }

        /// <summary>
        /// Print profiling results since StartSession() has been called.
        /// </summary>
        public static void PrintResults() { ErsEngine.ERS_Profiler_PrintResults(); }
    }
}
