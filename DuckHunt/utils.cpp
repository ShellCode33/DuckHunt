#include "utils.h"

SDL_Surface* loadImageWithColorKey(const char* filename, bool colorkey, int r, int g, int b)
{
    SDL_Surface* optimizedImage = NULL;
    SDL_Surface* loadedImage = IMG_Load(filename);

    if(loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL && colorkey)
        {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, r, g, b);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }

    return optimizedImage;
}
