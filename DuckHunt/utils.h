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
#include <fstream>
using namespace std;

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 761
#define SCREEN_BPP 32

#define NB_DUCK_PER_LEVEL 10
#define NB_DOG_BOSS_LEVEL 9

#define MAX_LENGTH_USERNAME 10

struct Sprite
{
    int x;
    int y;
    int w;
    int h;
    int x_src; //Origine/Début de l'animation
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
    bool displayed; //si le canard est affiché à l'écran
    bool flee;
    bool dead; //utilisé pour l'affichage tués dans la barre en bas de l'écran
    int cooldown;
};

struct Dog
{
    Sprite *sprite;
    int nbr_sprite;
    int mvt_x;
    int mvt_y;
    int state; //1 = isComing  2 = isJumping 3 = isWaiting 4 = isShowingDucks
    int cooldown; //cooldown utilisé à plusieurs moments afin de faire attendre le chien
};

struct DuckScore
{
    int cooldown;
    Sprite *sprite;
    int alpha;
};

struct Boss
{
    Dog *dogs[NB_DOG_BOSS_LEVEL];
    int floor[NB_DOG_BOSS_LEVEL]; //étage d'herbe où se trouve le chien 0=en haut, 1=au dessous, 2=etc... 3=tout en bas, 4=gameover=chien qui rigole en gros
    int index[NB_DOG_BOSS_LEVEL]; //place sur l'étage
    bool dead[NB_DOG_BOSS_LEVEL];
};

struct Player
{
    string name;
    int score;
};

SDL_Surface* loadImageWithColorKey(const char* filename, bool colorkey, int r, int g, int b);
void displayBulletLeft(SDL_Surface *screen, SDL_Surface *bullet_img, int bullet_left);
void displayScore(SDL_Surface *screen, TTF_Font* font, int score, int mode);
void displayDuckHit(SDL_Surface *screen, Duck duck[], int current_wave, SDL_Surface *duck_hit_img);
void sortBestScores(Player bestScores[], Player lastPlayer);
void createFile();
bool doesFileExists (char* name);

#endif
