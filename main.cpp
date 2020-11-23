#include <iostream>
#include <tuple>
#include <SDL2/SDL.h>
#include "include/utils.hpp"
#include "include/base_state.hpp"
#include "include/boids_state.hpp"

int main(int argc, char **argv)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    CreateWindowAndRenderer(&window, &renderer);

    Boids *boids = new Boids(window, renderer, &event);
    boids->run();

    delete boids;

    /* Free all objects*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit program */
    SDL_Quit();
    return 0;
}