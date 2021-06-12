#include "../include/base_state.hpp"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <nlohmann/json.hpp>

using namespace Eigen;
using json = nlohmann::json;

Clock::Clock(Uint8 targetFps)
    : targetFps(targetFps), targetFrameTime(1000 / targetFps), dt(targetFrameTime),
      prevTime(SDL_GetTicks()) {std::cout << "targetFrameTime: " << targetFrameTime << std::endl;}

void Clock::fpsControll()
{
    dt = SDL_GetTicks() - prevTime;
    if (dt < targetFrameTime)
        SDL_Delay(targetFrameTime - dt);
    frameTime = SDL_GetTicks() - prevTime;
    prevTime = SDL_GetTicks();
}

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event, json &config)
    : window(window), renderer(renderer), event(event), active(false), eventHappened(false),
      inputEventListeners(new std::vector<StateEventListener *>), keystates(SDL_GetKeyboardState(NULL)),
      config(config), clock(Clock(config["targetFps"].get<int>()))
{
    SDL_GetWindowSize(window, &pixelSize[0], &pixelSize[1]);
    inputEventListeners = new std::vector<StateEventListener *>;
    std::cout << "(" << pixelSize[0] << "," << pixelSize[1] << ")\n";
}

BaseState::~BaseState()
{
    delete inputEventListeners;
}

void BaseState::addInputEventListener(StateEventListener *listener)
{
    inputEventListeners->emplace_back(listener);
}

void BaseState::handleUserInput()
{
    // Polling events updates keystates, VERY IMPORTANT!!!
    while (SDL_PollEvent(event) > 0)
    {
        switch (event->type)
        {
        case SDL_QUIT:
            active = false;
            break;

        case SDL_KEYDOWN:
            keyDown = (*event).key.keysym.sym;
            switch (keyDown)
            {
            case SDLK_F4:
                if ((*event).key.keysym.mod == SDLK_LALT)
                    active = false;
                break;
            }

            // Key presses are broadcasted to listeners
            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onKeyDown(keyDown);
            }
            break;

        case SDL_KEYUP:
            keyUp = (*event).key.keysym.sym;
            // Key presses are broadcasted to listeners
            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onKeyUp(keyUp);
            }
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            mouseDown = (*event).button.button;
            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onMouseDown(mouseDown);
            }
            break;
        
        case SDL_MOUSEBUTTONUP:
            mouseUp = (*event).button.button;
            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onMouseUp(mouseUp);
            }
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

void BaseState::run()
{
    activate();
    while (active)
    {
        handleUserInput();
        update();
        clock.fpsControll();
        worldDt = clock.frameTime / clock.targetFrameTime;
        // std::cout << "worldDt: " << worldDt << " ("<< clock.frameTime << "ms)"<< std::endl;
        // SDL_Delay(20);
    }
}