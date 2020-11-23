#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include <SDL2/SDL.h>
#include "../include/base_state.hpp"
#include <vector>

class Boids : public BaseState
{
public:
    std::vector<void*> *entities;
    Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    ~Boids();
    void update_graphics();
    void logic();
    void interact_user();
    int run();
};

#endif