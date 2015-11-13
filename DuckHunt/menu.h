#ifndef MENU_H
#define MENU_H

#include "utils.h"

void showMenu(SDL_Surface* screen, SDL_Surface* menu_img, TTF_Font* small_font, TTF_Font* big_font, Button &singleplayer, Button &quit);
void detectKeyboardMenu(Button &singleplayer, Button &quit);

#endif
