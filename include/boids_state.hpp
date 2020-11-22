#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include <SDL2/SDL.h>
#include "../include/base_state.hpp"
#include "../include/boids_state.hpp"

class Boids : BaseState
{
private:
    SDL_Rect rect;

public:
    int speed;
    Uint16 i;

    Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    void update_graphics();
    void logic();
    void interact_user();
    int run();
};

#endif