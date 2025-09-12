
#include "APILocalEvent.h"

#include <stdlib.h>
#include <string.h>
#include <vector>

#define DEFAULT_MEMPOOL_SIZE 16
namespace Ers
{
    void LocalEventCallback(void* dataPtr)
    {
        auto* event = static_cast<APILocalEvent*>(dataPtr);
        event->Callback();
        delete event;
    }

    APILocalEvent::APILocalEvent(std::function<void()>&& callback) :
        Callback(std::move(callback))
    {
    }
} // namespace Ers