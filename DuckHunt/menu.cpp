#include "menu.h"

void detectKeyboardMenu(Button &singleplayer, Button &quit)
{
    Uint8* keystate = SDL_GetKeyState(NULL);
    if (singleplayer.select && (keystate[SDLK_UP] || keystate[SDLK_DOWN]))
    {
        singleplayer.select = false;
        quit.select=true;
    }
    else if (quit.select && (keystate[SDLK_UP] || keystate[SDLK_DOWN]))
    {
        quit.select=false;
        singleplayer.select=true;
    }
}

void showMenu(SDL_Surface *screen, SDL_Surface *menu_img, TTF_Font* small_font, TTF_Font* big_font, Button &singleplayer, Button &quit)
{
    SDL_Color blackcolor = {0, 0, 0, 0};

    SDL_Rect text_rect;
    text_rect.x = singleplayer.x;
    text_rect.y = singleplayer.y;

    SDL_BlitSurface(menu_img, NULL, screen, NULL);

    if(singleplayer.select)
    {
        singleplayer.surface = TTF_RenderText_Solid(big_font, "Play", blackcolor);
        quit.surface = TTF_RenderText_Solid(small_font, "Quit", blackcolor);
    }
    else if(quit.select)
    {
        quit.surface = TTF_RenderText_Solid(big_font, "Quit", blackcolor);
        singleplayer.surface = TTF_RenderText_Solid(small_font, "Play", blackcolor);
    }

    SDL_BlitSurface(singleplayer.surface, NULL, screen, &text_rect);
    text_rect.x = quit.x;
    text_rect.y = quit.y;

    SDL_BlitSurface(quit.surface, NULL, screen, &text_rect);
}
