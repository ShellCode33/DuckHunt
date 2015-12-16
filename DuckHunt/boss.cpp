#include "boss.h"

void initBoss(SDL_Surface* entity_sprites, Boss &boss)
{
    int i;
    for(i = 0; i < NB_DOG_BOSS_LEVEL; i++)
    {
        boss.dogs[i] = new Dog;
        boss.dogs[i]->nbr_sprite = 1;
        boss.dogs[i]->sprite = new Sprite;
        boss.dogs[i]->sprite->rect_dst = new SDL_Rect;
        boss.dogs[i]->sprite->rect_src = new SDL_Rect;
        boss.dogs[i]->sprite->img = entity_sprites;

        boss.dogs[i]->sprite->rect_src->x = 707;
        boss.dogs[i]->sprite->rect_src->y = 24;
        boss.dogs[i]->sprite->w = boss.dogs[i]->sprite->rect_src->w = boss.dogs[i]->sprite->rect_dst->w = 60;
        boss.dogs[i]->sprite->h = boss.dogs[i]->sprite->rect_src->h = boss.dogs[i]->sprite->rect_dst->h = 78;

        boss.dogs[i]->sprite->x = boss.dogs[i]->sprite->rect_dst->x = 23 + (boss.dogs[i]->sprite->w+20) * i;
        boss.dogs[i]->sprite->y = boss.dogs[i]->sprite->rect_dst->y = 110;

        boss.floor[i] = 0;
        boss.dogs[i]->cooldown = 80;
        boss.dead[i] = false;
    }
}

void displayBoss(SDL_Surface *screen, Boss &boss, SDL_Surface *boss_bg[])
{
    SDL_BlitSurface(boss_bg[0], NULL, screen, NULL);

    int i, j;
    for(i = 0; i < NB_FLOOR; i++) //pour chaque étage on affiche les chiens qui doivent être là
    {
        for(j = 0; j < NB_DOG_BOSS_LEVEL; j++) //On affiche tous les chiens sur cet étage
        {
            if(boss.floor[j] == i && !boss.dead[j])
                SDL_BlitSurface(boss.dogs[j]->sprite->img, boss.dogs[j]->sprite->rect_src, screen, boss.dogs[j]->sprite->rect_dst);
        }

        SDL_BlitSurface(boss_bg[i+1], NULL, screen, NULL);
    }
}

void moveBoss(Boss &boss, int dog_index)
{
    boss.dogs[dog_index]->sprite->rect_dst->y += boss.dogs[dog_index]->mvt_y;
    boss.dogs[dog_index]->sprite->y = boss.dogs[dog_index]->sprite->rect_dst->y;
    boss.dogs[dog_index]->mvt_y = 0;
}

int processBoss(Boss &boss, int dog_index)
{
    if(boss.dogs[dog_index]->cooldown > 60)
    {
        boss.dogs[dog_index]->mvt_y = -1;
    }

    else if(boss.dogs[dog_index]->cooldown > 0)
    {
        boss.dogs[dog_index]->mvt_y = 1;
    }

    if(boss.dogs[dog_index]->cooldown > 0)
        boss.dogs[dog_index]->cooldown--;

    else
    {
        //les lignes qui suivent correspondent à une changement d'étage
        boss.dogs[dog_index]->cooldown = 80;
        boss.floor[dog_index]++;
        boss.dogs[dog_index]->sprite->rect_dst->y = 110*(boss.floor[dog_index]+1);
    }

    if(boss.floor[dog_index] >= NB_FLOOR)
        return 1; //game over

    return 0;
}

int killBoss(Boss &boss, int x_mouse, int y_mouse)
{
    int index = x_mouse / (boss.dogs[0]->sprite->w+20);
    int floor = y_mouse / 110;

    if(index > NB_DOG_BOSS_LEVEL-1 || index < 0 || floor < 0 || floor > NB_FLOOR)
        return 0;

    if(!boss.dead[index] && x_mouse > boss.dogs[index]->sprite->x && x_mouse < boss.dogs[index]->sprite->x+boss.dogs[index]->sprite->w && y_mouse > boss.dogs[index]->sprite->y && y_mouse < boss.dogs[index]->sprite->y+boss.dogs[index]->sprite->h)
    {
        boss.dead[index] = true;
        return 1;
    }

    return 0;
}
