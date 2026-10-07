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

        public static string EditionName
        {
            get {
                unsafe
                {
                    char* heapAllocatedName = (char*)ErsEngine.ERS_License_EditionName();
                    string edition          = new string(heapAllocatedName);
                    ErsEngine.ERS_String_Destroy((nint)heapAllocatedName);
                    return edition;
                }
            }
        }

        public static UInt32 MaxJobSystemCores() => ErsEngine.ERS_License_MaxJobSystemCores();

        public static UInt32 MaxComponentTypes() => ErsEngine.ERS_License_MaxComponentTypes();
    }
}
