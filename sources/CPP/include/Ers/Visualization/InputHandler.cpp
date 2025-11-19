#include "InputHandler.h"

#include "Ers/Api.h"

namespace Ers
{
    InputAction::InputAction(void* coreInstance) :
        coreInstance(coreInstance)
    {
    }

    InputAction::InputAction(const char* name)
    {
        coreInstance = ersAPIFunctionPointers.ERS_InputHandler_GetAction(name);
    }

    bool InputAction::IsTriggered() const
    {
        return *ersAPIFunctionPointers.ERS_InputAction_Triggered(coreInstance);
    }

    bool InputAction::IsReleased() const
    {
        return *ersAPIFunctionPointers.ERS_InputAction_Released(coreInstance);
    }

    float InputAction::GetStrength() const
    {
        return *ersAPIFunctionPointers.ERS_InputAction_Strength(coreInstance);
    }

    void InputAction::SetTriggered(bool triggered, float strength)
    {
        *ersAPIFunctionPointers.ERS_InputAction_Triggered(coreInstance) = triggered;
        *ersAPIFunctionPointers.ERS_InputAction_Strength(coreInstance)  = strength;
    }

    InputAction InputHandler::GetAction(const char* name)
    {
        return InputAction(ersAPIFunctionPointers.ERS_InputHandler_GetAction(name));
    }

    bool InputHandler::ExistsAction(const char* name)
    {
        return ersAPIFunctionPointers.ERS_InputHandler_ExistsAction(name);
    }

    void InputHandler::Cycle()
    {
        ersAPIFunctionPointers.ERS_InputHandler_Cycle();
    }

    void InputHandler::UpdateMousePos(int x, int y)
    {
        ersAPIFunctionPointers.ERS_InputHandler_UpdateMousePos(x, y);
    }
} // namespace Ers
