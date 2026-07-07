using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    [StructLayout(LayoutKind.Sequential)]
    public struct ResourceComponent : ICoreComponent
    {
        /// <summary>
        /// The number of input channels.
        /// </summary>
        public int NumInputChannels
        {
            get => (int)ErsEngine.ERS_ResourceComponent_GetNumInputChannels(CorePtr);
        }

        /// <summary>
        /// The number of output channels.
        /// </summary>
        public int NumOutputChannels
        {
            get => (int)ErsEngine.ERS_ResourceComponent_GetNumOutputChannels(CorePtr);
        }

        /// <summary>
        /// Close all input channels.
        /// </summary>
        public void CloseAllInput() { ErsEngine.ERS_ResourceComponent_CloseAllInput(CorePtr); }

        /// <summary>
        /// Open all input channels.
        /// </summary>
        public void OpenAllInput() { ErsEngine.ERS_ResourceComponent_OpenAllInput(CorePtr); }

        /// <summary>
        /// Close all output channels.
        /// </summary>
        public void CloseAllOutput() { ErsEngine.ERS_ResourceComponent_CloseAllOutput(CorePtr); }

        /// <summary>
        /// Open all output channels.
        /// </summary>
        public void OpenAllOutput() { ErsEngine.ERS_ResourceComponent_OpenAllOutput(CorePtr); }

        /// <summary>
        /// Get an input channel by index.
        /// </summary>
        /// <param name="index">The index of the input channel</param>
        /// <returns>The entity representing the input channel</returns>
        public Entity GetInputChannel(int index) => ErsEngine.ERS_ResourceComponent_GetInputChannel(CorePtr, (nuint)index);

        /// <summary>
        /// Get an output channel by index.
        /// </summary>
        /// <param name="index">The index of the output channel</param>
        /// <returns>The entity representing the output channel</returns>
        public Entity GetOutputChannel(int index) => ErsEngine.ERS_ResourceComponent_GetOutputChannel(CorePtr, (nuint)index);

        /// <summary>
        /// Get an interable range for input channels.
        /// </summary>
        /// <param name="resourceEntity">Resource entity with a <see cref="ResourceComponent"/></param>
        /// <returns>Iterable input channel range</returns>
        public static IEnumerable<Entity> InputChannels(Entity resourceEntity) =>
            new ChannelEnumerable(resourceEntity, enumerateOutputChannels: false);

        /// <summary>
        /// Get an interable range for output channels.
        /// </summary>
        /// <param name="resourceEntity">Resource entity with a <see cref="ResourceComponent"/></param>
        /// <returns>Iterable output channel range</returns>
        public static IEnumerable<Entity> OutputChannels(Entity resourceEntity) =>
            new ChannelEnumerable(resourceEntity, enumerateOutputChannels: true);

        private readonly struct ChannelEnumerable(Entity resourceEntity, bool enumerateOutputChannels) : IEnumerable<Entity>
        {
            private readonly Entity resourceEntity        = resourceEntity;
            private readonly bool enumerateOutputChannels = enumerateOutputChannels;

            public IEnumerator<Entity> GetEnumerator() => new ChannelEnumerator(resourceEntity, enumerateOutputChannels);

            IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
        }

        private class ChannelEnumerator : IEnumerator<Entity>
        {
            private readonly Entity resourceEntity;
            private readonly int channelCount;
            private readonly bool enumerateOutputChannels;
            private int currentIndex;

            public ChannelEnumerator(Entity resourceEntity, bool enumerateOutputChannels)
            {
                Ref<ResourceComponent> c = resourceEntity.GetComponent<ResourceComponent>();

                this.resourceEntity          = resourceEntity;
                this.channelCount            = enumerateOutputChannels ? c.Value.NumOutputChannels : c.Value.NumInputChannels;
                this.enumerateOutputChannels = enumerateOutputChannels;
                this.currentIndex            = -1;
            }

            public bool MoveNext()
            {
                if (currentIndex + 1 >= channelCount)
                {
                    currentIndex = channelCount;
                    return false;
                }

                currentIndex++;
                return true;
            }

            public void Reset() => currentIndex = -1;

            object IEnumerator.Current => Current;

            public Entity Current
            {
                get {
                    if (currentIndex < 0 || currentIndex >= channelCount)
                    {
                        throw new InvalidOperationException();
                    }

                    Ref<ResourceComponent> c = resourceEntity.GetComponent<ResourceComponent>();
                    return enumerateOutputChannels ? c.Value.GetOutputChannel(currentIndex) : c.Value.GetInputChannel(currentIndex);
                }
            }

            public void Dispose()
            {
                // Nothing to dispose
            }
        }

        public static nuint CoreTypeId() => ErsEngine.ERS_ResourceComponent_TypeId();

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr
        {
            get {
                unsafe
                {
                    fixed(ResourceComponent* compPtr = &this)
                    {
                        return (IntPtr)compPtr;
                    }
                }
            }
        }
    }
}
