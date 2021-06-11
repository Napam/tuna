#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

class TTFText
{
protected:
    SDL_Surface *surface;
    SDL_Texture *texture;

public:
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Color color;
    SDL_Rect rect;
    TTFText(SDL_Renderer *renderer, const char *file, int ptsize, 
            SDL_Color color, int x, int y);
    ~TTFText();
    void setText(const char *text);
    void blit();
};

#endif