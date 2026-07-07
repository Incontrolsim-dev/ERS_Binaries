using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Manages the events of the <see cref="SubModel"/> attached to it.
    ///
    /// <para>Simulators may have connections between each other to perform "sync events" where data is shared between them.</para>
    /// </summary>
    public struct Simulator
    {
        // clang-format off

        /// <summary>
        /// The ID of the simulator.
        /// </summary>
        [Category("Simulator")]
        [Description("The ID of the simulator.")]
        public readonly Int32 ID { get => ErsEngine.ERS_Simulator_GetID(CorePtr); }

        /// <summary>
        /// The name of the simulator.
        /// </summary>
        [Category("Simulator")]
        [Description("The name of the simulator.")]
        public readonly string Name { get => GetName(); }


        /// <summary>
        /// The type of the simulator. See <see cref="SimulatorType"/>.
        /// </summary>
        [Category("Simulator")]
        [Description("The type of simulator.")]
        public readonly SimulatorType Type { get => (SimulatorType)ErsEngine.ERS_Simulator_GetSimulatorType(CorePtr); }

        /// <summary>
        /// The current time of the simulator.
        /// </summary>
        [Category("Simulator")]
        [Description("The current time of the simulator.")]
        public readonly SimulationTime CurrentTime { get => ErsEngine.ERS_Simulator_GetCurrentTime(CorePtr); }

        /// <summary>
        /// Get the <see cref="ModelContainer"/> to which this simulator is attached.
        /// </summary>
        public readonly ModelContainer AttachedModelContainer { get => new ModelContainer(ErsEngine.ERS_Simulator_GetAttachedModelContainer(CorePtr));  }

        // clang-format on

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr = IntPtr.Zero;

        internal Simulator(IntPtr corePtr) { CorePtr = corePtr; }

        /// <summary>
        /// Check whether the Simulator is valid.
        ///
        /// <para>A Simulator is valid when it is contained in the <see cref="ModelContainer"/> it is connected to.</para>
        /// </summary>
        /// <returns>True when it is valid, false when it is not.</returns>
        public readonly bool Valid()
        {
            if (CorePtr == IntPtr.Zero)
                return false;

            return true;
        }

        public void EnterSubModel() => ErsEngine.ERS_ThreadLocal_EnterSubModel(ErsEngine.ERS_Simulator_GetSubModel(CorePtr));

        public void ExitSubModel()
        {
            Debug.Assert(ErsEngine.ERS_Simulator_GetSubModel(CorePtr) == ErsEngine.ERS_ThreadLocal_GetSubModel());
            ErsEngine.ERS_ThreadLocal_ExitSubModel();
        }

        /// <summary>
        /// Get the library collection for this simulator.
        /// </summary>
        /// <returns>The library collection</returns>
        public LibraryCollection GetLibraryCollection()
        {
            IntPtr ptr = ErsEngine.ERS_Simulator_GetLibraryCollection(CorePtr);
            return new LibraryCollection(ptr);
        }

        private readonly string GetName()
        {
            IntPtr ptr     = ErsEngine.ERS_Simulator_GetName(CorePtr);
            string? result = Marshal.PtrToStringAnsi(ptr);
            Debug.Assert(result != null);
            ErsEngine.ERS_String_Destroy(ptr);
            return result;
        }

        /// <summary>
        /// Get the names of all simulators that can schedule to this simulator.
        /// </summary>
        /// <returns></returns>
        public readonly string[] GetDependencyNames()
        {
            nuint totalDependencies  = ErsEngine.ERS_Simulator_GetDependenciesAmount(CorePtr);
            string[] dependencyNames = new string[totalDependencies];

            for (nuint i = 0; i < (nuint)dependencyNames.Length; i++)
            {
                IntPtr ptr             = ErsEngine.ERS_Simulator_GetDependencyName(CorePtr, i);
                string? dependencyName = Marshal.PtrToStringAnsi(ptr);
                Debug.Assert(dependencyName != null);
                ErsEngine.ERS_String_Destroy(ptr);
                dependencyNames[i] = dependencyName;
            }
            return dependencyNames;
        }

        /// <summary>
        /// Find a dependency of this simulator by its name.
        /// </summary>
        /// <param name="tag">The name of the dependency.</param>
        /// <returns></returns>
        public Simulator FindDependency(string tag)
        {
            var tagUtf8 = tag.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* tagByte = tagUtf8)
                {
                    IntPtr foundDependencyPtr = ErsEngine.ERS_Simulator_FindDependencyByName(CorePtr, tagByte, tag.Length);
                    return new Simulator(foundDependencyPtr);
                }
            }
        }

        /// <summary>
        /// Find a dependency of this simulator by its ID.
        /// </summary>
        /// <param name="simulatorId">The ID of the dependency.</param>
        /// <returns></returns>
        public Simulator FindDependency(Int32 simulatorId)
        {
            IntPtr foundDependencyPtr = ErsEngine.ERS_Simulator_FindDependencyById(CorePtr, simulatorId);
            return new Simulator(foundDependencyPtr);
        }

        /// <summary>
        /// Find the simulator to which this simulator can schedule events.
        /// </summary>
        /// <param name="name">The name of the simulator to find.</param>
        /// <returns>The simulator, or null if no such simulator exists.</returns>
        public Simulator? FindOutgoingDependency(string name)
        {
            var nameUtf8 = name.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* nameByte = nameUtf8)
                {
                    IntPtr found = ErsEngine.ERS_Simulator_FindOutgoingDependencyByName(CorePtr, nameByte, name.Length);
                    if (found == IntPtr.Zero)
                        return null;

                    return new Simulator(found);
                }
            }
        }

        /// <summary>
        /// Find a simulator to which this simulator can schedule events.
        /// </summary>
        /// <param name="simulatorId">The ID of the simulator to find.</param>
        /// <returns>The simulator, or null if no such simulator exists.</returns>
        public Simulator? FindOutgoingDependency(Int32 simulatorId)
        {
            IntPtr found = ErsEngine.ERS_Simulator_FindOutgoingDependencyById(CorePtr, simulatorId);
            if (found == IntPtr.Zero)
                return null;

            return new Simulator(found);
        }

        /// <summary>
        /// Check whether this simulator has a bidirectional dependency with another simulator, where all promises are 0.
        /// </summary>
        /// <param name="otherSimulatorId">The ID of the other simulator.</param>
        /// <returns></returns>
        public readonly bool IsRunTogether(int otherSimulatorId) => ErsEngine.ERS_Simulator_IsRunTogether(CorePtr, otherSimulatorId);

        /// <summary>
        /// Check whether this simulator has a direct dependency with another simulator that is bidirectional (both can schedule events on
        /// the other).
        /// </summary>
        /// <param name="otherSimulatorId">The ID of the other simulator.</param>
        /// <returns></returns>
        public readonly bool IsBiDirectional(int otherSimulatorId) => ErsEngine.ERS_Simulator_IsBiDirectional(CorePtr, otherSimulatorId);

        /// <summary>
        /// The time step of the simulator.
        /// </summary>
        public SimulationTime TimeStep
        {
            get => ErsEngine.ERS_Simulator_GetTimeStep(CorePtr);
            set => ErsEngine.ERS_Simulator_SetTimeStep(CorePtr, value);
        }

        /// <summary>
        /// The random seed of the simulator.
        /// </summary>
        public nuint Seed
        {
            get {
                IntPtr subModel = ErsEngine.ERS_Simulator_GetSubModel(CorePtr);
                return ErsEngine.ERS_SubModelRandomProperties_GetOriginalSeed(subModel);
            }
        }
    }
}
