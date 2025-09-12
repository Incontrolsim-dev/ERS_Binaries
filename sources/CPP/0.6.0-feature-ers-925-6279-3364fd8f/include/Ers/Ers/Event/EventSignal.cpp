#include "EventSignal.h"
#include "Ers/Api.h"

#include <cassert>

Ers::EventSignalBase::EventSignalBase(void* coreSignalHandle, ConnectFunction connectFunction_) :
    signalHandle(coreSignalHandle),
    connectFunction(connectFunction_)
{
}

Ers::EventSignalBase::~EventSignalBase()
{
    // No cleanup needed
}

void Ers::EventSignalBase::Disconnect(Connection& connection)
{
    connection.Disconnect();
}

Ers::EventSignalBase::Connection Ers::EventSignalBase::Connect(void* signalFunction, void* object)
{
    void* handle = connectFunction(signalHandle, signalFunction, object);
    return Connection(handle);
}

Ers::EventSignalBase::Connection::Connection() :
    Handle(nullptr)
{
}

Ers::EventSignalBase::Connection::Connection(void* handle) :
    Handle(handle)
{
}

Ers::EventSignalBase::Connection::Connection(Connection&& other) :
    Handle(other.Handle)
{
    other.Handle = nullptr;
}

Ers::EventSignalBase::Connection& Ers::EventSignalBase::Connection::operator=(Connection&& other)
{
    Handle       = other.Handle;
    other.Handle = nullptr;

    return *this;
}

Ers::EventSignalBase::Connection::~Connection()
{
    if (Handle == nullptr)
        return;

    Disconnect();
}

void Ers::EventSignalBase::Connection::Disconnect()
{
    assert(Handle != nullptr);
    ersAPIFunctionPointers.ERS_SubModel_Events_Disconnect(Handle);
}
