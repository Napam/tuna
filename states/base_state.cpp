#include "../headers/base_state.hpp"

BaseState::BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event)
{
    this->window = window;
    this->renderer = renderer;
    this->event = event;
    active = false;
}

BaseState::~BaseState()
{}

void BaseState::handle_user_input()
{
    while (SDL_PollEvent(event) > 0)
    {
        switch (event->type)
        {
        case SDL_QUIT:
            active = false;
        case SDLK_F4:
            active = false;
        }
    }
}

void BaseState::clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Fill sceen with black
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}