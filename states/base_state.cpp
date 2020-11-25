#include "../include/base_state.hpp"
#include <iostream>

class FPSController
{
public:
    Uint8 targetFps;
    float targetFrameTime;
    float timeDelta;
    Uint32 prevTime;

    FPSController(Uint8 targetFps);
    void operator()();
};

FPSController::FPSController(Uint8 targetFps)
    : targetFps(targetFps), targetFrameTime(1000 / targetFps), timeDelta(targetFrameTime),
      prevTime(SDL_GetTicks()) {}

void FPSController::operator()()
{
    Uint32 time = SDL_GetTicks();
    timeDelta = time - prevTime;
    prevTime = time;

    if (timeDelta < targetFrameTime)
    {
        SDL_Delay(targetFrameTime - timeDelta);
    }
}

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : window(window), renderer(renderer), event(event), active(false), eventHappened(false),
      inputEventListeners(new std::vector<StateEventListener *>), keystates(SDL_GetKeyboardState(NULL))
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

            for (StateEventListener *listener : *inputEventListeners)
            {
                listener->onKeyDown(keydown);
            }
            break;

        case SDL_KEYUP:
            keyup = (*event).key.keysym.sym;
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
    FPSController fps(60);

    while (active)
    {
        handleUserInput();
        update();
        fps();
    }
}