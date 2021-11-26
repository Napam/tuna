#include "include/tunapch.hpp"
#include "include/utils.hpp"
#include "include/baseState.hpp"
#include "include/simpleState.hpp"
#include "include/simpleGlState.hpp"
#include "include/manager.hpp"

using json = nlohmann::json;

class GameApp {
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext *context;
    SDL_Event event;
    SimpleState *simpleState;
    BaseState *currentState;
    Manager manager;

    GameApp() {
        std::ifstream configstream("config.json");
        json j3 = json::parse(configstream);

        CreateWindowAndRenderer(
            &window, &renderer, &context, 
            j3["window"]["width"].get<int>(), j3["window"]["height"].get<int>()
        );

        manager.addState("simple", new SimpleState(window, renderer, &event, j3, 2000, -1));
        manager.addState("simpleGl", new SimpleGlState(window, renderer, &event, j3, 2000, -1));

        currentState = manager.getState("simpleGl");
        currentState->activate();
        while (currentState = currentState->run());
    }

    ~GameApp() {

        /* Free all objects*/
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        /* Quit program */
        SDL_Quit();
    }
};

int main(int argc, char **argv)
{
    GameApp game;
    return 0;
}