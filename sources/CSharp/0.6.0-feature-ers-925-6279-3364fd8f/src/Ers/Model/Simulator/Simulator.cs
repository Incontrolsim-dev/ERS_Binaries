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
        public readonly Int32 ID { get => ErsEngine.ERS_Simulator_GetID(Data); }

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
        public readonly SimulatorType Type { get => (SimulatorType)ErsEngine.ERS_Simulator_GetSimulatorType(Data); }

        /// <summary>
        /// The current time of the simulator.
        /// </summary>
        [Category("Simulator")]
        [Description("The current time of the simulator.")]
        public SimulationTime CurrentTime { get => GetCurrentTime(); }

        // clang-format on

        internal readonly IntPtr Data;

        internal Simulator(IntPtr instance) { Data = instance; }

        /// <summary>
        /// Check whether the Simulator is valid.
        ///
        /// <para>A Simulator is valid when it is contained in the <see cref="ModelContainer"/> it is connected to.</para>
        /// </summary>
        /// <returns>True when it is valid, false when it is not.</returns>
        public readonly bool Valid()
        {
            if (Data == IntPtr.Zero)
                return false;

            return true;
        }

        public void EnterSubModel() => ErsEngine.ERS_ThreadLocal_EnterSubModel(ErsEngine.ERS_Simulator_GetSubModel(Data));
        public void ExitSubModel()
        {
            Debug.Assert(ErsEngine.ERS_Simulator_GetSubModel(Data) == ErsEngine.ERS_ThreadLocal_GetSubModel());
            ErsEngine.ERS_ThreadLocal_ExitSubModel();
        }

        private readonly string GetName()
        {
            IntPtr ptr     = ErsEngine.ERS_Simulator_GetName(Data);
            string? result = Marshal.PtrToStringAnsi(ptr);
            Debug.Assert(result != null);
            ErsEngine.ERS_STRING_DISPOSE(ptr);
            return result;
        }

        /// <summary>
        /// Get the names of all simulators that can schedule to this simulator.
        /// </summary>
        /// <returns></returns>
        public readonly string[] GetDependencyNames()
        {
            nuint totalDependencies  = ErsEngine.ERS_Simulator_GetDependenciesAmount(Data);
            string[] dependencyNames = new string[totalDependencies];

            for (nuint i = 0; i < (nuint)dependencyNames.Length; i++)
            {
                IntPtr ptr             = ErsEngine.ERS_Simulator_GetDependencyName(Data, i);
                string? dependencyName = Marshal.PtrToStringAnsi(ptr);
                Debug.Assert(dependencyName != null);
                ErsEngine.ERS_STRING_DISPOSE(ptr);
                dependencyNames[i] = dependencyName;
            }
            return dependencyNames;
        }

        /// <summary>
        /// Get the time the Simulator is currently at.
        /// </summary>
        /// <returns></returns>
        public readonly SimulationTime GetCurrentTime() => ErsEngine.ERS_Simulator_GetCurrentTime(Data);

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
                    IntPtr foundDependencyPtr = ErsEngine.ERS_Simulator_FindDependencyByName(Data, tagByte, tag.Length);
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
            IntPtr foundDependencyPtr = ErsEngine.ERS_Simulator_FindDependencyById(Data, simulatorId);
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
                    IntPtr found = ErsEngine.ERS_Simulator_FindOutgoingDependencyByName(Data, nameByte, name.Length);
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
            IntPtr found = ErsEngine.ERS_Simulator_FindOutgoingDependencyById(Data, simulatorId);
            if (found == IntPtr.Zero)
                return null;

            return new Simulator(found);
        }

        /// <summary>
        /// Check whether this simulator has a bidirectional dependency with another simulator, where all promises are 0.
        /// </summary>
        /// <param name="otherSimulatorId">The ID of the other simulator.</param>
        /// <returns></returns>
        public readonly bool IsRunTogether(int otherSimulatorId) => ErsEngine.ERS_Simulator_IsRunTogether(Data, otherSimulatorId);

        /// <summary>
        /// Check whether this simulator has a direct dependency with another simulator that is bidirectional (both can schedule events on
        /// the other).
        /// </summary>
        /// <param name="otherSimulatorId">The ID of the other simulator.</param>
        /// <returns></returns>
        public readonly bool IsBiDirectional(int otherSimulatorId) => ErsEngine.ERS_Simulator_IsBiDirectional(Data, otherSimulatorId);

        /// @brief Get the Timestep of the given Simulator
        /// <param name="instance [in]">Pointer to the given instance of the Simulator in the core.</param>
        /// @return the timestep set on the simulator
        public SimulationTime GetTimeStep() { return ErsEngine.ERS_Simulator_GetTimeStep(Data); }

        /// @brief Set the Timestep of the given Simulator
        /// <param name="instance [in]">Pointer to the given instance of the Simulator in the core.</param>
        /// <param name="newTimeStep [in]">New timestep.</param>
        void SetTimeStep(SimulationTime newTimeStep) { ErsEngine.ERS_Simulator_SetTimeStep(Data, newTimeStep); }
    }
}
