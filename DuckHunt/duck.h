#ifndef DUCK_H
#define DUCK_H

#include "utils.h"

void initDuck(SDL_Surface* entity_sprites, Duck &duck);
void processDuck(SDL_Surface *screen, Duck &duck);
void moveDuck(Duck &duck);
void showDuck(SDL_Surface *screen, Duck &duck);
void deleteDuck(Duck &duck);

#endif
