#include "../include/base_state.hpp"
#include <iostream>

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
{
    this->window = window;
    this->renderer = renderer;
    this->event = event;
    active = false;
}

BaseState::~BaseState()
{
}


void BaseState::handle_user_input()
{
    // TODO: Smarter keystroke recollection 
    // Hold down a button, and then another will make it 
    // forget that the first button is still pressed down etc...
    while (SDL_PollEvent(event) > 0)
    {
        switch (event->type)
        {
        case SDL_QUIT:
            active = false;
            break;

        case SDL_KEYDOWN:
            keyinput = (*event).key.keysym.sym;
            switch (keyinput)
            {
            case SDLK_F4:
                active = false;
                break;
            }
            break;

        case SDL_KEYUP:
            keyinput = 0;
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