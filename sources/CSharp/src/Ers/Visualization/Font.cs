using System;

namespace Ers
{
    public class Font
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;

        internal Font(IntPtr corePtr) { CorePtr = corePtr; }
    }
}
