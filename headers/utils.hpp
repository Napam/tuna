#ifndef UTILS_H 
#define UTILS_H

#include <iostream>
#include <tuple>
#include <SDL2/SDL.h>

std::tuple<SDL_Window*, SDL_Renderer*> GetSDLobjects();

#endif