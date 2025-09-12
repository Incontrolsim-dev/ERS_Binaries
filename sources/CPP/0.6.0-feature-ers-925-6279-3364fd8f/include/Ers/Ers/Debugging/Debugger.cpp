#include "Debugger.h"

#include "Ers/Api.h"

namespace Ers
{
    Debugger::Debugger(Ers::ModelContainer& modelContainer)
    {
        coreInstance = ersAPIFunctionPointers.ERS_Debugger_Create(modelContainer.Data());
    }

    Debugger::~Debugger()
    {
        ersAPIFunctionPointers.ERS_Debugger_Destroy(coreInstance);
    }

    void Debugger::Update()
    {
        ersAPIFunctionPointers.ERS_Debugger_Update(coreInstance);
    }
} // namespace Ers
