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
    void updateGraphics();
    void logic();
    void interactUser();
    virtual void update();
};

#endif