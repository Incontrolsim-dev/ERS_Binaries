using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Ers.Engine;
using Ers.Visualization;

namespace Ers
{
    public static class InterpreterRenderSystem
    {
        public static void Render2D() { ErsEngine.ERS_InterpreterRenderSystem_Render2D(); }

        public static void BuildMesh3D(Mesh mesh) { ErsEngine.ERS_InterpreterRenderSystem_BuildMesh3D(mesh.Data); }
    }
}
