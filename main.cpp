#include <iostream>
#include <tuple>
#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include "include/utils.hpp"
#include "include/base_state.hpp"
#include "include/boids_state.hpp"

using json = nlohmann::json;

int main(int argc, char **argv)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    std::ifstream configstream("config.json");
    json j3 = json::parse(configstream);

    CreateWindowAndRenderer(
        &window, &renderer, j3["window"]["width"].get<int>(), j3["window"]["height"].get<int>()
    );

    Boids *boids = new Boids(window, renderer, &event, j3);
    boids->run();

    delete boids;

    /* Free all objects*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    /* Quit program */
    SDL_Quit();
    return 0;
}