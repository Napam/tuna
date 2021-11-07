#ifndef BASE_STATE_H
#define BASE_STATE_H

#include "tunapch.hpp"

using json = nlohmann::json;

class BaseWorldObject;
class MousePointer;

/*
Clock used for fps controll and logging time (for example for physics stuff)

targetFPS: Set the target FPS the application should run in, will infer the frame time
           from this
*/
class Clock
{
protected:
    float dt;

public:
    Uint8 targetFps;
    float targetFrameTime;
    Uint32 prevTime;  // Used for delay
    Uint32 frameTime; // Used for physics

    Clock(Uint8 targetFps);

    /*
    Delays with necessary amount of milliseconds such that application runs at targetFps.

    Also updates frameTime attribute, which is used to calculate timesteps in physics etc
    */
    void fpsControll();
};

/* 
Listener is good for handling utf8 input, dont use for charactermovment etc.
Use for handling single key stroke stuff or something
*/
class StateEventListener
{
public:
    virtual ~StateEventListener(){}; // StackOverflow said it was good to do this
    virtual void onKeyDown(SDL_Keycode key) = 0;
    virtual void onKeyUp(SDL_Keycode key) = 0;
    virtual void onMouseDown() = 0;
    virtual void onMouseUp() = 0;
    virtual void onMousewheel(Sint32 horizontal, Sint32 vertical) = 0;
};

/*
Template for states
*/
class BaseState
{
protected:
    std::vector<StateEventListener *> *inputEventListeners = new std::vector<StateEventListener *>;

public:
    bool active = false;
    SDL_Event *event;
    bool mouseLeftIsDown = false;
    bool mouseMiddleIsDown = false;
    bool mouseRightIsDown = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
    float worldDt; // "world dt = world delta time, for physics"
    const Uint8 *keystates;
    Clock clock;
    MousePointer *mousePointer;
    glm::ivec2 pixelSize; // Window size in pixels
    glm::vec2 worldSize; // Window size in world units, initialized in child classes
    json &config;             // Config json reader thing

    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event, json &config);
    virtual ~BaseState();

    /*
    Fills window with color, used for "clearing" the screen
    */
    void clearfill(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /*
    Registers key strokes and broadcast to listeners, also updates keystates.

    This should be run for every application iteration
    */
    void handleUserInput();

    /*
    Setts state activate attribute to true
    */
    void activate();

    /*
    Adds input listener to broadcast vector
    */
    void addInputEventListener(StateEventListener *listener);

    /*
    Runs state, this should not be overriden. 
    */
    BaseState *run();

    /*
    Abstract function, should implement what to do in one application iteration.
    */
    virtual void update() = 0;
};

typedef struct PixelRect
{
    int x, y, w, h;
} PixelRect;

typedef struct WorldRect
{
    float x, y, w, h;
} WorldRect;

/*
Base class for objects that should interact with BaseState
*/
class BaseWorldObject
{
public:
    SDL_Rect rect;        // All objects are enclosed in their rects, representing their area
    WorldRect worldRect;
    glm::vec2 worldPosition; // Position in world units
    glm::ivec2 pixelPosition; // Position in pixel units
    BaseState *state;
    BaseWorldObject(BaseState *state, float x, float y, int w, int h); // Initialize with world coordinates
    BaseWorldObject(BaseState *state, int x, int y, int w, int h);     // Initialize with pixel coordinates

    /*
     * Initializes rect to zero vector
     */
    BaseWorldObject(BaseState *state);

    virtual ~BaseWorldObject(){};
    virtual void update() = 0;

    /*
    Draws rectangle
    */
    void drawRect();

    /*
    Draws circle
    */
    void drawCircle(Sint16 rad);

    /*
    Convert world units to pixel coordinates
    */
    int worldToPixel(float unit, int dim);

    /*
    Convert world units to pixel coordinates
    */
    glm::ivec2 worldToPixel(glm::vec2 units);

    /*
    Comvert pixel coordinates to world units
    */
    float pixelToWorld(int pixel, int dim);

    /*
    Comvert pixel coordinates to world units
    */
    glm::vec2 pixelToWorld(glm::ivec2 pixels);

    /*
    Synchronizes all attributes to world position, e.g. calculate what pixel values should be based 
    on world attributes
    */
    void updateWorldPosition();

    /*
    Accepts world position and synchronizes all attributes to world position, e.g. calculate what 
    pixel values should be based on world attributes
    */
    void updateWorldPosition(float x, float y);

    /*
    Accepts world position and synchronizes all attributes to world position, e.g. calculate what 
    pixel values should be based on world attributes
    */
    void updateWorldPosition(glm::vec2 units);

    /*
    Sets world position attributes and synchronizes all attributes to world position, e.g. calculate 
    what pixel values should be based on world attributes
    */
    void updateWorldPositionX(float x);

    /*
    Sets world position attributes and synchronizes all attributes to world position, e.g. calculate 
    what pixel values should be based on world attributes
    */
    void updateWorldPositionY(float y);

    /*
    Synchronizes all attributes to pixel position, e.g. calculate what world values should be based 
    on pixel attributes
    */
    void updatePixelPosition();

    /*
    Sets pixel attributes and synchronizes all attributes to pixel position, e.g. calculate what 
    world values should be based on pixel attributes
    */
    void updatePixelPosition(int x, int y);

    /*
    Sets pixel attributes and synchronizes all attributes to pixel position, e.g. calculate what 
    world values should be based on pixel attributes
    */
    void updatePixelPosition(glm::ivec2 pixels);

    /*
    Sets pixel attributes and synchronizes all attributes to pixel position, e.g. calculate what 
    world values should be based on pixel attributes
    */
    void updatePixelPositionX(int x);

    /*
    Sets pixel attributes and synchronizes all attributes to pixel position, e.g. calculate what 
    world values should be based on pixel attributes
    */
    void updatePixelPositionY(int y);

    virtual void blit() = 0;
};

/*
A BaseWorldObject for the mousepointer. 
*/
class MousePointer : public BaseWorldObject
{
public:
    MousePointer(BaseState *state);
    virtual void update();
    virtual void blit(){};
};

#endif