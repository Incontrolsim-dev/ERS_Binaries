#pragma once
#include <typeinfo>

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

        // Optional: Override this method to enable serialization support
        void Serialization(Ers::Serializer& serializer) {
            // Serialize your event data here
            // serializer.Serialize("field_name", FieldName);
        }
        */
        ISyncEvent()                  = default;
        ISyncEvent(const ISyncEvent&) = delete;
        ISyncEvent(ISyncEvent&&)      = delete;

        static void OnSenderSidePlain();

        static void OnTargetSidePlain();

      protected:
        using Data = Derived;
    };

    class SyncEvent
    {

      public:
        /// @brief Get data from a specific sync event
        /// Data is automatically allocated when the sync event is scheduled.
        /// @tparam T The data type
        /// @param syncEvent Pointer to the sync event
        /// @return Reference to the data
        template <typename T> static T& GetData(void* syncEvent) { return *static_cast<T*>(Ers::Engine::ERS_SyncEvent_GetData(syncEvent)); }

        /// @brief Get data from the current sync event (for use in callbacks)
        /// @tparam T The data type
        /// @return Reference to the data
        template <typename T> static T& GetData()
        {
            return *static_cast<T*>(Ers::Engine::ERS_SyncEvent_GetData(Ers::Engine::ERS_ThreadLocal_GetCurrentSyncEvent()));
        }

        template <typename T> constexpr static uint64_t TypeIdentifier()
        {
            // Enforce these rules to mostly ensure that the data is simple, and doesn't mind being moved and not explicitly destructed
            static_assert(std::is_trivially_destructible_v<T>, "T must be trivially destructible");
            static_assert(std::is_standard_layout_v<T>, "T must have standard layout");

            return reinterpret_cast<uint64_t>(&typeid(T));
        }

        /// @brief Check if the current simulator is in a sync event
        /// @return
        static bool IsInsideSyncEvent() { return Ers::Engine::ERS_ThreadLocal_IsInsideSyncEvent(); }

        /// @brief Get the target's simulator id of the current sync event
        /// @return
        static int32_t GetSyncEventTarget() { return Ers::Engine::ERS_ThreadLocal_GetSyncEventTarget(); }

        /// @brief Get the sender's simulator id of the current sync event
        /// @return
        static int32_t GetSyncEventSender() { return Ers::Engine::ERS_ThreadLocal_GetSyncEventSender(); }
    };
} // namespace Ers
