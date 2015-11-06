#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL_image.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

SDL_Surface* loadImageWithColorKey(char* filename, int r, int g, int b);

#endif
