#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <SDL2/SDL.h>
#include <vector>

/* 
Listener is good for handling utf8 input, dont use for charactermovment etc.
Use for handling single key stroke stuff or something
*/
class StateEventListener
{
public:
    virtual ~StateEventListener() {};
    virtual void onKeyDown(SDL_Keycode key) = 0;
    virtual void onKeyUp(SDL_Keycode key) = 0;
};

class BaseState
{
protected:
    std::vector<StateEventListener *> *inputEventListeners;

public:
    bool active;
    bool eventHappened;
    SDL_Event *event;
    SDL_Keycode keydown;
    SDL_Keycode keyup;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 timedelta;
    const Uint8 *keystates;

    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    ~BaseState();
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void handleUserInput();
    void activate();
    void addInputEventListener(StateEventListener *listener);
    void run();
    virtual void update() = 0;
};

#endif