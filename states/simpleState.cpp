#include "tunapch.h"
#include "../include/baseState.hpp"
#include "../include/utils.hpp"
#include "../include/simpleState.hpp"
#include "../include/fonts.hpp"
#define EPSILON 1e-6f

using json = nlohmann::json;

class Squareboy
    : public BaseWorldObject    
{
public:
    glm::vec2 velocity, acceleration;
    float repel{state->config["simple"]["misc"]["repel"]}, attract{state->config["simple"]["misc"]["attract"]};
    Sint16 circleRadius{state->config["debug"]["circleRadius"]};
    float mouseForce{state->config["simple"]["misc"]["mouseForce"]};
    float maxAcc{state->config["simple"]["misc"]["maxAcc"]};
    Squareboy(BaseState *state, float x, float y, int w, int h);
    Squareboy(BaseState *state, int x, int y, int w, int h);
    void interactUser();
    void behave();
    void blit();
    void motion();
    virtual void update();
    virtual ~Squareboy();
};

Squareboy::~Squareboy()
{
}

Squareboy::Squareboy(BaseState *state, float x, float y, int w, int h)
    : BaseWorldObject(state, x, y, w, h), velocity(0.0, 0.0), acceleration(0.0, 0.0)
{
}

Squareboy::Squareboy(BaseState *state, int x, int y, int w, int h)
    : BaseWorldObject(state, x, y, w, h), velocity(0.0, 0.0), acceleration(0.0, 0.0)
{
}

void Squareboy::blit()
{
    drawRect();
    drawCircle(circleRadius);
}

void Squareboy::interactUser()
{
    const Uint8 *keys = state->keystates;

    if (keys[SDL_SCANCODE_A])        { acceleration[0] += 2; }
    if (keys[SDL_SCANCODE_D])        { acceleration[0] -= 2; }
    if (keys[SDL_SCANCODE_W])        { acceleration[1] += 2; }
    if (keys[SDL_SCANCODE_S])        { acceleration[1] -= 2; }
    if (keys[SDL_SCANCODE_SPACE])    { acceleration *= 6; }
    if (keys[SDL_SCANCODE_LSHIFT])   { acceleration /= 6; }
    if (keys[SDL_SCANCODE_C])        { velocity -= velocity * 0.1f * state->worldDt; }

    glm::vec2 diff;
    float norm;
    if (state->mouseRightIsDown) {
        diff = (worldPosition - state->mousePointer->worldPosition) + EPSILON;
        norm = diff.length() + EPSILON; 
        acceleration -= diff / norm * mouseForce;
    }
}

void Squareboy::behave()
{
    glm::vec2 diff;
    float repelForce, norm, attractForce;
    std::vector<void *> entites;

    if ((pixelPosition[0] < 0) || (pixelPosition[0] > state->pixelSize[0]))
        updatePixelPositionX(pymod(pixelPosition[0], state->pixelSize[0]));
    else if ((pixelPosition[1] < 0) || (pixelPosition[1] > state->pixelSize[1]))
        updatePixelPositionY(pymod(pixelPosition[1], state->pixelSize[1]));

    entites = *((SimpleState *)state)->entities;

    // Can be more vectorized
    for (void *ent : entites)
    {
        if (ent == this) { continue; }

        diff = (worldPosition - ((BaseWorldObject *)ent)->worldPosition) + EPSILON;
        norm = diff.length() + 1e-6; // Euclidean norm

        repelForce = std::min(repel / std::pow(norm, 2), 20.0);
        attractForce = std::min(attract / norm, 20.0F);

        diff /= norm;
        acceleration += diff * (repelForce - attractForce);
    }
}

void Squareboy::motion()
{
    float accnorm = acceleration.length();
    if (accnorm > maxAcc) {
        acceleration = acceleration / accnorm * maxAcc;
    }

    velocity += acceleration * state->worldDt;
    velocity -= velocity * 0.08f * state->worldDt;
    updateWorldPosition(worldPosition + velocity * state->worldDt);
}

void Squareboy::update()
{
    acceleration *= 0;
    interactUser();
    behave();
    motion();
}

// ############################################################################################# //
class FpsCounter : public TTFText
{
public:
    Uint32 prevTime, updateRate;
    FpsCounter(BaseState *state);
    ~FpsCounter();
    virtual void update();
};

FpsCounter::FpsCounter(BaseState *state)
    : TTFText(state, state->config["simple"]["fpsMonitor"]), prevTime(SDL_GetTicks()), updateRate(250)
{
}

FpsCounter::~FpsCounter()
{
    std::cout << "Deleting FpsCounter\n";
}

void FpsCounter::update()
{
    if ((SDL_GetTicks() - prevTime) > updateRate)
    {
        std::stringstream ss;
        // Avoid divison by zero
        ss << "FPS: " << int(1000 / (state->clock.frameTime + 0.001));
        const std::string &tmp = ss.str();
        const char *cstr = tmp.c_str();
        this->setText(cstr);
        prevTime = SDL_GetTicks();
    }
}

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

    // Grid of squarebois
    int n = config["simple"]["misc"]["nStartBoxes"].get<int>();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            entities->emplace_back(new Squareboy(this, 100 + i * 50, 100 + j * 50, 20, 20));
        }
    }

    if (config["simple"]["fpsMonitor"]["use"].get<bool>())
    {
        entities->emplace_back(new FpsCounter(this));
    }
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
    // Fill sceen with black
    clearfill(0, 0, 0, 255);

    for (void *ent : *entities)
    {
        ((BaseWorldObject *)ent)->blit();
    }

    if (keystates[SDL_SCANCODE_LSHIFT])
        mousePointer->drawCircle(16);

    // Flip
    SDL_RenderPresent(renderer);
}

void SimpleState::logic()
{
    for (void *ent : *entities)
    {
        ((BaseWorldObject *)ent)->update();
    }

    if (mouseLeftIsDown && keystates[SDL_SCANCODE_LCTRL])
    {
        entities->emplace_back(new Squareboy(this, mousePointer->pixelPosition[0], mousePointer->pixelPosition[1], 20, 20));
    }

    if (mouseLeftIsDown && keystates[SDL_SCANCODE_LSHIFT]) 
    {   
        std::erase_if(*entities, 
            [mousePos = mousePointer->worldPosition](void *ent){
                glm::vec2 diff;
                diff = ((BaseWorldObject *)ent)->worldPosition - mousePos;
                
                if (diff.length() < 500) {
                    delete (BaseWorldObject *)ent;
                    return true;
                } else {
                    return false;
                };
            }
        );
    }

}

void SimpleState::onMouseDown()
{
    if (mouseLeftIsDown)
        entities->emplace_back(new Squareboy(this, mousePointer->pixelPosition[0], mousePointer->pixelPosition[1], 20, 20));

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
    float val = 1.05;
    float multiplier = vertical > 0 ? val : 1 / val;
    worldSize *= multiplier;
    for (void *ent : *entities)
    {
        
    }
}

/*
What to do in one iteration in game loop, will be called by BaseState::run, no need to
manually write game loop here
*/
void SimpleState::update()
{
    logic();
    updateGraphics();
}
