#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <SDL2/SDL.h>
#include <vector>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Clock
{
protected:
    float dt;

public:
    Uint8 targetFps;
    float targetFrameTime;
    Uint32 prevTime; // Used for delay
    Uint32 frameTime; // Used for physics 

    Clock(Uint8 targetFps);
    void fpsControll();
};

/* 
Listener is good for handling utf8 input, dont use for charactermovment etc.
Use for handling single key stroke stuff or something
*/
class StateEventListener
{
public:
    virtual ~StateEventListener() {};
    virtual void onKeyDown(SDL_Keycode key) = 0;
    virtual void onKeyUp(SDL_Keycode key) = 0;
};

class BaseState
{
protected:
    std::vector<StateEventListener *> *inputEventListeners;

public:
    bool active;
    bool eventHappened;
    SDL_Event *event;
    SDL_Keycode keydown;
    SDL_Keycode keyup;
    SDL_Window *window;
    SDL_Renderer *renderer;
    float worldDt; // "world dt = world delta time, for physics"
    const Uint8 *keystates;
    Clock clock;
    Array2i pixelSize;
    Array2f worldSize;

    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
    ~BaseState();
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void handleUserInput();
    void activate();
    void addInputEventListener(StateEventListener *listener);
    void run();
    virtual void update() = 0;
};

template <class T>
class BaseWorldObject // T should inherit BaseState template
{
public:
    SDL_Rect rect; // All objects are enclosed in their rects, representing their area
    Array2f worldPosition; // Position is center point of rect
    Array2i pixelPosition; // Position is center point of rect
    T *state;
    BaseWorldObject(T *state, float x, float y, int w, int h);
    virtual void update() = 0;

    void drawRect();

    int worldToPixel(float unit, int dim);
    Array2i worldToPixel(Array2f units);
    float pixelToWorld(int pixel, int dim);
    Array2f pixelToWorld(Array2i pixels);

    void updateWorldPosition();
    void updateWorldPosition(float x, float y);
    void updateWorldPositionX(float x);
    void updateWorldPositionY(float y);

    void updatePixelPosition();
    void updatePixelPosition(int x, int y);
    void updatePixelPositionX(int x);
    void updatePixelPositionY(int y);
};

template <class T>
BaseWorldObject<T>::BaseWorldObject(T *state, float x, float y, int w, int h)
    : state(state), worldPosition(x, y)
{
    rect.w = w;
    rect.h = h;
    updateWorldPosition();
}

template <class T>
void BaseWorldObject<T>::drawRect()
{
    SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(state->renderer, &rect);
}

template <class T>
int BaseWorldObject<T>::worldToPixel(float unit, int dim)
{
    return static_cast<int>((unit / state->worldSize[dim]) * state->pixelSize[dim]);
}

template <class T>
Array2i BaseWorldObject<T>::worldToPixel(Array2f units)
{
    return ((units / state->worldSize) * state->pixelSize.template cast<float>()).template cast<int>();
}

template <class T>
float BaseWorldObject<T>::pixelToWorld(int pixel, int dim)
{
    return (static_cast<float>(pixel) / state->pixelSize[dim]) * state->worldSize[dim];
}

template <class T>
Array2f BaseWorldObject<T>::pixelToWorld(Array2i pixels)
{
    return (pixels.cast<float>() / state->pixelSize.template cast<float>()) * state->worldSize;
}

template <class T>
void BaseWorldObject<T>::updateWorldPosition()
{    
    pixelPosition = worldToPixel(worldPosition);

    rect.x = pixelPosition[0];
    rect.y = pixelPosition[1];
}

template <class T>
void BaseWorldObject<T>::updateWorldPosition(float x, float y)
{
    worldPosition[0] = x;
    worldPosition[1] = y;
    updateWorldPosition();
}

template <class T>
void BaseWorldObject<T>::updateWorldPositionX(float x)
{
    worldPosition[0] = x;
    updateWorldPosition();
}

template <class T>
void BaseWorldObject<T>::updateWorldPositionY(float y)
{
    worldPosition[1] = y;
    updateWorldPosition();
}

template <class T>
void BaseWorldObject<T>::updatePixelPosition()
{
    worldPosition = pixelToWorld(pixelPosition);

    rect.x = pixelPosition[0];
    rect.y = pixelPosition[1];
}

template <class T>
void BaseWorldObject<T>::updatePixelPosition(int x, int y)
{
    pixelPosition[0] = x;
    pixelPosition[1] = y;
    updatePixelPosition();
}

template <class T>
void BaseWorldObject<T>::updatePixelPositionX(int x)
{
    pixelPosition[0] = x;
    updatePixelPosition();
}

template <class T>
void BaseWorldObject<T>::updatePixelPositionY(int y)
{
    pixelPosition[1] = y;
    updatePixelPosition();
}

#endif