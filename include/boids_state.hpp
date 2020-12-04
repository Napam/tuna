#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include <SDL2/SDL.h>
#include "../include/base_state.hpp"
#include <vector>

class Boids : public BaseState
{
public:
    std::vector<void *> *entities;
    float worldWidth, worldHeight;
    Boids(SDL_Window *window, SDL_Renderer *renderer,
          SDL_Event *event, float worldWidth = 1000, float worldHeight = -1);
    ~Boids();
    void updateGraphics();
    void logic();
    void interactUser();
    int worldToPixel(float x, float y);
    virtual void update();
};

#endif