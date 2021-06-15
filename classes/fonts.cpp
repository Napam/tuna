#include "../include/fonts.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TTFText::TTFText(BaseState *state, const char* file, int ptsize, 
                 SDL_Color color, int x, int y)
    : BaseWorldObject(state, x, y, 0, 0), color(color)
{
    font = TTF_OpenFont(file, ptsize);
    if (!font) {
        std::cout << "Could not open font: " << file << std::endl;
        exit(-1);
    }

    rect.x = x;
    rect.y = y;
}

TTFText::TTFText(BaseState *state, const char* file, int ptsize, 
                 SDL_Color color, float x, float y)
    : BaseWorldObject(state, x, y, 0, 0), color(color)
{
    font = TTF_OpenFont(file, ptsize);
    if (!font) {
        std::cout << "Could not open font: " << file << std::endl;
        exit(-1);
    }

    int w, h;
    SDL_GetRendererOutputSize(state->renderer, &w, &h);

    rect.x = int(x * w);
    rect.y = int(y * h);
}

TTFText::TTFText(BaseState *state, json &j)
    : BaseWorldObject(state)
{
    color = {
        j["color"][0].get<Uint8>(),
        j["color"][1].get<Uint8>(),
        j["color"][2].get<Uint8>(),
        j["color"][3].get<Uint8>()
    };
    
    const char* fontFile = j["fontFile"].get_ptr<json::string_t*>()->c_str();
    font = TTF_OpenFont(fontFile, j["ptsize"].get<Uint8>());
    if (!font) {
        std::cout << "Could not open font: " << fontFile << std::endl;
        exit(-1);
    }
    updateWorldPosition(j["x"].get<float>()*state->worldSize[0], j["y"].get<float>()*state->worldSize[1]);
}

TTFText::~TTFText()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void TTFText::setText(const char *text)
{
    surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(state->renderer, surface);

    rect.w = surface->w;
    rect.h = surface->h;
}

void TTFText::blit()
{
    SDL_RenderCopy(state->renderer, texture, NULL, &rect);
}

void TTFText::update()
{
}