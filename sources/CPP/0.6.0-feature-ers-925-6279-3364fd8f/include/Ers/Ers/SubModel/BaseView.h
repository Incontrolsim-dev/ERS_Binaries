#pragma once
#include "Ers/SubModel/Entity.h"
#include "Ers/Utility/Util.h"

namespace Ers
{

    /// @brief This class is the adapter between the core and Data to interact with views, that is querying an entity if it contains certain
    /// components and doesn't include other components.
    class BaseView
    {
      public:
        BaseView()                           = delete;
        BaseView(const BaseView&)            = delete;
        BaseView(BaseView&&)                 = default;
        BaseView& operator=(const BaseView&) = delete;
        BaseView& operator=(BaseView&& /*other*/) noexcept;
        virtual ~BaseView();

        Entity GetEntity();
        void* GetComponent(uint32_t typeIndex);
        bool Next();

      protected:
        BaseView(
            void* submodel,
            uint32_t* includedTypeIdArray,
            uint32_t includedTypeArraySize,
            uint32_t* excludedTypeIdArray,
            uint32_t excludedTypeArraySize);
        void* instance;
    };
} // namespace Ers
