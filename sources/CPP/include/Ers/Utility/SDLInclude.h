#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// Required for Linux, X11 defines these macros, which conflict with our code and our dependencies' code
#undef Bool
#undef None
#undef CurrentTime
#undef Status
#undef Always
#undef Success
#undef Font
