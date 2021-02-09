#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <cmath>
#include "../include/base_state.hpp"
#include "../include/boids_state.hpp"
#include "../include/utils.hpp"
#include "../include/utils.hpp"
#include <eigen3/Eigen/Dense>

class Squareboy
    : public BaseWorldObject<Boids>
{
public:
    Eigen::Array2f velocity, acceleration;
    bool spacemode;
    Squareboy(Boids *state, float x, float y, int w, int h);
    void interactUser();
    void behave();
    void blit();
    void motion();
    virtual void update();
};

Squareboy::Squareboy(Boids *state, float x, float y, int w, int h)
    : BaseWorldObject(state, x, y, w, h), velocity(0.0, 0.0), acceleration(0.0, 0.0), spacemode(false)
{
}

void Squareboy::blit()
{
    drawRect();
}

void Squareboy::interactUser()
{
    const Uint8 *keys = state->keystates;
    acceleration = 0;

    if (keys[SDL_SCANCODE_A])
    {
        acceleration[0] -= 1;
    }

    if (keys[SDL_SCANCODE_D])
    {
        acceleration[0] += 1;
    }

    if (keys[SDL_SCANCODE_W])
    {
        acceleration[1] -= 1;
    }

    if (keys[SDL_SCANCODE_S])
    {
        acceleration[1] += 1;
    }

    if (keys[SDL_SCANCODE_SPACE])
    {
        acceleration *= 5;
    }

    velocity += acceleration;
}

void Squareboy::behave()
{
    if ((pixelPosition[0] < 0) || (pixelPosition[0] > state->pixelSize[0]))
        updatePixelPositionX(pymod(pixelPosition[0], state->pixelSize[0]));
    else if ((pixelPosition[1] < 0) || (pixelPosition[1] > state->pixelSize[1]))
        updatePixelPositionY(pymod(pixelPosition[1], state->pixelSize[1]));
}

void Squareboy::motion()
{
    velocity -= velocity * 0.1 * state->worldDt;
    updateWorldPosition(worldPosition + velocity * state->worldDt);
}

void Squareboy::update()
{
    interactUser();
    behave();
    motion();
}

// ############################################################################################# //

Boids::Boids(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event,
             float worldWidth, float worldHeight)
    : BaseState(window, renderer, event)
{
    float unitPerPixel;

    entities = new std::vector<void *>;

    if ((worldHeight == -1) && (worldWidth == -1))
    {
        throw std::invalid_argument(
            "worldHeight and worldWidth cannot both be -1 stoopid");
    }

    if (worldHeight == -1)
    {
        unitPerPixel = worldWidth / pixelSize[0];
        worldHeight = unitPerPixel * pixelSize[1];
    }
    else if (worldWidth == -1)
    {
        unitPerPixel = worldHeight / pixelSize[1];
        worldWidth = unitPerPixel * pixelSize[0];
    }

    this->worldSize << worldWidth, worldHeight;

    // Grid of squarebois
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            entities->emplace_back(new Squareboy(this, 100 + i * 50, 100 + j * 50, 20, 20));
        }
    }
    // entities->emplace_back(new Squareboy(this, 100, 100, 20, 20));
};

Boids::~Boids()
{
    for (void *ent : *entities)
    {
        delete (Squareboy *)ent;
    }
    delete entities;
}

void Boids::updateGraphics()
{
    // Fill sceen with black
    clearfill(0, 0, 0, 255);

    for (void *ent : *entities)
    {
        ((Squareboy *)ent)->blit();
    }

    TTF_Font *Sans = TTF_OpenFont("Lato-Regular.ttf", 12); //this opens a font style and sets a size
    if (!Sans)
    {
        std::cout << Sans << std::endl;
        std::cout << "Font not work hehe\n";
        exit(4);
    }

    SDL_Color White = {255, 255, 255}; // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;    //controls the rect's x coordinate
    Message_rect.y = 0;    // controls the rect's y coordinte
    Message_rect.w = 200;  // controls the width of the rect
    Message_rect.h = 100;  // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    // Flip
    SDL_RenderPresent(renderer);

    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void Boids::logic()
{
    for (void *ent : *entities)
    {
        ((Squareboy *)ent)->update();
    }
}

void Boids::interactUser()
{
}

/*
What to do in one iteration in game loop, will be called by BaseState::run, no need to 
manually write game loop here
*/
void Boids::update()
{
    interactUser();
    logic();
    updateGraphics();
}
