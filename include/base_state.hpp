#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <SDL2/SDL.h>

class BaseState
{
protected:
    bool active;

public:
    SDL_Event *event;
    SDL_Keycode keyinput;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 timedelta;

    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    ~BaseState();
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void handle_user_input();
    void activate();
};

#endif