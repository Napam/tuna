#include "../include/base_state.hpp"
#include <iostream>

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
    : window(window), renderer(renderer), event(event), active(false), eventHappened(false),
      inputEventListeners(new std::vector<StateEventListener *>)
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

void BaseState::handle_user_input()
{
    // TODO: Smarter keystroke recollection
    // Hold down a button, and then another will make it
    // forget that the first button is still pressed down etc...

    while (SDL_PollEvent(event) > 0)
    {
        // std::cout << event->type << std::endl;
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