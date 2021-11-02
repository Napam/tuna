#ifndef FONTS_H
#define FONTS_H

#include "tunapch.h"
#include "../include/baseState.hpp"

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