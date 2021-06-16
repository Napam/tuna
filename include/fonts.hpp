#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../include/base_state.hpp"

using json = nlohmann::json;

class TTFText : public BaseWorldObject
{
protected:
    SDL_Surface *surface;
    SDL_Texture *texture;

public:
    TTF_Font *font;
    SDL_Color color;
    TTFText(BaseState *state, const char *file, int ptsize, 
            SDL_Color color, int x, int y);
    TTFText(BaseState *state, const char *file, int ptsize, 
            SDL_Color color, float x, float y);
    TTFText(BaseState *state, json &j);
    ~TTFText();
    void setText(const char *text);
    virtual void blit();
    void update();
};

#endif