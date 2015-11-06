#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL_image.h>


#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 761
#define SCREEN_BPP 32

SDL_Surface* loadImageWithColorKey(const char* filename, bool colorkey, int r, int g, int b);

#endif
