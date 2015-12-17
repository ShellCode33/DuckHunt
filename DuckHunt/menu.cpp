#include "menu.h"

int detectMouseMenu(Button &singleplayer, Button &quit, Button &boss, Button &highscores,SDL_Event &event)
{
    int ret_value = 0;

    if (event.motion.x< (singleplayer.x+singleplayer.surface->w) && event.motion.x > (singleplayer.x) && event.motion.y>(singleplayer.y) && event.motion.y<(singleplayer.y+singleplayer.surface->h))
    {
        singleplayer.select = true;
        quit.select = highscores.select = boss.select = false;

        if (event.type == SDL_MOUSEBUTTONDOWN) //Click on play button
            ret_value = 1;
    }
    else if(event.motion.x< (quit.x + quit.surface->w) && event.motion.x > (quit.x) && event.motion.y>(quit.y) && event.motion.y<(quit.y+quit.surface->h))
    {
        boss.select = highscores.select = singleplayer.select = false;
        quit.select = true;

        if (event.type == SDL_MOUSEBUTTONDOWN)
            ret_value = -1;
    }

    else if(event.motion.x< (boss.x + boss.surface->w) && event.motion.x > (boss.x) && event.motion.y>(boss.y) && event.motion.y<(boss.y+boss.surface->h))
    {
        boss.select = true;
        quit.select = highscores.select = singleplayer.select = false;

        if (event.type == SDL_MOUSEBUTTONDOWN)
            ret_value = 2;
    }

    else if(event.motion.x< (highscores.x + highscores.surface->w) && event.motion.x > (highscores.x) && event.motion.y>(highscores.y) && event.motion.y<(highscores.y+highscores.surface->h))
    {
        highscores.select = true;
        quit.select = boss.select = singleplayer.select = false;

        if (event.type == SDL_MOUSEBUTTONDOWN)
            ret_value = 3;
    }

    else
    {
        singleplayer.select = quit.select = boss.select = highscores.select = false;
    }

    return ret_value;
}

void showMenu(SDL_Surface *screen, SDL_Surface *menu_img, TTF_Font* small_font, TTF_Font* big_font, Button &singleplayer, Button &quit, Button &highscores, Button &boss_button)
{
    SDL_Color blackcolor = {0, 0, 0, 0};
    SDL_Rect text_rect;

    SDL_BlitSurface(menu_img, NULL, screen, NULL);

    if(singleplayer.select)
        singleplayer.surface = TTF_RenderText_Solid(big_font, "Play", blackcolor);

    else
        singleplayer.surface = TTF_RenderText_Solid(small_font, "Play", blackcolor);

    if(quit.select)
        quit.surface = TTF_RenderText_Solid(big_font, "Quit", blackcolor);

    else
        quit.surface = TTF_RenderText_Solid(small_font, "Quit", blackcolor);

    if(boss_button.select)
        boss_button.surface = TTF_RenderText_Solid(big_font, "Boss", blackcolor);

    else
        boss_button.surface = TTF_RenderText_Solid(small_font, "Boss", blackcolor);

    if(highscores.select)
        highscores.surface = TTF_RenderText_Solid(big_font, "Highscores", blackcolor);

    else
        highscores.surface = TTF_RenderText_Solid(small_font, "Highscores", blackcolor);

    singleplayer.x = (SCREEN_WIDTH - singleplayer.surface->w) / 2;
    quit.x = (SCREEN_WIDTH - quit.surface->w) / 2;
    highscores.x = (SCREEN_WIDTH - highscores.surface->w) / 2;
    boss_button.x = (SCREEN_WIDTH - boss_button.surface->w) / 2;

    text_rect.x = singleplayer.x;
    text_rect.y = singleplayer.y;
    SDL_BlitSurface(singleplayer.surface, NULL, screen, &text_rect);

    text_rect.x = quit.x;
    text_rect.y = quit.y;
    SDL_BlitSurface(quit.surface, NULL, screen, &text_rect);

    text_rect.x = highscores.x;
    text_rect.y = highscores.y;
    SDL_BlitSurface(highscores.surface, NULL, screen, &text_rect);

    text_rect.x = boss_button.x;
    text_rect.y = boss_button.y;
    SDL_BlitSurface(boss_button.surface, NULL, screen, &text_rect);
}
