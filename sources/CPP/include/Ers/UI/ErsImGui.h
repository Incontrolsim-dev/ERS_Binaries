#pragma once

#include "Ers/External/ImGuiCpp.hpp"
#include "Ers/Math/HMM/VectorMath.h"

namespace Ers
{
    /// @brief Set the ImGui style and colors to the ERS dark theme.
    void StyleColorsErsDark();

    /// @brief Set the ImGui style and colors to the ERS light theme.
    void StyleColorsErsLight();

    /// @brief Switch button (toggle).
    /// @param label The label/ID of the button.
    /// @param value The state of the button. Will be modified when the button is switched.
    /// @param flags Any ImGuiButtonFlags for the button.
    /// @return True when the buttons is toggled, otherwise false.
    bool SwitchButton(const char* label, bool& value, ImGuiButtonFlags flags = ImGuiButtonFlags_None);

    /// @brief Input widget for a Vector3, consisting of three DragFloat widgets with color-coded XYZ labels.
    /// @param label The label/ID for the widget.
    /// @param vector The vector to use.
    /// @param flags Any ImGuiSliderFlags for the internal DragFloat widgets.
    /// @return True when input was given, otherwise false.
    bool DragVectorXYZ(const char* label, Vector3& vector, ImGuiSliderFlags flags = ImGuiSliderFlags_None);
} // namespace Ers
