#ifndef UTILS_H 
#define UTILS_H

#include "tunapch.hpp"

/*
Assigns pointers inplace
*/
void CreateWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer, SDL_GLContext **context,
                             int width, int height);

/*
Python style modulo

e.g. -10 mod 30 = 20
*/
inline int pymod(int x, int m)
{
    return (x % m + m) % m;
}

#endif