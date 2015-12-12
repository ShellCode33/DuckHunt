#include "duck.h"

void initDuck(SDL_Surface* entity_sprites, Duck &duck, int levels[][3], int current_level)
{
    duck.sprite = new Sprite;
    duck.sprite->img = entity_sprites;
    duck.nbr_sprite = 3;
    duck.cooldown = 11;
    duck.sprite->x_src = 0;
    duck.sprite->h = 68;
    duck.sprite->w = 68;
    duck.sprite->x = rand() % (SCREEN_WIDTH - duck.sprite->w);
    duck.sprite->y = rand() % (SCREEN_HEIGHT/2 + 120 -duck.sprite->h/2);

    duck.sprite->rect_src = new SDL_Rect;
    duck.sprite->rect_src->h = duck.sprite->h;
    duck.sprite->rect_src->w = duck.sprite->w;
    duck.sprite->rect_src->x = 12;

    //init duck type

    int random_duck = rand()%3;

    while(levels[current_level-1][random_duck] <= 0)
        random_duck = (random_duck+1) % 3;

    duck.type = random_duck;
    levels[current_level-1][random_duck]--; //on enlève le canard du level

    //--------------



    if(duck.type == 0)
    {
        duck.sprite->rect_src->y = 227;
        duck.speed = 1.0;
    }

    else if(duck.type == 1)
    {
        duck.sprite->rect_src->y = 316;
        duck.speed = 1.5;
    }

    else if(duck.type == 2)
    {
        duck.sprite->rect_src->y = 402;
        duck.speed = 2.0;
    }

    duck.sprite->rect_dst = new SDL_Rect;
    duck.sprite->rect_dst->h = duck.sprite->h;
    duck.sprite->rect_dst->w = duck.sprite->w;
    duck.sprite->rect_dst->x = duck.sprite->x;
    duck.sprite->rect_dst->y = duck.sprite->y;

    duck.dead = false;
    duck.displayed = true;
    duck.flee = false;

    duckRandTrajectory(duck, false, false);
}




/*
 *
 *                      CETTE PUTAIN DE FONCTION EST A REFAIRE ENTIEREMENT !!!
 *                                              |
 *                                              |
 *                                              |
 *                                              |
 *                                              |
 *                                              |
 *                                              |
 *                                              |
 *                                              |
 *                                              V
 */

void duckRandTrajectory(Duck &duck, bool colTopBottom, bool colLeftRight)
{
    int trajectoires[] = {1, 2, 3, 4, 5, 6};
    int direction[]= {-1, 1};

    //Si le canard est en train de fuire, on désactive les collisions
    if(!duck.flee)
    {
        if (colLeftRight)
        {
            if (duck.sprite->x > SCREEN_WIDTH/2)
            {
                duck.mvt_x=trajectoires[rand()%sizeof(trajectoires)/sizeof(int)]*direction[0];
                duck.mvt_y=direction[rand()%sizeof(direction)/sizeof(int)]*(7+duck.mvt_x);
            }
            else if (duck.sprite->x < SCREEN_WIDTH/2)
            {
                duck.mvt_x=trajectoires[rand()%sizeof(trajectoires)/sizeof(int)]*direction[1];
                duck.mvt_y=direction[rand()%sizeof(direction)/sizeof(int)]*(7-duck.mvt_x);
            }
        }

        else if (colTopBottom)
        {
            if (duck.sprite->y > SCREEN_HEIGHT/3)
            {
                duck.mvt_y=trajectoires[rand()%sizeof(trajectoires)/sizeof(int)]*direction[0];
                duck.mvt_x=direction[rand()%sizeof(direction)/sizeof(int)]*(7+duck.mvt_y);
            }
            else if (duck.sprite->y < SCREEN_HEIGHT/2)
            {
                duck.mvt_y=trajectoires[rand()%sizeof(trajectoires)/sizeof(int)]*direction[1];
                duck.mvt_x=direction[rand()%sizeof(direction)/sizeof(int)]*(7-duck.mvt_y);
            }
        }

        else if (!colTopBottom && !colLeftRight)
        {
            duck.mvt_x=trajectoires[rand()%sizeof(trajectoires)/sizeof(int)]*direction[rand()%sizeof(direction)/sizeof(int)];

            if (duck.mvt_x > 0)
                duck.mvt_y=direction[rand()%sizeof(direction)/sizeof(int)]*(7-duck.mvt_x);

            else if (duck.mvt_x < 0)
                duck.mvt_y=direction[rand()%sizeof(direction)/sizeof(int)]*(7+duck.mvt_x);
        }
    }
}

void processDuck(SDL_Surface *screen, Duck &duck)
{
    bool colTopBottom = false; //colllision en haut et en bas de l'ecran
    bool colLeftRight = false; //collision a gauche et a droite de l'ecran

    if(duck.dead && duck.cooldown > 0)
        duck.cooldown--;

    else if(duck.dead && duck.cooldown == 0 )
    {
        changeDuckAnimation(duck, 2);
        duck.cooldown = -1; //on rend le cooldown inactif.
    }

    else if (duck.dead && duck.sprite->y > SCREEN_HEIGHT - SCREEN_HEIGHT/4) //Si le canard est mort, il ne s'affiche plus à partir de l'herbe (d'où le return)
    {
        duck.displayed = false;
        return;
    }

    if (duck.sprite->x>(SCREEN_WIDTH-duck.sprite->w/2))
    {
        colTopBottom = false;
        colLeftRight = true;
        duckRandTrajectory(duck, colTopBottom, colLeftRight);
    }

    else if (duck.sprite->x<duck.sprite->w/2)
    {
        colTopBottom = false;
        colLeftRight = true;
        duckRandTrajectory(duck, colTopBottom, colLeftRight);
    }

    else if (duck.sprite->y>SCREEN_HEIGHT/2 + 120 -duck.sprite->h/2 && !duck.dead)
    {
        colTopBottom = true;
        colLeftRight = false;
        duckRandTrajectory(duck, colTopBottom, colLeftRight);
    }

    else if (duck.sprite->y<duck.sprite->h/2)
    {
        colTopBottom = true;
        colLeftRight = false;
        duckRandTrajectory(duck, colTopBottom, colLeftRight);
    }

    moveDuck(duck);
    showDuck(screen, duck);
}

bool killDuck(Duck &duck, SDL_Event &event)
{
    if(event.motion.x < duck.sprite->x + duck.sprite->w/2 && event.motion.x > duck.sprite->x - duck.sprite->w/2 && event.motion.y < duck.sprite->y + duck.sprite->h/2 && event.motion.y > duck.sprite->y - duck.sprite->h/2)
        duck.dead = true;

    if (duck.dead)
    {
        duck.cooldown--;
        if (duck.cooldown == 10 )
            changeDuckAnimation(duck, 1);
    }

    return duck.dead;
}

void moveDuck(Duck &duck)
{
    if(duck.mvt_y == 0)

    duck.sprite->x += duck.mvt_x * duck.speed;
    duck.sprite->y += duck.mvt_y * duck.speed;

    duck.sprite->rect_dst->x = duck.sprite->x - duck.sprite->w / 2;
    duck.sprite->rect_dst->y = duck.sprite->y - duck.sprite->h / 2;
}

void showDuck(SDL_Surface *screen, Duck &duck)
{
        SDL_BlitSurface(duck.sprite->img, duck.sprite->rect_src, screen, duck.sprite->rect_dst);

        if(duck.nbr_sprite>1)
        {
            duck.sprite->rect_src->x += duck.sprite->w;
            duck.sprite->rect_src->x %= (duck.sprite->x_src + duck.sprite->w * duck.nbr_sprite);

            if(duck.sprite->rect_src->x < duck.sprite->x_src)
                duck.sprite->rect_src->x += duck.sprite->x_src;
        }
}

void changeDuckAnimation(Duck &duck, int anim_type)
{
    switch(anim_type)
    {
        case 1: //when the duck dies
            duck.speed = 1.0; //reset de la vitesse
            duck.sprite->rect_src->x = 450;
            //duck.sprite->rect_src->y = 240;
            duck.sprite->h = 80;
            duck.sprite->rect_src->h = duck.sprite->h;
            duck.nbr_sprite = 1;
            duck.sprite->x_src = 450;
            duck.mvt_x = 0;
            duck.mvt_y = 0;
            break;

        case 2: //when the duck falls
            duck.mvt_x = 0;
            duck.mvt_y = 0;
            duck.nbr_sprite = 2;
            duck.sprite->x_src = duck.sprite->rect_src->x = 532;
            //duck.sprite->rect_src->y = 246;
            duck.sprite->w = 48;
            duck.sprite->h = 80;
            duck.sprite->rect_src->h = duck.sprite->h;
            duck.sprite->rect_src->w = duck.sprite->w;
            duck.mvt_y = 15;
            break;
    }
}

void displayDuckScore(Duck &duck, DuckScore &duckScore, SDL_Surface* screen)
{
    if(duckScore.cooldown >= 42)
    {
        if(duck.sprite->x < SCREEN_WIDTH/2)
        {
            duckScore.sprite->rect_dst->x = duck.sprite->x + duck.sprite->w/2;
            duckScore.sprite->rect_dst->y = duck.sprite->y + 10;
        }
        else
        {
            duckScore.sprite->rect_dst->x = duck.sprite->x - duck.sprite->w;
            duckScore.sprite->rect_dst->y = duck.sprite->y - 10;
        }

    }

    else
    {
        duckScore.sprite->rect_dst->y -= 1;
    }

    duckScore.sprite->rect_src->x = 0;
    duckScore.sprite->rect_src->w = 40;
    duckScore.sprite->rect_src->h = 14;

    if(duck.type == 0)
        duckScore.sprite->rect_src->y = 42;

    else if(duck.type == 1)
        duckScore.sprite->rect_src->y = 26;

    else
        duckScore.sprite->rect_src->y = 10;

    SDL_SetAlpha(duckScore.sprite->img, SDL_SRCALPHA | SDL_RLEACCEL, duckScore.alpha); //disparition progressive
    SDL_BlitSurface(duckScore.sprite->img, duckScore.sprite->rect_src, screen, duckScore.sprite->rect_dst);
}

void fadeOutDuck(Duck &duck)
{
    duck.flee = true;
    duck.mvt_x = 3;
    duck.mvt_y = -3;

    if(duck.sprite->x-duck.sprite->w/2 > SCREEN_WIDTH || duck.sprite->y+duck.sprite->h/2 < 0)
        duck.displayed = false;
}


void deleteDuck(Duck &duck)
{
    delete duck.sprite->rect_dst;
    delete duck.sprite->rect_src;
    delete duck.sprite;
}
