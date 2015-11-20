#ifndef MAIN_H
#define MAIN_H

#include "utils.h"
#include "dog.h"
#include "duck.h"
#include "menu.h"

enum Display
{
    MENU,
    GAME
};

void processDog(SDL_Surface *screen, Dog &dog);
void processDuck(SDL_Surface *screen, Duck &duck);


#endif
