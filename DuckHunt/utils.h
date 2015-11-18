#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 761
#define SCREEN_BPP 32

struct Sprite
{
    int x;
    int y;
    int w;
    int h;
    SDL_Surface *img;
    SDL_Rect *rect_src;
    SDL_Rect *rect_dst;
};

struct Button
{
    bool select;
    SDL_Surface* surface;
    int x;
    int y;
};

SDL_Surface* loadImageWithColorKey(const char* filename, bool colorkey, int r, int g, int b);

#endif
