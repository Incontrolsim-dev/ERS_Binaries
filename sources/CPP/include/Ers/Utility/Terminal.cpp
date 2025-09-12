#include "Terminal.h"

#include <iostream>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#define NOMINMAX
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux

void Ers::GetTerminalSize(int& width, int& height)
{
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width  = (csbi.srWindow.Right - csbi.srWindow.Left + 1);
    height = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#elif defined(__linux__)
    // clang-format off
      struct winsize w;
      ioctl(fileno(stdout), TIOCGWINSZ, &w);
      width  = (int)(w.ws_col);
      height = (int)(w.ws_row);
    // clang-format on
#endif // Windows/Linux
}