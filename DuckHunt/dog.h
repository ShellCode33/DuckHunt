#ifndef DOG_H
#define DOG_H

#include "utils.h"

struct Dog
{
    Sprite *sprite;
    int nbr_sprite;
    int mvt_x;
    int mvt_y;
    bool isComing; //En début de jeu, lorsque le chien arrive
    bool isJumping; //Lorsque le chien arrive au milieu de l'écran, il va sauter dans l'herbe; ce boolean est donc définit pour
    bool isWaiting;
    int cooldown; //cooldown utilisé à plusieurs moments afin de faire attendre le chien
};

void initDog(SDL_Surface* entity_sprites, Dog &dog);
void moveDog(Dog &dog);
void showDog(SDL_Surface *screen, Dog &dog);
void changeDogAnimation(Dog &dog, int anim_type);
void deleteDog(Dog &dog);

#endif
