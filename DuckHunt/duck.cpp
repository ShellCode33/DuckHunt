#include "duck.h"

void initDuck(SDL_Surface* entity_sprites, Duck &duck)
{
    duck.sprite = new Sprite;
    duck.sprite->img = entity_sprites;
    duck.nbr_sprite = 9;
    duck.sprite->h = 66;
    duck.sprite->w = 60;
    duck.sprite->x = rand() % (SCREEN_WIDTH - duck.sprite->w);
    duck.sprite->y = rand() % (SCREEN_HEIGHT - duck.sprite->h);
}
