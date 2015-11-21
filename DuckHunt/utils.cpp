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

void displayBulletLeft(SDL_Surface *screen, SDL_Surface *bullet_img, int bullet_left)
{
    SDL_Rect rect_src, rect_dst;

    rect_dst.x = 65;
    rect_dst.y = 657;
    rect_dst.w = 76;
    rect_dst.h = 50;

    rect_src.w = rect_dst.w;
    rect_src.h = rect_dst.h;
    rect_src.x = 1*(bullet_left+1) + rect_src.w*bullet_left;
    rect_src.y = 1;

    SDL_BlitSurface(bullet_img, &rect_src, screen, &rect_dst);
}

void displayScore(SDL_Surface *screen, TTF_Font *font, int score)
{
    SDL_Color blackcolor = {0, 0, 0, 0};
    SDL_Color whitecolor = {255, 255, 255, 0};

    string score_str = "";
    score_str += to_string(score);

    SDL_Surface *text_score = TTF_RenderText_Shaded(font, score_str.c_str(), whitecolor, blackcolor);

    SDL_Rect rect_dst;
    rect_dst.x = 560;
    rect_dst.y = 683 - text_score->h / 2;
    rect_dst.w = text_score->w;
    rect_dst.h = text_score->h;

    SDL_BlitSurface(text_score, NULL, screen, &rect_dst);
}

void displayDuckHit(SDL_Surface *screen, Duck duck[], int current_wave, SDL_Surface *duck_hit_img)
{
    int i;
    for(i = 0; i < current_wave-1; i++)
    {
        if(duck[i].dead)
            ; //green duck

        else
            ; //red duck
    }


    for(; i < current_wave*2; i++)
    {
        if(duck[i].dead)
            ;//display green duck

        else
            ;
    }

    for(; i < NB_DUCK_PER_LEVEL; i++)
        ; //display grey duck
}
