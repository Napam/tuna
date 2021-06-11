#ifndef BOIDS_STATE_H
#define BOIDS_STATE_H

#include <SDL2/SDL.h>
#include "../include/base_state.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Boids : public BaseState
{
public:
    std::vector<void *> *entities; // Stores game entities
    std::vector<void *> *texts; // Stores text stuff
    Boids(SDL_Window *window, SDL_Renderer *renderer,
          SDL_Event *event, json &config, float worldWidth = 2000, float worldHeight = -1);
    ~Boids();

    /*
    Blits and flips
    */
    void updateGraphics();

    /*
    Calculate logic stuff
    */
    void logic();

    /*
    State interaction with user
    */
    void interactUser();
    
    /*
    Implements abstract method of BaseState
    */
    virtual void update();
};

#endif