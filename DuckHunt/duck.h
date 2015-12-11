#ifndef DUCK_H
#define DUCK_H

#include "utils.h"

void initDuck(SDL_Surface* entity_sprites, Duck &duck, int levels[][3], int current_level);
void processDuck(SDL_Surface *screen, Duck &duck);
void moveDuck(Duck &duck);
void showDuck(SDL_Surface *screen, Duck &duck);
void deleteDuck(Duck &duck);
void duckRandTrajectory (Duck &duck, bool colTopBottom, bool colLeftRight);
bool killDuck(Duck &duck, SDL_Event &event);
void changeDuckAnimation(Duck &duck, int anim_type);
void fadeOutDuck(Duck &duck, SDL_Surface* screen);
void displayDuckScore(Duck &duck,Score &duckScore, SDL_Surface* screen);

#endif
