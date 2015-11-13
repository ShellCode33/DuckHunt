#include "dog.h"

void initDog(SDL_Surface* entity_sprites, Dog &dog)
{
    dog.sprite = new Sprite;
    dog.sprite->img = entity_sprites;
    dog.nbr_sprite = 5; //dans un premier temps on met à 5 car au début du jeu lorsque le chien arrive, il n'y a que 5 animations différentes
    dog.sprite->h = 94;
    dog.sprite->w = 114;
    dog.sprite->x = 0;
    dog.sprite->y = SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 5;

    dog.sprite->rect_src = new SDL_Rect;
    dog.sprite->rect_src->h = dog.sprite->h;
    dog.sprite->rect_src->w = dog.sprite->w;
    dog.sprite->rect_src->x = 0;
    dog.sprite->rect_src->y = 0;

    dog.sprite->rect_dst = new SDL_Rect;
    dog.sprite->rect_dst->h = dog.sprite->h;
    dog.sprite->rect_dst->w = dog.sprite->w;
    dog.sprite->rect_dst->x = dog.sprite->x;
    dog.sprite->rect_dst->y = dog.sprite->y;
}

void moveDog(Dog &dog)
{
    dog.sprite->x += dog.mvt_x;
    dog.sprite->y += dog.mvt_y;

    dog.sprite->rect_dst->x = dog.sprite->x - dog.sprite->w / 2;
    dog.sprite->rect_dst->y = dog.sprite->y - dog.sprite->h / 2;

    dog.mvt_x = dog.mvt_y = 0; //reset le mouvement
}

void showDog(SDL_Surface *screen, Dog &dog)
{
    SDL_BlitSurface(dog.sprite->img, dog.sprite->rect_src, screen, dog.sprite->rect_dst);

    dog.sprite->rect_src->x += dog.sprite->w;
    dog.sprite->rect_src->x %= dog.sprite->w * (dog.nbr_sprite-1);
}

void changeDogStat(Dog &dog)
{
    //Pas encore implémenté
    //change l'état du chien en fonction de si il arrive au début, si il montre les canard tués, si il saute dans l'herbe etc...
}
