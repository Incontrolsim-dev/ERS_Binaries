using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
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
        public SimulationTime CurrentTime { get => ErsEngine.ERS_ModelContainer_CurrentTime(CorePtr); }

        // clang-format on

        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public IntPtr CorePtr = IntPtr.Zero;

        internal ModelContainer(IntPtr corePtr)
        {
            this.CorePtr = corePtr;
            ErsEngine.ERS_ModelContainer_Increase(corePtr);
        }

        /// <summary>
        /// Finalizer.
        /// </summary>
        ~ModelContainer() { ErsEngine.ERS_ModelContainer_Release(CorePtr); }

        /// <summary>
        /// Create a new ModelContainer.
        /// </summary>
        /// <returns></returns>
        public static ModelContainer Create()
        {
            IntPtr ptr            = ErsEngine.ERS_ModelContainer_Create();
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

                    IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_AddSimulator(CorePtr, tagByte, (byte)type);
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
            ErsEngine.ERS_ModelContainer_RemoveSimulator(CorePtr, simulator.CorePtr);
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
                    IntPtr foundCoreSimulator = ErsEngine.ERS_ModelContainer_FindSimulatorByTag(CorePtr, tagByte);
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
            IntPtr foundCoreSimulator = ErsEngine.ERS_ModelContainer_FindSimulatorById(CorePtr, simulatorId);
            return new Simulator(foundCoreSimulator);
        }

        /// <summary>
        /// Whether the ModelContainer is started.
        ///
        /// <para>
        /// A ModelContainer must be started before updates can be performed.
        /// After it has started, simulators can no longer be added or removed.
        /// </para>
        /// </summary>
        /// <returns></returns>
        public bool IsStarted
        {
            get => ErsEngine.ERS_ModelContainer_IsStarted(CorePtr);
        }

        /// <summary>
        /// Start the ModelContainer. See <see cref="IsStarted"/> for more details.
        /// </summary>
        public void Start() => ErsEngine.ERS_ModelContainer_Start(CorePtr);

        /// <summary>
        /// Perform an update step on the ModelContainer, updating all of its simulators.
        /// </summary>
        /// <param name="timeStep">The size of the step to perform.</param>
        public void Update(SimulationTime timeStep) => ErsEngine.ERS_ModelContainer_Update_Blocking(CorePtr, timeStep);

        /// <summary>
        /// Add a dependency from one simulator to another, so from simulator A can be schedule to simulator B.
        /// </summary>
        /// <param name="from">The simulator from which events will be scheduled (Simulator A).</param>
        /// <param name="to">The simulator to which events will be scheduled (Simulator B).</param>
        public void AddSimulatorDependency(Simulator from, Simulator to)
        {
            Debug.Assert(from.Valid());
            Debug.Assert(to.Valid());
            ErsEngine.ERS_ModelContainer_AddSimulatorDependency(CorePtr, from.CorePtr, to.CorePtr);
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
            ErsEngine.ERS_ModelContainer_RemoveSimulatorDependency(CorePtr, from.CorePtr, to.CorePtr);
        }

        /// <summary>
        /// Get all simulators in the ModelContainer.
        /// </summary>
        /// <returns></returns>
        public Simulator[] GetSimulators()
        {
            Simulator[] simulators = new Simulator[SimulatorCount];
            for (int i = 0; i < simulators.Length; i++)
            {
                IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_GetSimulator(CorePtr, i);
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
            IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_GetSimulatorById(CorePtr, simulatorId);
            return new Simulator(coreSimulator);
        }

        /// <summary>
        /// Get a simulator in the ModelContainer by its index.
        /// </summary>
        /// <param name="index">The index of the simulator.</param>
        /// <returns></returns>
        public Simulator GetSimulatorByIndex(int index)
        {
            IntPtr coreSimulator = ErsEngine.ERS_ModelContainer_GetSimulator(CorePtr, index);
            return new Simulator(coreSimulator);
        }

        /// <summary>
        /// Get the number of simulators in this ModelContainer.
        /// </summary>
        /// <returns></returns>
        public nuint SimulatorCount
        {
            get => ErsEngine.ERS_ModelContainer_GetSimulatorsCount(CorePtr);
        }

        /// <summary>
        /// The random seed of this model container.
        /// </summary>
        public nuint Seed
        {
            get => ErsEngine.ERS_ModelContainer_Seed(CorePtr);
            set => ErsEngine.ERS_ModelContainer_SetSeed(CorePtr, value);
        }

        /// <summary>
        /// Generate a random seed for this ModelContainer.
        /// </summary>
        public void GenerateRandomSeed() => ErsEngine.ERS_ModelContainer_GenerateRandomSeed(CorePtr);

        /// <summary>
        /// The precision used for this model.
        ///
        /// <para>This is an arbitrary value that is used to imitate decimal values for the simulation time.</para>
        /// </summary>
        public SimulationTime Precision
        {
            get => ErsEngine.ERS_ModelContainer_GetModelPrecision(CorePtr);
            set => ErsEngine.ERS_ModelContainer_SetModelPrecision(CorePtr, value);
        }

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
        public double GetSpeedUp() { return ErsEngine.ERS_ModelContainer_SimulationSpeedOverRealtime(CorePtr); }

        /// <summary>
        /// The working directory for this model container.
        ///
        /// <para>The working directory is used to store the scripts and assets related to the model container.</para>
        /// </summary>
        public string WorkingDir
        {
            get {
                IntPtr ptr     = ErsEngine.ERS_ModelContainer_GetWorkingDir(CorePtr);
                string? result = Marshal.PtrToStringAnsi(ptr);
                Debug.Assert(result != null);
                return result;
            }
            set {
                unsafe
                {
                    var utf8 = value.ToUtf8NullTerminated();
                    fixed(byte* path = utf8)
                    {
                        ErsEngine.ERS_ModelContainer_SetWorkingDir(CorePtr, path);
                    }
                }
            }
        }
    }
}
