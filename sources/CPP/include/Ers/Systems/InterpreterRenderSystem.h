#pragma once

namespace Ers
{
    class Mesh;
}

namespace Ers::Systems
{
    /// @brief System for rendering using the interpreter.
    class InterpreterRenderSystem
    {
      public:
        /// @brief Render 2D content.
        static void Render2D();

        /// @brief Build a 3D mesh.
        /// @param mesh The mesh to build
        static void BuildMesh3D(Ers::Mesh& mesh);
    };
} // namespace Ers::Systems
