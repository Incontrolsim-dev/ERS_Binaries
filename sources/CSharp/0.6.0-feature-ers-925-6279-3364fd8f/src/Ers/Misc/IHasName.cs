using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Ers
{
    public interface IHasName<T>
        where T : IHasName<T> {
        static abstract string Name { get; }
    }

    public static class NameUtf8Helper<T>
        where T : IHasName<T>
    {
        private static readonly byte[] _bytes = GetBytes();

        public static ReadOnlySpan<byte> NameUtf8Bytes => _bytes;

        private static byte[] GetBytes()
        {
            var props = typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Static);

            var prop =
                typeof(T).GetProperty("NameUtf8Bytes", System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.Public);
            if (prop is null)
                throw new InvalidOperationException($"Type {typeof(T)} does not define NameUtf8Bytes.");

            var value = prop.GetValue(null);

            return value switch { byte[] arr => arr,
                                  _          => throw new InvalidOperationException(
                                      $"Property NameUtf8Bytes on {typeof(T)} is not a supported type.") };
        }
    }

}
