#include "InterpreterRenderSystem.h"
#include "Ers/Api.h"
#include "Ers/Visualization/Mesh.h"

namespace Ers::Systems
{
    void InterpreterRenderSystem::Render2D()
    {
        ersAPIFunctionPointers.ERS_InterpreterRenderSystem_Render2D();
    }

    void InterpreterRenderSystem::BuildMesh3D(Ers::Mesh& mesh)
    {
        ersAPIFunctionPointers.ERS_InterpreterRenderSystem_BuildMesh3D(mesh.Data());
    }
} // namespace Ers::Systems
