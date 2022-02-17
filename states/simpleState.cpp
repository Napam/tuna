#include "tunapch.hpp"
#include "../include/simpleState.hpp"
#include "../include/utils.hpp"
#define EPSILON 1e-4f

using json = nlohmann::json;

// ############################################################################################# //
SimpleState::SimpleState(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event,
                         json &config, float worldWidth, float worldHeight)
    : BaseState(window, renderer, event, config)
{
    float unitPerPixel;

    entities = new std::vector<void *>;

    this->addInputEventListener(this);

    if ((worldHeight == -1) && (worldWidth == -1))
        throw std::invalid_argument( "worldHeight and worldWidth cannot both be -1 stoopid");

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

    this->worldSize = {worldWidth, worldHeight};
};

SimpleState::~SimpleState()
{
    for (void *ent : *entities)
    {
        delete (BaseWorldObject *)ent;
    }
    delete entities;
}

void SimpleState::updateGraphics()
{
    // glClearColor(0, 0, 0, 1);

    // // You'd want to use modern OpenGL here
    // glColor3d(0, 1, 0);
    // glBegin(GL_TRIANGLES);
    //     glVertex2f(.2, 0);
    //     glVertex2f(.01, .2);
    //     glVertex2f(-.2, 0);
    // glEnd();

    // SDL_GL_SwapWindow(window);
}

void SimpleState::logic()
{
}

void SimpleState::onMouseDown()
{
    if (mouseLeftIsDown) 
    {
    }

    if (mouseRightIsDown)
    {
    }
}

void SimpleState::onMouseUp()
{
    if (!mouseLeftIsDown)
    {
    }
    if (!mouseRightIsDown)
    {
    }
}

void SimpleState::onMousewheel(Sint32 horizontal, Sint32 vertical)
{
}

/*
What to do in one iteration in game loop, will be called by BaseState::run, no need to
manually write game loop here
*/
void SimpleState::update()
{
    // logic();
    updateGraphics();
}
