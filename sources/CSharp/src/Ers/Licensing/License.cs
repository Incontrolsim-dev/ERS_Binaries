using Ers.Engine;

namespace Ers
{
    public static class License
    {
        public static bool HasFeature(string featureCode)
        {
            var featureCodeUtf8 = featureCode.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* featureCodeByte = featureCodeUtf8)
                {
                    return ErsEngine.ERS_License_HasFeature(featureCodeByte);
                }
            }
        }

        public static string EditionName()
        {
            unsafe
            {
                char* heapAllocatedName = (char*)ErsEngine.ERS_License_EditionName();
                string edition          = new string(heapAllocatedName);
                ErsEngine.ERS_STRING_DISPOSE((nint)heapAllocatedName);

                return edition;
            }
        }

        public static int MaxJobSystemCores() { return ErsEngine.ERS_License_GetLimits_MaxJobSystemCores(); }
        public static int MaxComponentTypes() { return ErsEngine.ERS_License_GetLimits_MaxComponentTypes(); }
    }
}
