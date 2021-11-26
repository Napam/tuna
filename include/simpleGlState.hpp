#ifndef SIMPLE_GL_STATE_H
#define SIMPLE_GL_STATE_H

#include "tunapch.hpp"
#include "../include/baseState.hpp"

using json = nlohmann::json;

class SimpleGlState : public BaseState, public StateEventListener
{
public:
    std::vector<void *> *entities; // Stores game entities
    
    SimpleGlState(SDL_Window *window, SDL_Renderer *renderer,
          SDL_Event *event, json &config, float worldWidth, float worldHeight);
    ~SimpleGlState();

    /*
    Blits and flips
    */
    void updateGraphics();

    /*
    Calculate logic stuff
    */
    void logic();

    virtual void onKeyDown(SDL_Keycode key) {};
    virtual void onKeyUp(SDL_Keycode key) {};
    virtual void onMouseDown();
    virtual void onMouseUp();
    virtual void onMousewheel(Sint32 horizontal, Sint32 vertical);
    
    /*
    Implements abstract method of BaseState
    */
    virtual void update();
};

#endif