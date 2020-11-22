#include <iostream>
#include <tuple>
#include <SDL2/SDL.h>
#include "headers/utils.hpp"
// #include "headers/base_state.hpp"

class BaseState
{
protected:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event *event;
    bool active;

public:
    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    ~BaseState();
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void handle_user_input();
};

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
{
    this->window = window;
    this->renderer = renderer;
    this->event = event;
    active = false;
}

BaseState::~BaseState()
{
    delete event;
}

void BaseState::handle_user_input()
{
    while (SDL_PollEvent(event) > 0)
    {
        switch (event->type)
        {
        case SDL_QUIT:
            active = false;
        case SDLK_F4:
            active = false;
        }
    }
}

void BaseState::clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Fill sceen with black
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

class Boids : BaseState
{
public:
    Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
        : BaseState(window, renderer, event) {};

    int run()
    {
        active = true;

        int i = 0;
        while (active)
        {
            handle_user_input();
            // Create a square
            // create a black square
            SDL_Rect rect = {i, i, 10 + i, 10 + i}; // x, y, width, height

            // Fill sceen with black
            clearfill(0, 0, 0, 255);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
            i++;
        }

        return 0;
    }
};

int main(int argc, char **argv)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    std::tie(window, renderer) = GetSDLobjects();

    Boids boids(window, renderer, &event);
    boids.run();

    /* Free all objects*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit program */
    SDL_Quit();
    return 0;
}