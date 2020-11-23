#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "../include/boids_state.hpp"

class Squareboy
{
public:
    SDL_Rect rect;
    Boids *boids;
    Squareboy(Boids *boids, int x, int y, int w, int h);
    void interact_user();
    void interact_state();
    void logic();
    void update();
    void blit();
};

Squareboy::Squareboy(Boids *boids, int x, int y, int w, int h)
{
    rect = {x, y, w, h};
    this->boids = boids;
}

void Squareboy::blit()
{
    SDL_SetRenderDrawColor(boids->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(boids->renderer, &rect);
}

void Squareboy::interact_user()
{
    switch (boids->keyinput)
    {
    case SDLK_a:
        rect.x -= 1;
        break;
    case SDLK_d:
        rect.x += 1;
        break;
    case SDLK_w:
        rect.y -= 1;
        break;
    case SDLK_s:
        rect.y += 1;
        break;
    default:
        break;
    }
}

void Squareboy::interact_state()
{
}

void Squareboy::update()
{
    interact_user();
    interact_state();
}

// -------------------------------------------------------------------------- //
Boids::Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : BaseState(window, renderer, event)
{
    entities = new std::vector<void *>;

    for (int i=0; i < 7; i++)
    {
        for (int j=0; j < 7; j++)
        {
            entities->emplace_back(new Squareboy(this, 100+i*25, 100+j*25, 20, 20));
        }
    }
};

Boids::~Boids()
{
    for (void *ent : *entities)
    {
        delete (Squareboy *)ent;
    }
    delete entities;
}

void Boids::update_graphics()
{
    // Fill sceen with black
    clearfill(0, 0, 0, 255);

    for (void *ent : *entities)
    {
        ((Squareboy *)ent)->blit();
    }

    // Flip
    SDL_RenderPresent(renderer);
}

void Boids::logic()
{
    for (void *ent : *entities)
    {
        ((Squareboy *)ent)->update();
    }
}

void Boids::interact_user() {}

int Boids::run()
{
    Uint32 time, timedelta;
    activate();

    float target_fps = 60;
    float target_frametime = 1000 / target_fps; // ms
    timedelta = target_frametime;
    while (active)
    {
        time = SDL_GetTicks();
        handle_user_input();
        interact_user();
        logic();
        update_graphics();
        timedelta = SDL_GetTicks() - time;

        if (timedelta < target_frametime)
        {
            SDL_Delay(target_frametime - timedelta);
        }

        // std::cout << SDL_GetTicks() - time << std::endl;
    }

    return 0;
}
