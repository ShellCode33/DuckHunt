#include "dog.h"

void initDog(SDL_Surface* entity_sprites, Dog &dog)
{
    dog.state = 1;
    dog.cooldown = 0;

    dog.sprite = new Sprite;
    dog.sprite->img = entity_sprites;
    dog.nbr_sprite = 5; //dans un premier temps on met à 5 car au début du jeu lorsque le chien arrive, il n'y a que 5 animations différentes
    dog.sprite->h = 94;
    dog.sprite->w = 114;
    dog.sprite->x = 0;
    dog.sprite->y = 590 - dog.sprite->h / 2; //590 = position où doit être le chien sur l'écran

    dog.sprite->x_src = 5;

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

    dog.mvt_x = 0;
    dog.mvt_y = 0;
}

void processDog(SDL_Surface *screen, Dog &dog)
{
    switch(dog.state)
    {
        case 1: //isComing
        {
            dog.mvt_x = 7;
            moveDog(dog);
            showDog(screen, dog);

            SDL_Delay(30); //On rajoute un delai supplémentaire quand le chien arrive, c'est le début du jeu

            if(dog.sprite->x >= SCREEN_WIDTH/2)
            {
                changeDogAnimation(dog, 1);
                dog.state = 2;
            }

            break;
        }

        case 2: //isWaiting
        {
            moveDog(dog);
            showDog(screen, dog);

            dog.cooldown--;

            if(dog.cooldown <= 0)
            {
                changeDogAnimation(dog, 2);
                dog.state = 3;
            }

            break;
        }

        case 3: //isJumping
        {
            dog.mvt_y = -5;
            dog.mvt_x = 3;

            if(dog.cooldown == 8)
                changeDogAnimation(dog, 3);

            if(dog.cooldown > 0)
                dog.cooldown--;

            else
               dog.state = 0;

            moveDog(dog);
            showDog(screen, dog);

            SDL_Delay(10);

            break;
        }

        case 4: //isShowingDucks
        case 5: //isLaughing
        {
            if(dog.cooldown > 50)
                dog.mvt_y = -3;

            else if(dog.cooldown > 0 && dog.cooldown < 25)
                dog.mvt_y = 3;

            if(dog.cooldown <= 0)
                dog.state = 0;

            else
            {
                moveDog(dog);
                showDog(screen, dog);
            }

            dog.cooldown--;
            SDL_Delay(35);

            break;
        }
    }
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
        dog.sprite->rect_src->x %= (dog.sprite->x_src + dog.sprite->w * dog.nbr_sprite);

        if(dog.sprite->rect_src->x < dog.sprite->x_src)
            dog.sprite->rect_src->x += dog.sprite->x_src;
    }
}

void changeDogAnimation(Dog &dog, int anim_type)
{
    switch(anim_type)
    {
        case 0:
            dog.nbr_sprite = 5; //dans un premier temps on met à 5 car au début du jeu lorsque le chien arrive, il n'y a que 5 animations différentes
            dog.sprite->h = 94;
            dog.sprite->w = 114;
            dog.sprite->x = 0;
            dog.sprite->y = 590 - dog.sprite->h / 2; //590 = position où doit être le chien sur l'écran

            dog.sprite->x_src = 5;

            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            dog.sprite->rect_src->x = 5;
            dog.sprite->rect_src->y = 0;
            break;

        case 1: //waiting
            dog.nbr_sprite = 1;
            dog.sprite->rect_src->x = 0;
            dog.sprite->rect_src->y = 110;
            dog.sprite->h = 120;
            dog.sprite->w = 117;
            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            dog.cooldown = 50;
            dog.sprite->x_src = dog.sprite->rect_src->x;
            break;

        case 2: //jumping 1
            dog.nbr_sprite = 1;
            dog.sprite->rect_src->x = 125;
            dog.sprite->rect_src->y = 110;
            dog.sprite->h = 110;
            dog.sprite->w = 75;
            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            dog.cooldown = 12;
            dog.sprite->x_src = dog.sprite->rect_src->x;
            break;

        case 3: //jumping 2
            dog.nbr_sprite = 1;
            dog.sprite->rect_src->x = 210;
            dog.sprite->rect_src->y = 110;
            dog.sprite->h = 110;
            dog.sprite->w = 75;
            dog.sprite->rect_src->h = dog.sprite->h;
            dog.sprite->rect_src->w = dog.sprite->w;
            dog.sprite->x_src = dog.sprite->rect_src->x;
            break;

        case 4: //showing ducks
            dog.nbr_sprite = 1;
            dog.sprite->x = SCREEN_WIDTH / 2;
            dog.sprite->y = 590;
            dog.sprite->rect_src->x = 305; //sera redéfinit quoi qu'il arrive en fonction du type de canard tué
            dog.sprite->rect_src->y = 125;
            dog.sprite->h = dog.sprite->rect_src->h = 85;
            dog.sprite->w = dog.sprite->rect_src->w = 90;
            dog.cooldown = 88;
            dog.sprite->x_src = dog.sprite->rect_src->x;
            break;

        case 5: //laughing
            dog.nbr_sprite = 2;
            dog.sprite->x = SCREEN_WIDTH / 2;
            dog.sprite->y = 590;
            dog.sprite->rect_src->x = 580;
            dog.sprite->rect_src->y = 24;
            dog.sprite->h = dog.sprite->rect_src->h = 76;
            dog.sprite->w = dog.sprite->rect_src->w = 62;
            dog.cooldown = 88;
            dog.sprite->x_src = dog.sprite->rect_src->x;
            break;
    }
}

void deleteDog(Dog &dog)
{
    delete dog.sprite->rect_dst;
    delete dog.sprite->rect_src;
    delete dog.sprite;
}
