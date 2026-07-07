#include "Ers/Api.h"
#include "Ers/Utility/Util.h"
#include "View.h"

namespace Ers
{

    BaseView::BaseView(
        void* submodel,
        uint32_t* includedTypeIdArray,
        uint32_t includedTypeArraySize,
        uint32_t* excludedTypeIdArray,
        uint32_t excludedTypeArraySize)
    {
        corePtr = Ers::Engine::ERS_Submodel_View_Create(
            submodel, includedTypeIdArray, includedTypeArraySize, excludedTypeIdArray, excludedTypeArraySize);
    }

    BaseView& BaseView::operator=(BaseView&& other) noexcept
    {
        // Transfer ownership of allocated view in core
        corePtr       = other.corePtr;
        other.corePtr = nullptr;
        return *this;
    }

    BaseView::~BaseView()
    {
        if (corePtr)
        {
            Ers::Engine::ERS_Submodel_View_Destroy(corePtr);
        }
    }

    bool BaseView::Next()
    {
        return Ers::Engine::ERS_Submodel_View_Next(corePtr);
    }

    Entity BaseView::GetEntity()
    {
        return Ers::Engine::ERS_Submodel_View_GetEntity(corePtr);
    }

    void* BaseView::GetComponent(uint32_t typeIndex)
    {
        return Ers::Engine::ERS_Submodel_View_GetComponent(corePtr, typeIndex);
    }
} // namespace Ers
