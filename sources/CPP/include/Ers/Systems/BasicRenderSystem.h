#pragma once

#include "Ers/SubModel/SubModel.h"
#include "Ers/Visualization/RenderContext.h"

namespace Ers
{
    class BasicRenderSystem
    {
      public:
        /// @brief Render the BasicRenderComponent on all eligible entities in a given submodel in 2D.
        /// @param subModel The submodel in which the basic renders are rendered.
        /// @param renderContext The render context to use.
        static void Render2D(SubModel& subModel, Visualization::RenderContext& renderContext);
        /// @brief Render the BasicRenderComponent on all eligible entities in a given submodel in 3D.
        /// @param subModel The submodel in which the basic renders are rendered.
        /// @param renderContext The render context to use.
        static void Render3D(SubModel& subModel, Visualization::RenderContext& renderContext);
    };
} // namespace Ers
