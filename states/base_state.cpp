#include "../include/base_state.hpp"
#include <iostream>

Clock::Clock(Uint8 targetFps)
    : targetFps(targetFps), targetFrameTime(1000 / targetFps), dt(targetFrameTime),
      prevTime(SDL_GetTicks()) {}

void Clock::fpsControll()
{
    dt = SDL_GetTicks() - prevTime;
    if (dt < targetFrameTime)
        SDL_Delay(targetFrameTime - dt);
    prevTime = SDL_GetTicks();
}

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : window(window), renderer(renderer), event(event), active(false), eventHappened(false),
      inputEventListeners(new std::vector<StateEventListener *>), keystates(SDL_GetKeyboardState(NULL)),
      clock(Clock(60))
{
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
            keydown = (*event).key.keysym.sym;
            switch (keydown)
            {
            case SDLK_F4:
                if ((*event).key.keysym.mod == SDLK_LALT)
                    active = false;
                break;
            }

            // Key presses are broadcasted to listeners
            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onKeyDown(keydown);
            }
            break;

        case SDL_KEYUP:
            keyup = (*event).key.keysym.sym;
            // Key presses are broadcasted to listeners
            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onKeyUp(keyup);
            }
            break;
        }
    }
}

void BaseState::clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Fill sceen with black
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
    }
}