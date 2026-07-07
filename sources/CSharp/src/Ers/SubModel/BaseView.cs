using Ers.Engine;
using System.Runtime.InteropServices;

namespace Ers
{
    [StructLayout(LayoutKind.Sequential)]
    internal ref struct BaseView
    {
        /// <summary>
        /// Native pointer to the core instance.
        /// </summary>
        public readonly IntPtr CorePtr;
        public readonly UInt32[] IncludedTypeIdArray;
        public readonly UInt32[] ExcludedTypeIdArray;

        internal BaseView(IntPtr subModel, UInt32[] includedTypeIdArray_, UInt32[] excludedTypeIdArray_)
        {
            IncludedTypeIdArray = includedTypeIdArray_;
            ExcludedTypeIdArray = excludedTypeIdArray_;
            unsafe
            {
                fixed(UInt32* includedTypePtr = IncludedTypeIdArray) fixed(UInt32* excludedTypePtr = ExcludedTypeIdArray)
                {
                    CorePtr = ErsEngine.ERS_Submodel_View_Create(
                        subModel, (IntPtr)includedTypePtr, (UInt32)IncludedTypeIdArray.Length, (IntPtr)excludedTypePtr,
                        (UInt32)ExcludedTypeIdArray.Length);
                }
            }
        }

        public void Dispose() => ErsEngine.ERS_Submodel_View_Destroy(CorePtr);

        public bool Next() => ErsEngine.ERS_Submodel_View_Next(CorePtr);

        public readonly Entity GetEntity() => ErsEngine.ERS_Submodel_View_GetEntity(CorePtr);

        internal IntPtr GetComponent(int typeIndex) => ErsEngine.ERS_Submodel_View_GetComponent(CorePtr, (nuint)typeIndex);

        public readonly int FindTypeIdx(UInt32 findType)
        {
            for (int i = 0; i < IncludedTypeIdArray.Length; i++)
            {
                UInt32 componentType = IncludedTypeIdArray[i];
                if (componentType == findType)
                {
                    return i;
                }
            }

            // Type not found.
            return -1;
        }

        T GetComponent<T>()
            where T : ScriptBehaviorComponent, new()
        {
            int idx = FindTypeIdx(ComponentTraits<T>.GetComponentTypeId());
            if (idx != -1)
            {
                IntPtr handle = GetComponent(idx);
                return ComponentUtil.GetScriptBehavior<T>(handle);
            }
            throw new ArgumentException($"Type {typeof(T).Name} is not included in this view.");
        }
    }
}
