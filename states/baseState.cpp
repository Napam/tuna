#include "../include/baseState.hpp"
#include <iostream>
#include "pch.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MousePointer::MousePointer(BaseState *state)
    : BaseWorldObject(state)
{
    rect.w = 0;
    rect.h = 0;
}

void MousePointer::update()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    updatePixelPosition(x, y);
    // std::cout << x << "," << y << "\n";
}

Clock::Clock(Uint8 targetFps)
    : targetFps(targetFps), targetFrameTime(1000 / targetFps), dt(targetFrameTime),
      prevTime(SDL_GetTicks()) { std::cout << "targetFrameTime: " << targetFrameTime << std::endl; }

void Clock::fpsControll()
{
    dt = SDL_GetTicks() - prevTime;
    if (dt < targetFrameTime)
        SDL_Delay(targetFrameTime - dt);
    frameTime = SDL_GetTicks() - prevTime;
    prevTime = SDL_GetTicks();
}

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event, json &config)
    : window(window), renderer(renderer), event(event), keystates(SDL_GetKeyboardState(nullptr)),
      config(config), clock(Clock(config["targetFps"].get<int>())), mousePointer(new MousePointer(this))
{
    SDL_GetWindowSize(window, &pixelSize[0], &pixelSize[1]);
    std::cout << "(" << pixelSize[0] << "," << pixelSize[1] << ")\n";
}

BaseState::~BaseState()
{
    delete inputEventListeners;
    delete mousePointer;
}

void BaseState::addInputEventListener(StateEventListener *listener)
{
    inputEventListeners->emplace_back(listener);
}

void BaseState::handleUserInput()
{
    // Polling events updates IO status, VERY IMPORTANT!!!
    while (SDL_PollEvent(event) > 0)
    {
        switch (event->type)
        {
        case SDL_QUIT:
            active = false;
            break;

        case SDL_KEYDOWN: {
            SDL_Keysym keySym = (*event).key.keysym;
            
            if (keySym.mod == SDLK_LALT)
                active = false;

            for (StateEventListener *listener : *inputEventListeners)
                listener->onKeyDown(keySym.sym);

        } break;

        case SDL_KEYUP: {
            SDL_Keycode keyUp = (*event).key.keysym.sym;
            for (StateEventListener *listener : *inputEventListeners)
                listener->onKeyUp(keyUp);

        } break;

        case SDL_MOUSEBUTTONDOWN:
            switch ((*event).button.button)
            {
            case SDL_BUTTON_LEFT:
                mouseLeftIsDown = true;
                break;
            case SDL_BUTTON_MIDDLE:
                mouseMiddleIsDown = true;
                break;
            case SDL_BUTTON_RIGHT:
                mouseRightIsDown = true;
                break;
            default:
                break;
            }

            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onMouseDown();
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch ((*event).button.button)
            {
            case SDL_BUTTON_LEFT:
                mouseLeftIsDown = false;
                break;
            case SDL_BUTTON_MIDDLE:
                mouseMiddleIsDown = false;
                break;
            case SDL_BUTTON_RIGHT:
                mouseRightIsDown = false;
                break;
            default:
                break;
            }

            for (StateEventListener *listener : *inputEventListeners)
                listener->onMouseUp();
            break;

        case SDL_MOUSEWHEEL:
            for (StateEventListener *listener : *inputEventListeners)
                listener->onMousewheel(event->wheel.x, event->wheel.y);
            break;
        }

    }
}

void BaseState::clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

void BaseState::activate()
{
    active = true;
}

BaseState* BaseState::run()
{
    activate();
    while (active)
    {
        handleUserInput();
        mousePointer->update();
        update();
        clock.fpsControll();
        worldDt = clock.frameTime / clock.targetFrameTime;
        // std::cout << "worldDt: " << worldDt << " ("<< clock.frameTime << "ms)"<< std::endl;
        // SDL_Delay(20);
    }

    return nullptr;
}

BaseWorldObject::BaseWorldObject(BaseState *state, float x, float y, int w, int h)
    : state(state)
{
    rect.w = w;
    rect.h = h;
    updateWorldPosition(w, h);
}

BaseWorldObject::BaseWorldObject(BaseState *state, int x, int y, int w, int h)
    : state(state)
{
    rect.w = w;
    rect.h = h;
    updatePixelPosition(x, y);
}

BaseWorldObject::BaseWorldObject(BaseState *state)
    : state(state)
{
    rect.w = 0;
    rect.h = 0;
    updateWorldPosition(0, 0);
}

void BaseWorldObject::drawRect()
{
    SDL_SetRenderDrawColor(state->renderer, 20, 255, 10, 255);
    SDL_Rect temp = {rect.x - rect.w / 2, rect.y - rect.h / 2, rect.w, rect.h};
    SDL_RenderDrawRect(state->renderer, &temp);
}

void BaseWorldObject::drawCircle(Sint16 rad)
{
    filledCircleRGBA(state->renderer, rect.x, rect.y, rad, 20, 255, 10, 255);
}

int BaseWorldObject::worldToPixel(float unit, int dim)
{
    return static_cast<int>((unit / state->worldSize[dim]) * state->pixelSize[dim]);
}

glm::ivec2 BaseWorldObject::worldToPixel(glm::vec2 units)
{
    return (((glm::ivec2)units / (glm::ivec2)state->worldSize) * state->pixelSize);
}

float BaseWorldObject::pixelToWorld(int pixel, int dim)
{
    return (static_cast<float>(pixel) / state->pixelSize[dim]) * state->worldSize[dim];
}

glm::vec2 BaseWorldObject::pixelToWorld(glm::ivec2 pixels)
{
    return (((glm::vec2)pixels / (glm::vec2)state->pixelSize) * state->worldSize);
}

void BaseWorldObject::updateWorldPosition()
{
    pixelPosition = worldToPixel(worldPosition);

    rect.x = pixelPosition[0];
    rect.y = pixelPosition[1];
}

void BaseWorldObject::updateWorldPosition(float x, float y)
{
    worldPosition[0] = x;
    worldPosition[1] = y;
    updateWorldPosition();
}

void BaseWorldObject::updateWorldPosition(glm::vec2 units)
{
    worldPosition = units;
    updateWorldPosition();
}

void BaseWorldObject::updateWorldPositionX(float x)
{
    worldPosition[0] = x;
    updateWorldPosition();
}

void BaseWorldObject::updateWorldPositionY(float y)
{
    worldPosition[1] = y;
    updateWorldPosition();
}

void BaseWorldObject::updatePixelPosition()
{
    worldPosition = pixelToWorld(pixelPosition);

    rect.x = pixelPosition[0];
    rect.y = pixelPosition[1];
}

void BaseWorldObject::updatePixelPosition(int x, int y)
{
    pixelPosition[0] = x;
    pixelPosition[1] = y;
    updatePixelPosition();
}

void BaseWorldObject::updatePixelPosition(glm::ivec2 pixels)
{
    pixelPosition = pixels;
    updatePixelPosition();
}

void BaseWorldObject::updatePixelPositionX(int x)
{
    pixelPosition[0] = x;
    updatePixelPosition();
}

void BaseWorldObject::updatePixelPositionY(int y)
{
    pixelPosition[1] = y;
    updatePixelPosition();
}