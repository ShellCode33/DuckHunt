#include "menu.h"

int detectMouseMenu(Button &singleplayer, Button &quit, SDL_Event &event)
{
    int ret_value = 0;

    if (event.motion.x< (SCREEN_WIDTH/2+(singleplayer.surface->w/2)) && event.motion.x > (SCREEN_WIDTH/2-(singleplayer.surface->w/2)) && event.motion.y>(SCREEN_HEIGHT/3-(singleplayer.surface->h/2)) && event.motion.y<(SCREEN_HEIGHT/3+(singleplayer.surface->h/2)))
    {
        singleplayer.select = true;
        quit.select=false;

        if (event.type == SDL_MOUSEBUTTONDOWN) //Click on play button
            ret_value = 1;

    }
    else if(event.motion.x< (SCREEN_WIDTH/2+(quit.surface->w/2)) && event.motion.x > (SCREEN_WIDTH/2-(quit.surface->w/2)) && event.motion.y>(SCREEN_HEIGHT/2-(quit.surface->h/2)) && event.motion.y<(SCREEN_HEIGHT/2+(quit.surface->h/2)))
    {
        singleplayer.select = false;
        quit.select = true;

        if (event.type == SDL_MOUSEBUTTONDOWN)
            ret_value = -1;
    }

    else
    {
        singleplayer.select = false;
        quit.select = false;
    }

    return ret_value;
}

void showMenu(SDL_Surface *screen, SDL_Surface *menu_img, TTF_Font* small_font, TTF_Font* big_font, Button &singleplayer, Button &quit)
{
    SDL_Color blackcolor = {0, 0, 0, 0};

    SDL_Rect text_rect;

    SDL_BlitSurface(menu_img, NULL, screen, NULL);

    if(singleplayer.select)
    {
        singleplayer.surface = TTF_RenderText_Solid(big_font, "Play", blackcolor);
        quit.surface = TTF_RenderText_Solid(small_font, "Quit", blackcolor);
        singleplayer.x = SCREEN_WIDTH/2-(singleplayer.surface->w/2)-(12.5);
        singleplayer.y = SCREEN_HEIGHT/3-(singleplayer.surface->h/2)-(12.5);
        quit.x = SCREEN_WIDTH/2-(quit.surface->w/2);
        quit.y = SCREEN_HEIGHT/2-(quit.surface->h/2);
    }
    else if(quit.select)
    {
        quit.surface = TTF_RenderText_Solid(big_font, "Quit", blackcolor);
        singleplayer.surface = TTF_RenderText_Solid(small_font, "Play", blackcolor);
        quit.x = SCREEN_WIDTH/2-(quit.surface->w/2)-(12.5);
        quit.y = SCREEN_HEIGHT/2-(quit.surface->h/2)-(12.5);
        singleplayer.x = SCREEN_WIDTH/2-(singleplayer.surface->w/2);
        singleplayer.y = SCREEN_HEIGHT/3-(singleplayer.surface->h/2);
    }
    else
    {
        singleplayer.x = SCREEN_WIDTH/2-(singleplayer.surface->w/2);
        singleplayer.y = SCREEN_HEIGHT/3-(singleplayer.surface->h/2);
        quit.x = SCREEN_WIDTH/2-(quit.surface->w/2);
        quit.y = SCREEN_HEIGHT/2-(quit.surface->h/2);
        quit.surface = TTF_RenderText_Solid(small_font, "Quit", blackcolor);
        singleplayer.surface = TTF_RenderText_Solid(small_font, "Play", blackcolor);
    }


    text_rect.x = singleplayer.x;
    text_rect.y = singleplayer.y;
    SDL_BlitSurface(singleplayer.surface, NULL, screen, &text_rect);

    text_rect.x = quit.x;
    text_rect.y = quit.y;
    SDL_BlitSurface(quit.surface, NULL, screen, &text_rect);
}
