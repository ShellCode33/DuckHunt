#ifndef BOSS_H
#define BOSS_H

#include "utils.h"

#define NB_FLOOR 4

void initBoss(SDL_Surface* entity_sprites, Boss &boss, int current_wave);
void displayBoss(SDL_Surface* screen, Boss &boss, SDL_Surface *boss_bg[]);
int processBoss(Boss &boss, int index_dog, int current_wave);
void moveBoss(Boss &boss, int index_dog);
int killBoss(Boss &boss, int x_mouse, int y_mouse);
void deleteBoss(Boss &boss);

#endif //BOSS_H
