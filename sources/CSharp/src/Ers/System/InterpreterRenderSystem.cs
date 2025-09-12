using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;

namespace Ers
{
    public static class InterpreterRenderSystem
    {
        public static void Render()
        {
            ErsEngine.ERS_InterpreterRenderSystem_Render();
        }
    }
}
