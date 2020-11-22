#include "../include/utils.hpp"

std::tuple<SDL_Window*, SDL_Renderer*> GetSDLobjects()
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        goto error;
    }

    window = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               680, 480,
                               0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        goto error;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        std::cout << "Failed to get the renderer from the window\n";
        goto error;
    }
    
    return std::make_tuple(window, renderer);

error:
    std::cout << "Some allocation failed in initialization of SDL objects\n";
    exit(-1);
}