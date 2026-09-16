using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ers;

namespace SourceQueueServerSink
{
    /// <summary>
    /// Relevant information for a product.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Product : IDataComponent
    {
        public bool Filled = false;

        public Product()
        {
        }
    }
}
