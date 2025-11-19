using System;
using System.ComponentModel;
using System.Diagnostics;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Contains all <see cref="Simulator"/>s that make up the simulation.
    /// Manages the events between them and runs the entire model.
    ///
    /// For example, simulators in a ModelContainer can be synchronized (send data between each other).
    /// When a ModelContainer is updated, all Simulators in the container are also updated.
    /// </summary>
    public class ModelContainer
    {
        // clang-format off

        /// <summary>
        /// The current time of the simulation.
        /// </summary>
        [Category("Simulation")]
        [Description("The current time of the simulation.")]
        public SimulationTime CurrentTime { get => GetCurrentTime(); }

        // clang-format on

        private readonly IntPtr coreModelContainerInstance;

        internal IntPtr Data
        {
            get => coreModelContainerInstance;
        }

        internal ModelContainer(IntPtr coreInstance)
        {
            this.coreModelContainerInstance = coreInstance;
            ErsEngine.ERS_ModelContainer_Increase(coreInstance);
        }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~ModelContainer() { ErsEngine.ERS_ModelContainer_Release(coreModelContainerInstance); }

        /// <summary>
        /// Create a new ModelContainer.
        /// </summary>
        /// <returns></returns>
        public static ModelContainer CreateModelContainer()
        {
            IntPtr ptr            = ErsEngine.ERS_ModelContainer_CreateModelContainer();
            ModelContainer output = new ModelContainer(ptr);
            ErsEngine.ERS_ModelContainer_Release(ptr);
            return output;
        }

        /// <summary>
        /// Creata a new <see cref="Simulator"/> and add it to the ModelContainer.
        /// </summary>
        /// <param name="tag">The name of the new simulator.</param>
        /// <param name="type">The type of the new simulator.</param>
        /// <returns></returns>
        /// <exception cref="ArgumentException">When there already exists a simulator with the same name.</exception>
        public Simulator AddSimulator(string tag, SimulatorType type)
        {
            var tagUtf8 = tag.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* tagByte = tagUtf8)
                {
                    if (FindSimulator(tag).Valid())
                        throw new ArgumentException("Tag is already used, unique tag for this Container is required");

                    IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_AddSimulator(coreModelContainerInstance, tagByte, (byte)type);
                    return new Simulator(coreSimulator);
                }
            }
        }

        /// <summary>
        /// Remove a simulator from the ModelContainer, deleting the simulator.
        /// </summary>
        /// <param name="simulator">The simulator to remove.</param>
        public void RemoveSimulator(Simulator simulator)
        {
            Debug.Assert(simulator.Valid());
            Debug.Assert(FindSimulator(simulator.ID).Valid());
            ErsEngine.ERS_ModelContainer_RemoveSimulator(coreModelContainerInstance, simulator.Data);
        }

        /// <summary>
        /// Find a simulator in the ModelContainer by its name.
        /// </summary>
        /// <param name="tag">The name to search for.</param>
        /// <returns></returns>
        public Simulator FindSimulator(string tag)
        {
            var tagUtf8 = tag.ToUtf8NullTerminated();
            unsafe
            {
                fixed(byte* tagByte = tagUtf8)
                {
                    IntPtr foundCoreSimulator = ErsEngine.ERS_ModelContainer_FindSimulatorByTag(coreModelContainerInstance, tagByte);
                    return new Simulator(foundCoreSimulator);
                }
            }
        }

        /// <summary>
        /// Find a simulator in the ModelContainer by its ID.
        /// </summary>
        /// <param name="simulatorId">The ID of the simulator to search for.</param>
        /// <returns></returns>
        public Simulator FindSimulator(int simulatorId)
        {
            IntPtr foundCoreSimulator = ErsEngine.ERS_ModelContainer_FindSimulatorById(coreModelContainerInstance, simulatorId);
            return new Simulator(foundCoreSimulator);
        }

        /// <summary>
        /// The elapsed time of the simulation in the ModelContainer.
        /// </summary>
        /// <returns></returns>
        private SimulationTime GetCurrentTime() => ErsEngine.ERS_ModelContainer_CurrentTime(coreModelContainerInstance);

        /// <summary>
        /// Whether the ModelContainer is started.
        ///
        /// <para>
        /// A ModelContainer must be started before updates can be performed.
        /// After it has started, simulators can no longer be added or removed.
        /// </para>
        /// </summary>
        /// <returns></returns>
        public bool IsStarted() => ErsEngine.ERS_ModelContainer_IsStarted(coreModelContainerInstance);

        /// <summary>
        /// Start the ModelContainer. See <see cref="IsStarted"/> for more details.
        /// </summary>
        public void Start() => ErsEngine.ERS_ModelContainer_Start(coreModelContainerInstance);

        /// <summary>
        /// Perform an update step on the ModelContainer, updating all of its simulators.
        /// </summary>
        /// <param name="timeStep">The size of the step to perform.</param>
        public void Update(SimulationTime timeStep) => ErsEngine.ERS_ModelContainer_Update_Blocking(coreModelContainerInstance, timeStep);

        /// <summary>
        /// Add a dependency from one simulator to another, so from simulator A can be schedule to simulator B.
        /// </summary>
        /// <param name="from">The simulator from which events will be scheduled (Simulator A).</param>
        /// <param name="to">The simulator to which events will be scheduled (Simulator B).</param>
        public void AddSimulatorDependency(Simulator from, Simulator to)
        {
            Debug.Assert(from.Valid());
            Debug.Assert(to.Valid());
            ErsEngine.ERS_ModelContainer_AddSimulatorDependency(coreModelContainerInstance, from.Data, to.Data);
        }

        /// <summary>
        /// Remove a dependency between two simulators.
        /// </summary>
        /// <param name="from">The simulator from which events would be scheduled.</param>
        /// <param name="to">The simulator to which events would be scheduled.</param>
        public void RemoveSimulatorDependency(Simulator from, Simulator to)
        {
            Debug.Assert(from.Valid());
            Debug.Assert(to.Valid());
            ErsEngine.ERS_ModelContainer_RemoveSimulatorDependency(coreModelContainerInstance, from.Data, to.Data);
        }

        /// <summary>
        /// Get all simulators in the ModelContainer.
        /// </summary>
        /// <returns></returns>
        public Simulator[] GetSimulators()
        {
            Simulator[] simulators = new Simulator[SimulatorCount()];
            for (int i = 0; i < simulators.Length; i++)
            {
                IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_GetSimulator(coreModelContainerInstance, i);
                simulators[i]        = new Simulator(coreSimulator);
            }
            return simulators;
        }

        /// <summary>
        /// Get a simulator in the ModelContainer by its ID.
        /// </summary>
        /// <param name="simulatorId">The ID of the simulator.</param>
        /// <returns></returns>
        public Simulator GetSimulator(int simulatorId)
        {
            IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_GetSimulatorById(coreModelContainerInstance, simulatorId);
            return new Simulator(coreSimulator);
        }

        /// <summary>
        /// Get a simulator in the ModelContainer by its index.
        /// </summary>
        /// <param name="index">The index of the simulator.</param>
        /// <returns></returns>
        public Simulator GetSimulatorByIndex(int index)
        {
            IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_GetSimulator(coreModelContainerInstance, index);
            return new Simulator(coreSimulator);
        }

        /// <summary>
        /// Get the number of simulators in this ModelContainer.
        /// </summary>
        /// <returns></returns>
        public nuint SimulatorCount() => ErsEngine.ERS_ModelContainer_GetSimulatorsCount(coreModelContainerInstance);

        /// <summary>
        /// Get the random seed of this ModelContainer.
        /// </summary>
        /// <returns></returns>
        public nuint GetSeed() => ErsEngine.ERS_ModelContainer_Seed(coreModelContainerInstance);

        /// <summary>
        /// Set the random seed of this ModelContainer.
        /// </summary>
        /// <param name="newSeed">The new seed.</param>
        public void SetSeed(nuint newSeed) => ErsEngine.ERS_ModelContainer_SetSeed(coreModelContainerInstance, newSeed);

        /// <summary>
        /// Generate a random seed for this ModelContainer.
        /// </summary>
        public void GenerateRandomSeed() => ErsEngine.ERS_ModelContainer_GenerateRandomSeed(coreModelContainerInstance);

        /// @brief set an arbitary value as the model precision, this precision will be used in ERS for monitoring & displayed graphics
        public void SetPrecision(SimulationTime precision)
        {
            ErsEngine.ERS_ModelContainer_SetModelPrecision(coreModelContainerInstance, precision);
        }
        public SimulationTime GetPrecision() { return ErsEngine.ERS_ModelContainer_GetModelPrecision(coreModelContainerInstance); }

        /// <summary>
        /// Get the simulation speed over real-time.
        /// </summary>
        /// <remarks>
        /// This function calculates speedup independently when called - it is not automatically
        /// updated by Update(). For meaningful results, call this after multiple Update() iterations
        /// in blocking mode. In non-blocking mode with simple models, the speedup may be 0.0 if the
        /// simulation completes too quickly.
        /// </remarks>
        /// <returns>The speedup factor (simulation time / real time)</returns>
        public double GetSpeedUp() { return ErsEngine.ERS_ModelContainer_SimulationSpeedOverRealtime(coreModelContainerInstance); }
    }
}
