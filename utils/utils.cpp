#include "../include/tunapch.hpp"
#include "../include/utils.hpp"

void CreateWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer, SDL_GLContext **context,
                             int width, int height)
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        goto error;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    *window = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width, height,
                               SDL_WINDOW_OPENGL);
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

    **context = SDL_GL_CreateContext(*window);
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize the OpenGL context." << std::endl;
        exit(1);
    }

    std::cout << "OpenGL version loaded: " 
              << GLVersion.major << "." << GLVersion.minor << "\n";
    
    return;

error:
    std::cout << "Some allocation failed in initialization of SDL objects\n";
    exit(-1);
}

