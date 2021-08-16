#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
    Uint32 prevTime; // Used for delay
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
    virtual ~StateEventListener() {}; // StackOverflow said it was good to do this
    virtual void onKeyDown(SDL_Keycode key) = 0;
    virtual void onKeyUp(SDL_Keycode key) = 0;
    virtual void onMouseDown(Uint8 button) = 0;
    virtual void onMouseUp(Uint8 button) = 0;
};

/*
Template for states
*/
class BaseState
{
protected:
    std::vector<StateEventListener *> *inputEventListeners;

public:
    bool active;
    bool eventHappened;
    SDL_Event *event;
    SDL_Keycode keyDown;
    SDL_Keycode keyUp;
    Uint8 mouseDown;
    Uint8 mouseUp;
    SDL_Window *window;
    SDL_Renderer *renderer;
    float worldDt; // "world dt = world delta time, for physics"
    const Uint8 *keystates;
    Clock clock;
    Eigen::Array2i pixelSize; // Window size in pixels
    Eigen::Array2f worldSize; // Window size in world units
    json &config; // Config json reader thing

    BaseState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event, json &config);
    ~BaseState();

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
    void run();

    /*
    Abstract function, should implement what to do in one application iteration.
    */
    virtual void update() = 0;
};

/*
Template class for objects that should interact with BaseState
*/
class BaseWorldObject // T should inherit BaseState template
{
public:
    SDL_Rect rect; // All objects are enclosed in their rects, representing their area
    Eigen::Array2f worldPosition; // Position in world units
    Eigen::Array2i pixelPosition; // Position in pixel units
    BaseState *state;
    BaseWorldObject(BaseState *state, float x, float y, int w, int h); // Initialize with world coordinates
    BaseWorldObject(BaseState *state, int x, int y, int w, int h); // Initialize with pixel coordinates

    /*
     * Initializes rect to zero vector
     */
    BaseWorldObject(BaseState *state);
    
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
    Eigen::Array2i worldToPixel(Eigen::Array2f units);

    /*
    Comvert pixel coordinates to world units
    */
    float pixelToWorld(int pixel, int dim);

    /*
    Comvert pixel coordinates to world units
    */
    Eigen::Array2f pixelToWorld(Eigen::Array2i pixels);

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
    void updateWorldPosition(Eigen::Array2f units);

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
    void updatePixelPosition(Eigen::Array2i pixels);

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

#endif