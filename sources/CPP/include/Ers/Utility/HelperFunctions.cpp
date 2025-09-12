#include "HelperFunctions.h"
#include <cstring>
#include <stdexcept>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>
#elif defined(PLATFORM_POSIX) || defined(__linux__)
#include <limits.h>
#include <string>
#include <unistd.h>
#endif

std::string executable_name()
{
#if defined(PLATFORM_POSIX) || defined(__linux__) // check defines for your setup

    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        return std::string(buffer);
    }
    else
    {
        return ""; // Handle error appropriately in real use
    }

#elif defined(_WIN32)

    char buf[MAX_PATH];
    GetModuleFileNameA(nullptr, buf, MAX_PATH);
    return {buf};

#else

    static_assert(false, "unrecognized platform");

#endif
}

/// @brief Copies the given string into the given string buffer. Assuming the given buffer is big enough,
/// the string data is copied into the first N bytes of the buffer including the null termnator.
/// If the original string does not end with null terminator, it will be added to the copy.
/// @param stringToCopy The given string to copy.
/// @param stringBuffer The pointer to a string buffer to copy to.
/// @param bufferSize The size of the string buffer.
/// @throws Runtime error, if the pointer to the string buffer is null or
/// if the given size of the buffer is smaller than the size of the string including the null terminator.
void CopyString(const std::string& stringToCopy, char* stringBuffer, const std::size_t& bufferSize)
{
    // Make sure the buffer pointer is valid.
    if (stringBuffer == nullptr)
    {
        throw std::runtime_error("Invalid pointer to the string buffer to copy.");
    }

    auto strSize = stringToCopy.size();

    // If the string is not null terminated, reserve space for adding it.
    if (stringToCopy.empty() || stringToCopy.back() != '\0')
    {
        strSize = strSize + 1;
    }

    // Make sure the buffer to copy the string is big enough.
    if (bufferSize < strSize)
    {
        throw std::runtime_error("The buffer size is too small to store a null terminated copy of the given string.");
    }

    // Copy the string into the string buffer.
    std::strncpy(stringBuffer, stringToCopy.data(), strSize);

    // Make sure the copied string has null terminator as it's last character.
    if (stringBuffer[strSize - 1] != '\0')
    {
        stringBuffer[strSize - 1] = '\0';
    }
}

char* CopyString(const std::string_view& str)
{
    auto* returnString = static_cast<char*>(malloc(str.size() + 1));
    if (returnString == nullptr)
    {
        std::abort(); // Out of memory
    }

    std::strncpy(returnString, str.data(), str.size() + 1);
    return returnString;
}
