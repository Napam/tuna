#include "../include/fonts.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTFText::TTFText(SDL_Renderer *renderer, const char* file, int ptsize, 
                 SDL_Color color, int x, int y, int w, int h)
    : renderer(renderer), color(color)
{
    font = TTF_OpenFont(file, ptsize);
    if (!font) {
        std::cout << "Could not open font: " << file << std::endl;
        exit(-1);
    }

    rect = {x, y, w, h};
}

TTFText::~TTFText()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void TTFText::setText(const char *text)
{
    surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void TTFText::blit()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}