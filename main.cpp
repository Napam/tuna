#include <iostream>
#include <tuple>
#include <SDL2/SDL.h>
#include "utils.h"

class BaseState
{
protected:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

public:
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        // Fill sceen with black
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }
};


class BaseGameObject
{
public:
    void draw();
    void interact();
};

class Square
{

};

class Boids:BaseState
{
public:
    Boids(SDL_Window* window, SDL_Surface* surface, SDL_Renderer* renderer) 
    {
        this->window = window;
        this->surface = surface;
        this->renderer = renderer;
    }

    int run()
    {
        SDL_UpdateWindowSurface(window);

        bool run = true;
        SDL_Event e;

        int i = 0;
        while (run)
        {
            while (SDL_PollEvent(&e) > 0) 
            {
                switch (e.type) 
                {
                    case SDL_QUIT:
                        run = false;
                        break;
                }
            }

            // Create a square
            // create a black square
            SDL_Rect rect= {i,i,10+i,10+i}; // x, y, width, height
    
            // std::cout << "i = " << i <<"\n";
            
            // Fill sceen with black
            clearfill(0,0,0,255);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
            i++;
        }

        return 0;
    }
};


int main(int argc, char **argv)
{
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;

    std::tie(window, surface, renderer) = GetSDLobjects();

    Boids boids(window, surface, renderer);
    boids.run();

    /* Free all objects*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit program */
    SDL_Quit();
    return 0;
}