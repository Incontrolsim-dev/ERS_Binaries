using System;

namespace Ers.Visualization
{
    public class Font
    {
        internal readonly IntPtr Data;

        internal Font(IntPtr corePointer) { Data = corePointer; }
    }
}
