#include <iostream>
#include <SDL2/SDL.h>
#include "include/fonts.hpp"
#include "include/utils.hpp"
#include "include/base_state.hpp"

class MockState 
    : public BaseState
{
public:
    MockState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    TTFText *text;
    virtual void update();
};

MockState::MockState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : BaseState(window, renderer, event) {
        text = new TTFText(renderer, "Lato-Regular.ttf", 128, {255,255,255}, 0, 0, 200, 100);
        text->setText("Hello, World!");
    }

void MockState::update() 
{
    clearfill(0,0,0,255);
    text->blit();
    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    CreateWindowAndRenderer(&window, &renderer);

    MockState state(window, renderer, &event);
    state.run();

    return 0;
}