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
        instance = ersAPIFunctionPointers.ERS_Submodel_View_Create(
            submodel, includedTypeIdArray, includedTypeArraySize, excludedTypeIdArray, excludedTypeArraySize);
    }

    BaseView& BaseView::operator=(BaseView&& other) noexcept
    {
        // Transfer ownership of allocated view in core
        instance       = other.instance;
        other.instance = nullptr;
        return *this;
    }

    BaseView::~BaseView()
    {
        if (instance)
        {
            ersAPIFunctionPointers.ERS_Submodel_View_Dispose(instance);
        }
    }

    bool BaseView::Next()
    {
        return ersAPIFunctionPointers.ERS_Submodel_View_Next(instance);
    }

    Entity BaseView::GetEntity()
    {
        return ersAPIFunctionPointers.ERS_Submodel_View_GetEntity(instance);
    }

    void* BaseView::GetComponent(uint32_t typeIndex)
    {
        return ersAPIFunctionPointers.ERS_Submodel_View_GetComponent(instance, typeIndex);
    }
} // namespace Ers
