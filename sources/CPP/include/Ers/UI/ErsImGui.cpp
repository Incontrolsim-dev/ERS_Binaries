#include "ErsImGui.h"

#include "Ers/Api.h"

namespace Ers
{
    void StyleColorsErsDark()
    {
        Ers::Engine::ERS_ImGui_StyleColorsErsDark();
    }

    void StyleColorsErsLight()
    {
        Ers::Engine::ERS_ImGui_StyleColorsErsLight();
    }

    bool SwitchButton(const char* label, bool& value, ImGuiButtonFlags flags)
    {
        return Ers::Engine::ERS_ImGui_SwitchButton(label, &value, flags);
    }

    bool DragVectorXYZ(const char* label, Vector3& vector, ImGuiSliderFlags flags)
    {
        return Ers::Engine::ERS_ImGui_DragVectorXYZ(label, &vector.X, &vector.Y, &vector.Z, flags);
    }
} // namespace Ers
