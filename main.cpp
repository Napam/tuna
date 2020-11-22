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
    SDL_Surface *surface;
    SDL_Event *event;
    bool active;

public:
    BaseState(SDL_Window* window, SDL_Surface* surface, SDL_Renderer* renderer);

    /*
     * Lol
     */
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void handle_user_input();
};

BaseState::BaseState(SDL_Window *window, SDL_Surface *surface, SDL_Renderer *renderer)
{
    this->window = window;
    this->surface = surface;
    this->renderer = renderer;
    active = false;
}

void BaseState::clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Fill sceen with black
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
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

class Boids : BaseState
{
public:
    Boids(SDL_Window *window, SDL_Surface *surface, SDL_Renderer *renderer)
        : BaseState(window, surface, renderer)
    {
        
    }

    int run()
    {
        std::cout << "Debug1\n";
        SDL_UpdateWindowSurface(window);
        std::cout << "Debug2\n";

        SDL_Event e;

        int i = 0;
        active = true;
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
    SDL_Surface *surface;
    SDL_Renderer *renderer;

    std::tie(window, surface, renderer) = GetSDLobjects();

    Boids boids(window, surface, renderer);
    boids.run();

    /* Free all objects*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit program */
    SDL_Quit();
    return 0;
}