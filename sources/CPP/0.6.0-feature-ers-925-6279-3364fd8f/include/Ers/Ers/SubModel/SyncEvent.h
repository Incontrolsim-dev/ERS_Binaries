#pragma once
#include "Ers/Api.h"

namespace Ers
{

    // Base class with compile-time check and static_assert guidance
    template <typename Derived> struct ISyncEvent
    {
        // This class must implement the following:

        /*
        static const char* GetName() {
            return "YourEventName";
        }

        void OnSenderSide() {
            Data& data = Ers::SyncEvent::GetData<Data>();
            return data;
        }

        void OnTargetSide() {
            Data& data = Ers::SyncEvent::GetData<Data>();
            return data;
        }
        */
        ISyncEvent()                  = delete;
        ISyncEvent(const ISyncEvent&) = delete;
        ISyncEvent(ISyncEvent&&)      = delete;

        static void OnSenderSidePlain();

        static void OnTargetSidePlain();

      protected:
        using Data = Derived;
    };

    // Optional extension: ensures OnSenderSide/OnTargetSide redirect to a shared OnSyncEvent
    template <typename Derived> struct ISyncEventCombined : ISyncEvent<Derived>
    {
        // This class must implement the following:

        /*
        static const char* GetName() {
            return "YourEventName";
        }

        void OnSyncEvent() {
            Data& data = Ers::SyncEvent::GetData<Data>();
            return data;
        }
        */

        void OnSenderSide() { Derived::OnSyncEvent(); }

        void OnTargetSide() { Derived::OnSyncEvent(); }
    };

    class SyncEvent
    {

      public:
        // Engine Internal
        template <typename T> static T& GetData(void* syncEvent)
        {
            auto globalidx = ersAPIFunctionPointers.ERS_SyncEvent_GetOrRegisterDataContext(syncEvent, TypeIdentifier<T>(), sizeof(T));
            return *static_cast<T*>(ersAPIFunctionPointers.ERS_SyncEvent_GetData(syncEvent, globalidx));
        }

        // Engine Internal
        template <typename T> static T& GetData() { return GetData<T>(ersAPIFunctionPointers.ERS_ThreadLocal_GetCurrentSyncEvent()); }

        template <typename T> constexpr static uint64_t TypeIdentifier()
        {
            // Enforce these rules to mostly ensure that the data is simple, and doesn't mind being moved and not explicitly destructed
            static_assert(std::is_trivially_destructible_v<T>, "T must be trivially destructible");
            static_assert(std::is_standard_layout_v<T>, "T must have standard layout");

            return reinterpret_cast<uint64_t>(&typeid(T));
        }

        /// @brief Check if the current simulator is in a sync event
        /// @return
        static bool IsInsideSyncEvent() { return ersAPIFunctionPointers.ERS_ThreadLocal_IsInsideSyncEvent(); }

        /// @brief Check if the current simulator is currently executing the senderside of a sync event
        /// @return
        static bool IsSyncEventInSenderSide() { return ersAPIFunctionPointers.ERS_ThreadLocal_IsSyncEventInSenderSide(); }

        /// @brief Get the target's simulator id of the current sync event
        /// @return
        static int32_t GetSyncEventTarget() { return ersAPIFunctionPointers.ERS_ThreadLocal_GetSyncEventTarget(); }

        /// @brief Get the sender's simulator id of the current sync event
        /// @return
        static int32_t GetSyncEventSender() { return ersAPIFunctionPointers.ERS_ThreadLocal_GetSyncEventSender(); }
    };
} // namespace Ers