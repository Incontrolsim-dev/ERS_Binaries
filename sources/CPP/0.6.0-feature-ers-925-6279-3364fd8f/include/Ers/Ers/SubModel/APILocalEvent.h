#pragma once

#include <functional>

namespace Ers
{
    struct APILocalEvent
    {
        APILocalEvent() = delete;
        APILocalEvent(std::function<void()>&& callback);
        APILocalEvent(const APILocalEvent&) = delete;
        APILocalEvent(APILocalEvent&&)      = delete;
        APILocalEvent& operator=(const APILocalEvent&) = delete;
        APILocalEvent& operator=(APILocalEvent&&)      = delete;


        std::function<void()> Callback;
    };

    void LocalEventCallback(void* dataPtr);

} // namespace Ers