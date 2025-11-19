using System.Runtime.InteropServices;

namespace Ers
{
    /// <summary>
    /// Color union with RGBA components.
    /// Memory layout: ABGR.
    /// </summary>
    [StructLayout(LayoutKind.Explicit)]
    public struct Color
    {
        /// <summary>
        /// The full ABGR color as a 32-bit unsigned integer.
        /// </summary>
        [FieldOffset(0)]
        public UInt32 Value;

        /// <summary>
        /// The alpha color component.
        /// </summary>
        [FieldOffset(0)]
        public byte R;

        /// <summary>
        /// The blue color component.
        /// </summary>
        [FieldOffset(1)]
        public byte G;

        /// <summary>
        /// The green color component.
        /// </summary>
        [FieldOffset(2)]
        public byte B;

        /// <summary>
        /// The red color component.
        /// </summary>
        [FieldOffset(3)]
        public byte A;

        /// <summary>
        /// Default constructor. Creates a black, transparent color.
        ///
        /// <para>Use <see cref="FromInt(uint)"/>, <see cref="FromBytes(byte, byte, byte, byte)"/>, or <see cref="FromFloats(float, float,
        /// float, float)"/> instead.</para>
        /// </summary>
        public Color()
        {
            Value = 0;
            R     = 0;
            G     = 0;
            B     = 0;
        }

        /// <summary>
        /// Create new color from a <see cref="UInt32"/> value.
        /// </summary>
        /// <param name="value">The color value (ABGR format)</param>
        public static Color FromInt(uint value) { return new Color { R = 0, G = 0, B = 0, Value = value }; }

        /// <summary>
        /// Create a new color from RGBA byte components.
        /// </summary>
        /// <param name="red">Red (0-255)</param>
        /// <param name="green">Green (0-255)</param>
        /// <param name="blue">Blue (0-255)</param>
        /// <param name="alpha">Alpha (0-255)</param>
        public static Color FromBytes(byte red, byte green, byte blue, byte alpha = 255)
        {
            return new Color { Value = 0, R = red, G = green, B = blue, A = alpha };
        }

        /// <summary>
        /// Create a new color from RGBA float components.
        /// </summary>
        /// <param name="red">Red (0.0-1.0)</param>
        /// <param name="green">Green (0.0-1.0)</param>
        /// <param name="blue">Blue (0.0-1.0)</param>
        /// <param name="alpha">Alpha (0.0-1.0)</param>
        public static Color FromFloats(float red, float green, float blue, float alpha = 1.0f)
        {
            return new Color {
                Value = 0, R = (byte)(red * 255.0f), G = (byte)(green * 255.0f), B = (byte)(blue * 255.0f), A = (byte)(alpha * 255.0f)
            };
        }

        /// <summary>
        /// Implicit conversion from System.Drawing.Color to Ers.Color.
        /// </summary>
        /// <param name="color">System.Drawing.Color to convert</param>
        public static implicit operator Color(System.Drawing.Color color) => FromBytes(color.R, color.G, color.B, color.A);

        /// <summary>
        /// Implicit conversion from Ers.Color to System.Drawing.Color.
        /// </summary>
        /// <param name="color">Ers.Color to convert</param>
        public static implicit operator System.Drawing.Color(Color color)
        {
            return System.Drawing.Color.FromArgb(color.A, color.R, color.G, color.B);
        }

        public override bool Equals(object? obj)                => obj is Color other && Value == other.Value;
        public override int GetHashCode()                       => (int)Value;
        public static bool operator ==(Color left, Color right) => left.Value == right.Value;
        public static bool operator !=(Color left, Color right) => left.Value != right.Value;
    }
}
