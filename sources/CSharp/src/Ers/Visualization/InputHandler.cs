using Ers.Engine;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Ers
{
    public class InputAction
    {
        internal readonly IntPtr Data;

        internal InputAction(IntPtr coreInstance) { Data = coreInstance; }

        /// <summary>
        /// Get the InputAction with a given name. If it does not exist, it will be created.
        /// </summary>
        /// <param name="name"></param>
        public InputAction(string name)
        {
            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    Data = ErsEngine.ERS_InputHandler_GetAction(nameByte);
                }
            }
        }

        /// <summary>
        /// Whether the action is currently triggered.
        /// </summary>
        /// <returns></returns>
        public bool IsTriggered()
        {
            unsafe
            {
                return *(bool*)ErsEngine.ERS_InputAction_Triggered(Data);
            }
        }

        /// <summary>
        /// Whether the action was previously triggered.
        /// </summary>
        /// <returns></returns>
        public bool IsReleased()
        {
            unsafe
            {
                return *(bool*)ErsEngine.ERS_InputAction_Released(Data);
            }
        }

        /// <summary>
        /// The currently strength of the action.
        /// </summary>
        public float Strength
        {
            get => ErsEngine.ERS_InputAction_Strength(Data);
        }

        /// <summary>
        /// Set the action as triggered or not.
        /// </summary>
        /// <param name="triggered">Whether the action should be set to be triggered.</param>
        /// <param name="strength">The strength of the trigger.</param>
        public void SetTriggered(bool triggered, float strength = 1.0f)
        {
            unsafe
            {
                *(bool*)ErsEngine.ERS_InputAction_Triggered(Data) = triggered;
                *(float*)ErsEngine.ERS_InputAction_Strength(Data) = strength;
            }
        }
    }

    /// <summary>
    /// Handler for mouse and keynboard input.
    ///
    /// <para>Integrates with the <see cref="Camera3DController"/> to create camera movement by user input.</para>
    /// </summary>
    public static class InputHandler
    {
        /// <summary>
        /// Get an <see cref="InputAction"/> with a given name.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static InputAction GetAction(string name)
        {

            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    return new InputAction(ErsEngine.ERS_InputHandler_GetAction(nameByte));
                }
            }
        }

        /// <summary>
        /// Check whether an <see cref="InputAction"/> with a give name exists.
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static bool ExistsAction(string name)
        {

            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    return ErsEngine.ERS_InputHandler_ExistsAction(nameByte);
                }
            }
        }
        /// <summary>
        /// Cycle the input actions, resetting them for the next frame.
        ///
        /// <para>Call this function either at the beginning or end of your update loop.</para>
        /// </summary>
        public static void Cycle() { ErsEngine.ERS_InputHandler_Cycle(); }

        /// <summary>
        /// Update the mouse position for the input handler.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        public static void UpdateMousePos(int x, int y) { ErsEngine.ERS_InputHandler_UpdateMousePos(x, y); }
    }
}
