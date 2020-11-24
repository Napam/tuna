#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <SDL2/SDL.h>
#include <vector>

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

    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    ~BaseState();
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void handle_user_input();
    void activate();
    void addInputEventListener(StateEventListener *listener);
};

#endif