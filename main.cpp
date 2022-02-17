#include "include/tunapch.hpp"
#include "include/utils.hpp"
#include "include/baseState.hpp"
#include "include/simpleState.hpp"
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

        // Create an event handler
        SDL_Event event;
        // Loop condition
        bool running = true;

        while (running) {
            SDL_PollEvent(&event);

            switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
            }

            glClearColor(1.0f,1.0f,0.0f,1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);

            SDL_GL_SwapWindow(window);
        }

        // Destroy everything to not leak memory.
        // SDL_GL_DeleteContext(gl_context);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();

        return;

        manager.addState("simple", new SimpleState(window, renderer, &event, j3, 2000, -1));

        currentState = manager.getState("simple");
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