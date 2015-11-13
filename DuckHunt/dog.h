#ifndef DOG_H
#define DOG_H

#include "utils.h"

struct Dog
{
    Sprite *sprite;
    int nbr_sprite;
    int mvt_x;
    int mvt_y;
};

void initDog(SDL_Surface* entity_sprites, Dog &dog);
void moveDog(Dog &dog);
void showDog(SDL_Surface *screen, Dog &dog);
void changeDogStat(Dog &dog);

#endif
