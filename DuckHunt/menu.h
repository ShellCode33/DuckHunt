#ifndef MENU_H
#define MENU_H

#include "utils.h"

void showMenu(SDL_Surface* screen, SDL_Surface* menu_img, TTF_Font* small_font, TTF_Font* big_font, Button &singleplayer, Button &quit, Button &highscores, Button &boss_button);
int detectMouseMenu(Button &singleplayer, Button &quit, Button &boss, Button &highscores, SDL_Event &event);

#endif
