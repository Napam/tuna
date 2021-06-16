#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <cmath>
#include "../include/base_state.hpp"
#include "../include/boids_state.hpp"
#include "../include/utils.hpp"
#include "../include/utils.hpp"
#include "../include/fonts.hpp"
#include <eigen3/Eigen/Dense>
#include <iomanip>

using json = nlohmann::json;

class Squareboy
    : public BaseWorldObject<BaseState>
{
public:
    Eigen::Array2f velocity, acceleration;
    bool spacemode;
    Squareboy(BaseState *state, float x, float y, int w, int h);
    Squareboy(BaseState *state, int x, int y, int w, int h);
    void interactUser();
    void behave();
    void blit();
    void motion();
    virtual void update();
};

Squareboy::Squareboy(BaseState *state, float x, float y, int w, int h)
    : BaseWorldObject(state, x, y, w, h), velocity(0.0, 0.0), acceleration(0.0, 0.0), spacemode(false)
{
}

Squareboy::Squareboy(BaseState *state, int x, int y, int w, int h)
    : BaseWorldObject(state, x, y, w, h), velocity(0.0, 0.0), acceleration(0.0, 0.0), spacemode(false)
{
}

void Squareboy::blit()
{
    drawRect();
    drawCircle(state->config["debug"]["circleRadius"]);
}

void Squareboy::interactUser()
{
    const Uint8 *keys = state->keystates;
    acceleration = 0;

    if (keys[SDL_SCANCODE_A])
    {
        acceleration[0] -= 2;
    }

    if (keys[SDL_SCANCODE_D])
    {
        acceleration[0] += 2;
    }

    if (keys[SDL_SCANCODE_W])
    {
        acceleration[1] -= 2;
    }

    if (keys[SDL_SCANCODE_S])
    {
        acceleration[1] += 2;
    }

    if (keys[SDL_SCANCODE_SPACE])
    {
        acceleration *= 6;
    }
    
    if (keys[SDL_SCANCODE_LSHIFT])
    {
        acceleration /= 6;
    }

    if (keys[SDL_SCANCODE_C])
    {
        velocity -= velocity * 0.1 * state->worldDt;
    }

    velocity += acceleration * state->worldDt;
}

void Squareboy::behave()
{
    if ((pixelPosition[0] < 0) || (pixelPosition[0] > state->pixelSize[0]))
        updatePixelPositionX(pymod(pixelPosition[0], state->pixelSize[0]));
    else if ((pixelPosition[1] < 0) || (pixelPosition[1] > state->pixelSize[1]))
        updatePixelPositionY(pymod(pixelPosition[1], state->pixelSize[1]));
}

void Squareboy::motion()
{
    velocity -= velocity * 0.05 * state->worldDt;
    updateWorldPosition(worldPosition + velocity * state->worldDt);
}

void Squareboy::update()
{
    interactUser();
    behave();
    motion();
}

// ############################################################################################# //

class FpsCounter : public TTFText
{
public:
    Uint32 prevTime, updateRate;
    FpsCounter(BaseState *state);
    virtual void update();
};

FpsCounter::FpsCounter(BaseState *state) 
    : TTFText(state, state->config["boids"]["fpsMonitor"]), prevTime(SDL_GetTicks()), updateRate(250)
{
}

void FpsCounter::update() 
{
    if ((SDL_GetTicks() - prevTime) > updateRate) {
        std::stringstream ss;
        // Avoid divison by zero
        ss << "FPS: " << int(1000 / (state->clock.frameTime + 0.001));
        const std::string &tmp = ss.str();
        const char *cstr = tmp.c_str();
        this->setText(cstr);
        prevTime = SDL_GetTicks();
    }
}

Boids::Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event,
             json &config, float worldWidth, float worldHeight)
    : BaseState(window, renderer, event, config)
{
    float unitPerPixel;

    entities = new std::vector<void *>;

    this->addInputEventListener(this);

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

    this->worldSize << worldWidth, worldHeight;

    // Grid of squarebois
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            entities->emplace_back(new Squareboy(this, 100 + i * 50, 100 + j * 50, 20, 20));
        }
    }

    entities->emplace_back(new FpsCounter(this));
};

Boids::~Boids()
{
    for (void *ent : *entities)
    {
        delete (BaseWorldObject<BaseState> *)ent;
    }
    delete entities;
}

void Boids::updateGraphics()
{
    // Fill sceen with black
    clearfill(0, 0, 0, 255);

    for (void *ent : *entities)
    {
        ((BaseWorldObject<BaseState> *)ent)->blit();
    }

    // Flip
    SDL_RenderPresent(renderer);
}

void Boids::logic()
{
    for (void *ent : *entities)
    {
        ((BaseWorldObject<BaseState> *)ent)->update();
    }
}

void Boids::onMouseDown(Uint8 button) {
    if (button == SDL_BUTTON_LEFT) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        entities->emplace_back(new Squareboy(this, x, y, 20, 20));
    }
        
    if (button == SDL_BUTTON_RIGHT) {}
}

void Boids::onMouseUp(Uint8 button) {
    if (button == SDL_BUTTON_LEFT) {}
    if (button == SDL_BUTTON_RIGHT) {}
}

/*
What to do in one iteration in game loop, will be called by BaseState::run, no need to 
manually write game loop here
*/
void Boids::update()
{
    logic();
    updateGraphics();
}
