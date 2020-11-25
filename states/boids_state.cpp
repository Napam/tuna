#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "../include/base_state.hpp"
#include "../include/boids_state.hpp"
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Squareboy : public StateEventListener
{
public:
    SDL_Rect rect;
    Boids *boids;
    Array2i position;
    Array2i velocity;
    Squareboy(Boids *boids, int x, int y, int w, int h);
    void interactUser();
    void behave();
    void update();
    void blit();
    void motion();
    void setPosition(int x, int y);
    virtual void onKeyDown(SDL_Keycode key);
    virtual void onKeyUp(SDL_Keycode key);
};

Squareboy::Squareboy(Boids *boids, int x, int y, int w, int h)
    : boids(boids), position(x, y), velocity(0, 0)
{
    rect = {position[0] - w / 2, position[1] - h / 2, w, h};
    // boids->addInputEventListener(this);
}

void Squareboy::onKeyDown(SDL_Keycode key)
{
}

void Squareboy::onKeyUp(SDL_Keycode key)
{
}

void Squareboy::blit()
{
    SDL_SetRenderDrawColor(boids->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(boids->renderer, &rect);
}

void Squareboy::interactUser()
{
    const Uint8 *keys = boids->keystates;
    
    if (keys[SDL_SCANCODE_A]) 
    {
        velocity[0] -= 1;
    }
    
    if (keys[SDL_SCANCODE_D]) 
    {
        velocity[0] += 1;
    }
    
    if (keys[SDL_SCANCODE_W]) 
    {
        velocity[1] -= 1;
    }
    
    if (keys[SDL_SCANCODE_S]) 
    {
        velocity[1] += 1;
    }
    
    if (keys[SDL_SCANCODE_SPACE]) 
    {
        velocity = 0;
    }
}

void Squareboy::behave()
{
    int w, h;
    SDL_GetWindowSize(boids->window, &w, &h);

    if (position[0] + rect.w / 2 > w)
    {
        position[0] = rect.w / 2;
    }
    else if (position[0] - rect.w / 2 < 0)
    {
        position[0] = w - rect.w / 2;
    }
    else if (position[1] + rect.h / 2 > h)
    {
        position[1] = rect.h / 2;
    }
    else if (position[1] - rect.h / 2 < 0)
    {
        position[1] = h - rect.h / 2;
    }
}

void Squareboy::motion()
{
    velocity = velocity.min(2).max(-2);
    position = position + velocity;
    rect.x = position[0] - rect.w / 2;
    rect.y = position[1] - rect.h / 2;
}

void Squareboy::update()
{
    interactUser();
    behave();
    motion();
}

// ############################################################################################# //
// ############################################################################################# //
// ############################################################################################# //
// ############################################################################################# //
// ############################################################################################# //
// ############################################################################################# //

Boids::Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : BaseState(window, renderer, event)
{
    entities = new std::vector<void *>;

    // Grid of squarebois
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            entities->emplace_back(new Squareboy(this, 100 + i * 25, 100 + j * 25, 20, 20));
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

void Boids::updateGraphics()
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

void Boids::interactUser()
{
}

/*
What to do in one iteration in game loop, will be called by BaseState::run, no need to 
manually write game loop here
*/
void Boids::update()
{   
    interactUser();
    logic();
    updateGraphics();
}
