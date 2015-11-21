#ifndef DOG_H
#define DOG_H

#include "utils.h"

void initDog(SDL_Surface* entity_sprites, Dog &dog);
void moveDog(Dog &dog);
void showDog(SDL_Surface *screen, Dog &dog);
void changeDogAnimation(Dog &dog, int anim_type);
void deleteDog(Dog &dog);
void processDog(SDL_Surface *screen, Dog &dog);

#endif
