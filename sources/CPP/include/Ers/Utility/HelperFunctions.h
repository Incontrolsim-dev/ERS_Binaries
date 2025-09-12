#pragma once

#include <string>

std::string executable_name();

/// @brief Utility function to copy a string to return raw char* for CStyleReturns
/// @param str String to copy
/// @return raw ptr to copied null terminated string
char* CopyString(const std::string_view& str);

void CopyString(const std::string& stringToCopy, char* stringBuffer, const std::size_t& bufferSize);
