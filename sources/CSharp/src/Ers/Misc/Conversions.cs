using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ers
{
    internal static class Conversions
    {
        /// <summary>
        /// Returns a UTF-8 encoded, null-terminated byte array version of the string,
        /// matching the behavior used in P/Invoke marshalling.
        /// </summary>
        internal static byte[] ToUtf8NullTerminated(this string str)
        {
            if (str is null)
                return new byte[1] { 0 }; // Only the null terminator

            int byteCount = Encoding.UTF8.GetByteCount(str);
            byte[] buffer = new byte[byteCount + 1]; // +1 for null terminator

            Encoding.UTF8.GetBytes(str, 0, str.Length, buffer, 0);
            buffer[byteCount] = 0; // Null-terminator

            return buffer;
        }
    }
}
