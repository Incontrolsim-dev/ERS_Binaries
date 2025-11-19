using System;

namespace Ers
{
    public class Font
    {
        internal readonly IntPtr Data;

        internal Font(IntPtr corePointer) { Data = corePointer; }
    }
}
