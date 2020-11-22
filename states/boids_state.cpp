#include <iostream>
#include <SDL2/SDL.h>
#include "../include/boids_state.hpp"
// #include "../include/base_state.hpp"

Boids::Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : BaseState(window, renderer, event)
{
    i = 0;
    rect = {100, 100, 10, 10};
    speed = 6;
};

void Boids::update_graphics()
{
    // Fill sceen with black
    clearfill(0, 0, 0, 255);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Switch
    SDL_RenderPresent(renderer);
    SDL_Delay(30);
}

void Boids::logic()
{
}

void Boids::interact_user()
{
    std::cout << keyinput << "\n";
    switch (keyinput)
    {
    case SDLK_LEFT:
        rect.x -= speed;
        break;
    case SDLK_RIGHT:
        rect.x += speed;
        break;
    case SDLK_UP:
        rect.y -= speed;
        break;
    case SDLK_DOWN:
        rect.y += speed;
        break;
    case SDLK_a:
        rect.x -= speed;
        break;
    case SDLK_d:
        rect.x += speed;
        break;
    case SDLK_w:
        rect.y -= speed;
        break;
    case SDLK_s:
        rect.y += speed;
        break;
    }
}

int Boids::run()
{
    activate();
    while (active)
    {
        handle_user_input();
        interact_user();
        logic();
        update_graphics();
    }

    return 0;
}
