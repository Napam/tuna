#ifndef SIMPLE_STATE_H
#define SIMPLE_STATE_H

#include <SDL2/SDL.h>
#include "../include/base_state.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SimpleState : public BaseState, public StateEventListener
{
public:
    std::vector<void *> *entities; // Stores game entities
    
    SimpleState(SDL_Window *window, SDL_Renderer *renderer,
          SDL_Event *event, json &config, float worldWidth = 2000, float worldHeight = -1);
    ~SimpleState();

    /*
    Blits and flips
    */
    void updateGraphics();

    /*
    Calculate logic stuff
    */
    void logic();

    void onKeyDown(SDL_Keycode key) {};
    void onKeyUp(SDL_Keycode key) {};
    void onMouseDown(Uint8 button);
    void onMouseUp(Uint8 button);
    
    /*
    Implements abstract method of BaseState
    */
    virtual void update();
};

#endif