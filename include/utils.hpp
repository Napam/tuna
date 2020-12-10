#ifndef UTILS_H 
#define UTILS_H

#include <iostream>
#include <SDL2/SDL.h>

void CreateWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer);

/*
Python style modulo

e.g. -10 mod 30 = 20
*/
inline int pymod(int x, int m)
{
    return (x % m + m) % m;
}

#endif