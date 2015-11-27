#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <stdio.h>
#include <string>
using namespace std;

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 761
#define SCREEN_BPP 32

#define NB_DUCK_PER_LEVEL 10

struct Sprite
{
    int x;
    int y;
    int w;
    int h;
    SDL_Surface *img;
    SDL_Rect *rect_src;
    SDL_Rect *rect_dst;
};

struct Button
{
    bool select;
    SDL_Surface* surface;
    int x;
    int y;
};

struct Duck
{
    Sprite *sprite;
    float speed;      //vitesse du canard
    int nbr_sprite; //nbr d'images qui va composer l'animation
    int type;
    int mvt_x;
    int mvt_y;
    bool collision;
    bool dead; //utilisé pour l'affichage tués dans la barre en bas de l'écran
};

struct Dog
{
    Sprite *sprite;
    int nbr_sprite;
    int mvt_x;
    int mvt_y;
    bool isComing; //En début de jeu, lorsque le chien arrive
    bool isJumping; //Lorsque le chien arrive au milieu de l'écran, il va sauter dans l'herbe; ce boolean est donc définit pour
    bool isWaiting;
    int cooldown; //cooldown utilisé à plusieurs moments afin de faire attendre le chien
};

SDL_Surface* loadImageWithColorKey(const char* filename, bool colorkey, int r, int g, int b);
void displayBulletLeft(SDL_Surface *screen, SDL_Surface *bullet_img, int bullet_left);
void displayScore(SDL_Surface *screen, TTF_Font* font, int score);
void displayDuckHit(SDL_Surface *screen, Duck duck[], int current_wave, SDL_Surface *duck_hit_img);

#endif
