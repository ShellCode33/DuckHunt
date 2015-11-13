#ifndef DUCK_H
#define DUCK_H

struct Duck
{
    Sprite *sprite;
    int speed;      //vitesse du canard
    int nbr_sprite; //nbr d'images qui va composer l'animation
};

#endif
