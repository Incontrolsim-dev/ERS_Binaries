using System;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    public enum ChannelType
    {
        Input  = 0,
        Output = 1,
    }
    ;

    [StructLayout(LayoutKind.Sequential)]
    public struct ChannelComponent : ICoreComponent
    {
        public static nuint CoreTypeId() => ErsEngine.ERS_ChannelComponent_TypeId();

        /// <summary>
        /// Get the type of the channel.
        /// </summary>
        /// <returns>The channel type</returns>
        public ChannelType GetType() { return (ChannelType)ErsEngine.ERS_ChannelComponent_GetType(CorePtr); }

        /// <summary>
        /// Get the entity this channel is connected to.
        /// </summary>
        /// <returns>The connected entity</returns>
        public Entity GetConnectedTo() { return ErsEngine.ERS_ChannelComponent_GetConnectedTo(CorePtr); }

        /// <summary>
        /// Check if the channel is open.
        /// </summary>
        /// <returns>True if the channel is open</returns>
        public bool IsOpen() { return ErsEngine.ERS_ChannelComponent_IsOpen(CorePtr); }

        /// <summary>
        /// Check if the channel is open.
        /// </summary>
        /// <param name="channel"></param>
        public static bool IsOpen(Entity channel) => ErsEngine.ERS_ChannelComponent_IsOpenStatic(channel);

        /// <summary>
        /// Send a child entity through the channel.
        /// </summary>
        /// <param name="channelFrom">The channel to send from</param>
        /// <param name="child">The entity to send</param>
        /// <returns>True if the child entity was succesfully sent, false otherwise</returns>
        public static bool Send(Entity channelFrom, Entity child) => ErsEngine.ERS_Channel_Send(channelFrom, child);

        /// <summary>
        /// Open a channel.
        /// </summary>
        /// <param name="channel">The channel entity</param>
        public static void Open(Entity channel) => ErsEngine.ERS_Channel_Open(channel);

        /// <summary>
        /// Close a channel
        /// </summary>
        /// <param name="channel">The channel entity</param>
        public static void Close(Entity channel) => ErsEngine.ERS_Channel_Close(channel);

        /// <summary>
        /// Check if a channel is ready.
        /// </summary>
        /// <param name="channel">The channel entity</param>
        /// <returns>True if the channel is ready</returns>
        public static bool IsReady(Entity channel) => ErsEngine.ERS_Channel_IsReady(channel);

        /// <summary>
        /// Connect two channels.
        /// </summary>
        /// <param name="input">Input channel entity</param>
        /// <param name="output">Output channel entity</param>
        public static void Connect(Entity input, Entity output) => ErsEngine.ERS_Channel_Connect(input, output);

        /// <summary>
        /// Add a <see cref="ChannelComponent"/> to an entity and register it on its parent's <see cref="ResourceComponent"/>.
        /// </summary>
        /// <param name="channel">The entity to add the <see cref="ChannelComponent"/> to</param>
        /// <param name="type">The type of the channel</param>
        /// <param name="resource">THe parent entity with a <see cref="ResourceComponent"/> to register the channel to</param>
        public static void AddChannelComponent(Entity channel, ChannelType type, Entity resource) =>
            ErsEngine.ERS_Channel_AddChannelComponent(channel, (int)type, resource);

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr
        {
            get {
                unsafe
                {
                    fixed(ChannelComponent* ptr = &this)
                    {
                        return (IntPtr)ptr;
                    }
                }
            }
        }
    }
}
