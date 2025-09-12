#pragma once

// Macro to export C++ function in dll
#if defined _WIN32 || defined __CYGWIN__ || defined __linux__
#ifdef __GNUC__
#define ERS_API extern "C" __attribute__((__visibility__("default")))
#else
#define ERS_API extern "C" __declspec(dllexport)
#endif
#endif

// Macro to indicate a parameter is unused, usefull for averting warning as errors in places it is expected
#define UNUSED(x) (void)(x)
#define UNUSEDDECLARE(x) \
    auto* unused = x;    \
    UNUSED(unused);

template <typename T> inline T Max(T a, T b)
{
    return a > b ? a : b;
}

template <typename T> inline T Min(T a, T b)
{
    return a < b ? a : b;
}