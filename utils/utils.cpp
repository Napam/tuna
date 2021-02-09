#include "../include/utils.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void CreateWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer)
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        goto error;
    }
    
    if(TTF_Init() < 0)
    {
        std::cout << "Failed to initialize the SDL2_TTF library\n";
        goto error;
    }

    *window = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               1366, 768,
                               0);

    if(!(*window))
    {
        std::cout << "Failed to create window\n";
        goto error;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(!(*renderer))
    {
        std::cout << "Failed to get the renderer from the window\n";
        goto error;
    }
    
    return;

error:
    std::cout << "Some allocation failed in initialization of SDL objects\n";
    exit(-1);
}

