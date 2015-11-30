#ifndef DUCK_H
#define DUCK_H

#include "utils.h"

void initDuck(SDL_Surface* entity_sprites, Duck &duck);
void processDuck(SDL_Surface *screen, Duck &duck);
void moveDuck(Duck &duck);
void showDuck(SDL_Surface *screen, Duck &duck);
void deleteDuck(Duck &duck);
void duckRandTrajectory (Duck &duck, bool colTopBottom, bool colLeftRight);
void killDuck(Duck &duck, SDL_Event &event, int &bullet_left);
void changeDuckAnimation(Duck &duck, int anim_type);

#endif
