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
        boss.dogs[i]->sprite->rect_src->w = boss.dogs[i]->sprite->rect_dst->w = 60;
        boss.dogs[i]->sprite->rect_src->h = boss.dogs[i]->sprite->rect_dst->h = 78;
        boss.floor[i] = 0;
    }
}
