#ifndef MAIN_H
#define MAIN_H

#include "utils.h"
#include "dog.h"
#include "duck.h"
#include "menu.h"
#include "level.h"
#include "boss.h"


enum Display
{
    MENU,
    GAME,
    GAME_OVER
};

enum GameState
{
    DOG,
    LEVEL,
    DUCK,
    BOSS
};

void processDog(SDL_Surface *screen, Dog &dog);
void processDuck(SDL_Surface *screen, Duck &duck);


#endif
