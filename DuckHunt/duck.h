#ifndef DUCK_H
#define DUCK_H

#include "utils.h"

struct Duck
{
    Sprite *sprite;
    int speed;      //vitesse du canard
    int nbr_sprite; //nbr d'images qui va composer l'animation
    int mvt_x;
    int mvt_y;
    bool collision;
};

void initDuck(SDL_Surface* entity_sprites, Duck &duck);
void processDuck(SDL_Surface *screen, Duck &duck);
void moveDuck(Duck &duck);
void showDuck(SDL_Surface *screen, Duck &duck);
void deleteDuck(Duck &duck);




#endif
