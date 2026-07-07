#include "InputHandler.h"

#include "Ers/Api.h"

namespace Ers
{
    InputAction::InputAction(void* corePtr) :
        corePtr(corePtr)
    {
    }

    InputAction::InputAction(const char* name)
    {
        corePtr = Ers::Engine::ERS_InputHandler_GetAction(name);
    }

    bool InputAction::IsTriggered() const
    {
        return Ers::Engine::ERS_InputAction_GetTriggered(corePtr);
    }

    bool InputAction::IsReleased() const
    {
        return Ers::Engine::ERS_InputAction_GetReleased(corePtr);
    }

    float InputAction::GetStrength() const
    {
        return Ers::Engine::ERS_InputAction_GetStrength(corePtr);
    }

    void InputAction::SetTriggered(bool triggered, float strength)
    {
        Ers::Engine::ERS_InputAction_SetTriggered(corePtr, triggered);
        Ers::Engine::ERS_InputAction_SetStrength(corePtr, strength);
    }

    InputAction InputHandler::GetAction(const char* name)
    {
        return InputAction(Ers::Engine::ERS_InputHandler_GetAction(name));
    }

    bool InputHandler::ExistsAction(const char* name)
    {
        return Ers::Engine::ERS_InputHandler_ExistsAction(name);
    }

    void InputHandler::Cycle()
    {
        Ers::Engine::ERS_InputHandler_Cycle();
    }

    void InputHandler::UpdateMousePos(int x, int y)
    {
        Ers::Engine::ERS_InputHandler_UpdateMousePos(x, y);
    }
} // namespace Ers
