using System.Numerics;
using Ers.Engine;
using ImGuiNET;

namespace Ers
{
    /// <summary>
    /// ERS ImGui related functions.
    /// </summary>
    public static class ErsImGui
    {
        /// <summary>
        /// Set the ImGui style and colors to the ERS dark theme.
        /// </summary>
        public static void StyleColorsErsDark() => ErsEngine.ERS_ImGui_StyleColorsErsDark();

        /// <summary>
        /// Set the ImGui style and colors to the ERS light theme.
        /// </summary>
        public static void StyleColorsErsLight() => ErsEngine.ERS_ImGui_StyleColorsErsLight();

        /// <summary>
        /// Switch button (toggle).
        /// </summary>
        /// <param name="label">The label/ID of the button.</param>
        /// <param name="value">The state of the button. Will be modified when the button is switched.</param>
        /// <param name="flags">Any <see cref="ImGuiButtonFlags"/> for the button.</param>
        /// <returns>True when the button is toggled, otherwise false.</returns>
        public static bool SwitchButton(string label, ref bool value, ImGuiButtonFlags flags = ImGuiButtonFlags.None)
        {
            unsafe
            {
                fixed(byte* utf8Label = label.ToUtf8NullTerminated()) fixed(bool* valuePtr = &value)
                {
                    return ErsEngine.ERS_ImGui_SwitchButton(utf8Label, valuePtr, (int)flags);
                }
            }
        }

        // clang-format off

        /// <summary>
        /// Input widget for a <see cref="Vector3"/>, consisting of three DragFloat widgets with color-coded XYZ labels.
        /// </summary>
        /// <param name="label">The label/ID for the widget.</param>
        /// <param name="vector">The vector to use.</param>
        /// <param name="flags">Any <see cref="ImGuiSliderFlags"/> for the internal DragFloat widgets.</param>
        /// <returns>True when input was given, otherwise false.</returns>
        // clang-format on
        public static bool DragVectorXYZ(string label, ref Vector3 vector, ImGuiSliderFlags flags = ImGuiSliderFlags.None)
        {
            unsafe
            {
                // clang-format off
                fixed (byte* utf8Label = label.ToUtf8NullTerminated())
                fixed(float* xPtr = &vector.X)
                fixed(float* yPtr = &vector.Y)
                fixed(float* zPtr = &vector.Z)
                // clang-format on
                {
                    return ErsEngine.ERS_ImGui_DragVectorXYZ(utf8Label, (IntPtr)xPtr, (IntPtr)yPtr, (IntPtr)zPtr, (int)flags);
                }
            }
        }
    }
}
