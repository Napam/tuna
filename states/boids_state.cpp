#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include "../include/base_state.hpp"
#include "../include/boids_state.hpp"
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Squareboy : public BaseWorldObject<Boids>
{
public:
    Array2f velocity;
    Squareboy(Boids *state, float x, float y, int w, int h);
    void interactUser();
    void behave();
    void blit();
    void motion();
    virtual void update();
};

Squareboy::Squareboy(Boids *state, float x, float y, int w, int h)
    : BaseWorldObject(state, x, y, w, h), velocity(0.0, 0.0)
{
}

void Squareboy::blit()
{
    drawRect();
}

void Squareboy::interactUser()
{
    const Uint8 *keys = state->keystates;

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
    if (state->pixelSize[0] < pixelPosition[0])
    {
        updatePixelPositionX(0);
    }
    else if (pixelPosition[0] < 0)
    {
        updatePixelPositionX(state->pixelSize[0]);
    }
    else if (state->pixelSize[1] < pixelPosition[1])
    {
        updatePixelPositionY(0);
    }
    else if (pixelPosition[1] < 0)
    {
        updatePixelPositionY(state->pixelSize[1]);
    }
}

void Squareboy::motion()
{
    velocity -= velocity * 0.05 * state->worldDt;
    worldPosition = worldPosition + velocity * state->worldDt;
    updateWorldPosition();
}

void Squareboy::update()
{
    interactUser();
    behave();
    motion();
}

// ############################################################################################# //

Boids::Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event,
             float worldWidth, float worldHeight)
    : BaseState(window, renderer, event)
{
    float unitPerPixel;

    entities = new std::vector<void *>;

    if ((worldHeight == -1) && (worldWidth == -1))
    {
        throw std::invalid_argument(
            "worldHeight and worldWidth cannot both be -1 stoopid");
    }

    if (worldHeight == -1)
    {
        unitPerPixel = worldWidth / pixelSize[0];
        worldHeight = unitPerPixel * pixelSize[1];
    }
    else if (worldWidth == -1)
    {
        unitPerPixel = worldHeight / pixelSize[1];
        worldWidth = unitPerPixel * pixelSize[0];
    }

    this->worldWidth = worldWidth;
    this->worldHeight = worldHeight;
    this->worldSize << worldWidth, worldHeight;

    // Grid of squarebois
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            entities->emplace_back(new Squareboy(this, 100 + i * 50, 100 + j * 50, 20, 20));
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
