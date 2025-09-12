#pragma once
#include <cassert>
#include <functional>
#include <type_traits>

namespace Ers
{
    class EventSignalBase
    {
      public:
        struct Connection
        {
            Connection();
            Connection(void* handle);
            Connection(const Connection&) = delete;
            Connection(Connection&&);
            Connection& operator=(const Connection&) = delete;
            Connection& operator=(Connection&&);
            ~Connection();

            void Disconnect();

            void* Handle;
        };

        using ConnectFunction = void* (*)(void* signalHandle, void* callback, void* object);

        EventSignalBase()                                  = delete;
        EventSignalBase(const EventSignalBase&)            = delete;
        EventSignalBase(EventSignalBase&&)                 = delete;
        EventSignalBase& operator=(const EventSignalBase&) = delete;
        EventSignalBase& operator=(EventSignalBase&&)      = delete;
        virtual ~EventSignalBase();

        void Disconnect(Connection& connection);

      protected:
        EventSignalBase(void* coreSignalHandle, ConnectFunction connectFunction_);
        Connection Connect(void* signalFunction, void* object);

      private:
        void* signalHandle;
        ConnectFunction connectFunction;
    };

    template <typename... EventSignatureArgs> class EventSignal : public EventSignalBase
    {
      public:
        EventSignal(void* coreSignalHandle, ConnectFunction connectFunction);
        EventSignal()                              = delete;
        EventSignal(const EventSignal&)            = delete;
        EventSignal(EventSignal&&)                 = delete;
        EventSignal& operator=(const EventSignal&) = delete;
        EventSignal& operator=(EventSignal&&)      = delete;
        virtual ~EventSignal()                     = default;

        /// @brief Connect an event callback without state
        /// @tparam EventSignature
        /// @param callback
        template <void (*callback)(EventSignatureArgs...)> EventSignalBase::Connection Connect();

        /// @brief Connect an event callback on a specific object
        /// @tparam EventSignature
        /// @tparam T
        /// @param callback
        /// @param object
        template <typename T, void (T::*callback)(EventSignatureArgs...)> EventSignalBase::Connection Connect(T* object);
    };
    template <typename... EventSignatureArgs>
    template <void (*callback)(EventSignatureArgs...)>
    inline EventSignalBase::Connection EventSignal<EventSignatureArgs...>::Connect()
    {
        static_assert(callback != nullptr);
        auto function = [](void* object, EventSignatureArgs... args) { callback(args...); };

        return EventSignalBase::Connect(reinterpret_cast<void*>(+function), nullptr);
    }

    template <typename... EventSignatureArgs>
    template <typename T, void (T::*callback)(EventSignatureArgs...)>
    inline EventSignalBase::Connection EventSignal<EventSignatureArgs...>::Connect(T* object)
    {
        static_assert(callback != nullptr);
        auto function = [](void* object, EventSignatureArgs... args) { (static_cast<T*>(object)->*callback)(args...); };

        return EventSignalBase::Connect(reinterpret_cast<void*>(+function), object);
    }

    template <typename... EventSignatureArgs>
    inline EventSignal<EventSignatureArgs...>::EventSignal(void* coreSignalHandle, ConnectFunction connectFunction) :
        EventSignalBase(coreSignalHandle, connectFunction)
    {
    }

} // namespace Ers