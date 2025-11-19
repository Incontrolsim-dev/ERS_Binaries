using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Settings class for getting and setting configuration values.
    /// </summary>
    public static class Settings
    {
        /// <summary>
        /// Get a setting value from the configuration.
        /// </summary>
        /// <param name="section">The section name</param>
        /// <param name="setting">The setting name</param>
        /// <param name="defaultValue">The default value if the setting doesn't exist</param>
        /// <returns>The setting value</returns>
        public static string GetSetting(string section, string setting, string defaultValue)
        {
            var sectionUtf8 = section.ToUtf8NullTerminated();
            var settingUtf8 = setting.ToUtf8NullTerminated();
            var defaultUtf8 = defaultValue.ToUtf8NullTerminated();

            unsafe
            {
                fixed(byte* sectionByte = sectionUtf8) fixed(byte* settingByte = settingUtf8) fixed(byte* defaultByte = defaultUtf8)
                {
                    IntPtr ptr     = ErsEngine.ERS_Settings_GetSetting(sectionByte, settingByte, defaultByte);
                    string? result = Marshal.PtrToStringAnsi(ptr);
                    Debug.Assert(result != null);
                    ErsEngine.ERS_STRING_DISPOSE(ptr);
                    return result;
                }
            }
        }

        /// <summary>
        /// Set a setting value in the configuration.
        /// </summary>
        /// <param name="section">The section name</param>
        /// <param name="setting">The setting name</param>
        /// <param name="value">The value to set</param>
        public static void SetSetting(string section, string setting, string value)
        {
            var sectionUtf8 = section.ToUtf8NullTerminated();
            var settingUtf8 = setting.ToUtf8NullTerminated();
            var valueUtf8   = value.ToUtf8NullTerminated();

            unsafe
            {
                fixed(byte* sectionByte = sectionUtf8) fixed(byte* settingByte = settingUtf8) fixed(byte* valueByte = valueUtf8)
                {
                    ErsEngine.ERS_Settings_SetSetting(sectionByte, settingByte, valueByte);
                }
            }
        }

        /// <summary>
        /// Clear all settings by deleting the ini file and resetting the settings to default.
        /// </summary>
        public static void ClearSettings() { ErsEngine.ERS_Settings_Clear(); }
    }
}
