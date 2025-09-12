using System.Diagnostics;
using System.Runtime.InteropServices;
using Ers.Engine;

namespace Ers
{
    /// <summary>
    /// Class overseeing simulation models (<see cref="ModelContainer"/>.
    /// It will manage and update the active collection of ModelContainers.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public ref struct ModelManager
    {
        private readonly IntPtr Data;

        /// <summary>
        /// Construct a new ModelManager.
        ///
        /// <para>Use <see cref="GetModelManager"/> instead of this constructor.</para>
        /// </summary>
        public ModelManager() { Data = ErsEngine.ERS_ModelManager_GetModelManager(); }

        /// <summary>
        /// Get the ModelManager singleton.
        /// </summary>
        /// <returns></returns>
        public static ModelManager GetModelManager() { return new ModelManager(); }

        /// <summary>
        /// Add a <see cref="ModelContainer"/> to the manager.
        /// </summary>
        /// <param name="modelContainer">The ModelContainer to add.</param>
        /// <param name="endTime">The end time for the ModelContainer.</param>
        public void AddModelContainer(in ModelContainer modelContainer, SimulationTime endTime)
        {
            Debug.Assert(!HasModelContainer(modelContainer));
            ErsEngine.ERS_ModelManager_AddModelContainer(Data, modelContainer.Data, endTime);
        }

        /// <summary>
        /// Remove a ModelContainer from the manager.
        /// </summary>
        /// <param name="modelContainer"></param>
        /// <exception cref="Exception">When the given ModelContainer is not in the manager.</exception>
        public void RemoveModelContainer(in ModelContainer modelContainer)
        {
            if (!HasModelContainer(modelContainer))
            {
                throw new Exception("ModelContainer is not inside this ModelContainer");
            }

            ErsEngine.ERS_ModelManager_RemoveModelContainer(Data, modelContainer.Data);
        }

        /// <summary>
        /// Check whether a given ModelContainer is in the manager.
        /// </summary>
        /// <param name="modelContainer">The ModelContainer to check for.</param>
        /// <returns>True if the ModelContainer exists in the manager, false if not.</returns>
        public bool HasModelContainer(in ModelContainer modelContainer)
        {
            return ErsEngine.ERS_ModelManager_HasModelContainer(Data, modelContainer.Data);
        }

        /// <summary>
        /// Get the model container at the given index.
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public ModelContainer GetModelContainerAt(nuint index)
        {
            IntPtr coreModelContainerPtr = ErsEngine.ERS_ModelManager_GetModelContainerAt(Data, index);
            return new ModelContainer(coreModelContainerPtr);
        }

        /// <summary>
        /// Get the number of ModelContainers in the manager.
        /// </summary>
        /// <returns></returns>
        public ulong CountModelContainers() => ErsEngine.ERS_ModelManager_CountModelContainers(Data);

        /// <summary>
        /// Update the manager, updating all ModelContainers inside it.
        /// </summary>
        public void Update() => ErsEngine.ERS_ModelManager_Update(Data);

        /// <summary>
        /// Run all models that are currently in the ModelManager until completion and print a combined progress bar while running.
        /// </summary>
        public void RunWithProgressBar() => ErsEngine.ERS_RunWithProgressBar();
    }
}
