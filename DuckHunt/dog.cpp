#include "dog.h"

void initDog(SDL_Surface* entity_sprites, Dog &dog)
{
    dog.isComing = true;
    dog.isJumping = false;
    dog.cooldown = 0;

    dog.sprite = new Sprite;
    dog.sprite->img = entity_sprites;
    dog.nbr_sprite = 5; //dans un premier temps on met à 5 car au début du jeu lorsque le chien arrive, il n'y a que 5 animations différentes
    dog.sprite->h = 94;
    dog.sprite->w = 114;
    dog.sprite->x = 0;
    dog.sprite->y = 590 - dog.sprite->h / 2; //590 = position où doit être le chien sur l'écran

    dog.sprite->rect_src = new SDL_Rect;
    dog.sprite->rect_src->h = dog.sprite->h;
    dog.sprite->rect_src->w = dog.sprite->w;
    dog.sprite->rect_src->x = 5;
    dog.sprite->rect_src->y = 0;

    dog.sprite->rect_dst = new SDL_Rect;
    dog.sprite->rect_dst->h = dog.sprite->h;
    dog.sprite->rect_dst->w = dog.sprite->w;
    dog.sprite->rect_dst->x = dog.sprite->x - dog.sprite->w / 2;
    dog.sprite->rect_dst->y = dog.sprite->y - dog.sprite->h / 2;
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

    if(dog.nbr_sprite > 1)
    {
        dog.sprite->rect_src->x += dog.sprite->w;
        dog.sprite->rect_src->x %= (dog.sprite->w * dog.nbr_sprite);
    }
}

void changeDogAnimation(Dog &dog, int anim_type)
{
    switch(anim_type)
    {
        case 1: //waiting
            dog.nbr_sprite = 1;
            dog.sprite->rect_src->x = 0;
            dog.sprite->rect_src->y = 110;
            dog.sprite->h = 120;
            dog.sprite->w = 117;
            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            break;

        case 2: //jumping 1
            dog.nbr_sprite = 1;
            dog.sprite->rect_src->x = 125;
            dog.sprite->rect_src->y = 110;
            dog.sprite->h = 110;
            dog.sprite->w = 75;
            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            break;

        case 3: //jumping 2
            dog.nbr_sprite = 1;
            dog.sprite->rect_src->x = 210;
            dog.sprite->rect_src->y = 110;
            dog.sprite->h = 110;
            dog.sprite->w = 75;
            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            break;
    }
}

void deleteDog(Dog &dog)
{
    delete dog.sprite->rect_dst;
    delete dog.sprite->rect_src;
    delete dog.sprite;
}
