#include "utils.h"

SDL_Surface* loadImageWithColorKey(const char* filename, bool colorkey, int r, int g, int b)
{
    SDL_Surface* optimizedImage = NULL;
    SDL_Surface* loadedImage = IMG_Load(filename);

    if(loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL && colorkey)
        {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, r, g, b);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }

    return optimizedImage;
}

void displayBulletLeft(SDL_Surface *screen, SDL_Surface *bullet_img, int bullet_left)
{
    SDL_Rect rect_src, rect_dst;

    rect_dst.x = 65;
    rect_dst.y = 657;
    rect_dst.w = 76;
    rect_dst.h = 50;

    rect_src.w = rect_dst.w;
    rect_src.h = rect_dst.h;
    rect_src.x = 1*(bullet_left+1) + rect_src.w*bullet_left;
    rect_src.y = 1;

    SDL_BlitSurface(bullet_img, &rect_src, screen, &rect_dst);
}

void displayScore(SDL_Surface *screen, TTF_Font *font, int score, int mode)
{
    SDL_Color blackcolor = {0, 0, 0, 0};
    SDL_Color whitecolor = {255, 255, 255, 0};

    string score_str = "";

    if(mode == 2)
        score_str += "Score: ";

    score_str += to_string(score);

    SDL_Surface *text_score = TTF_RenderText_Shaded(font, score_str.c_str(), whitecolor, blackcolor);

    SDL_Rect rect_dst;

    if(mode == 1) //mode 1 correspond au mode de jeu normal
        rect_dst.x = 560;

    else if(mode == 2) //mode 2 correspond au boss
        rect_dst.x = (SCREEN_WIDTH-text_score->w) / 2;

    rect_dst.y = 683 - text_score->h / 2;
    rect_dst.w = text_score->w;
    rect_dst.h = text_score->h;
    SDL_BlitSurface(text_score, NULL, screen, &rect_dst);
}

void displayDuckHit(SDL_Surface *screen, Duck duck[], int current_wave, SDL_Surface *duck_hit_img)
{
    SDL_Rect dst_rect, src_rect;
    src_rect.x = 9;
    src_rect.y = 8;
    src_rect.w = 21;
    src_rect.h = 21;

    dst_rect.x = 190;
    dst_rect.y = 660;
    dst_rect.w = 21;
    dst_rect.h = 21;

    int i;
    for(i = 0; i < (current_wave-1)*2; i++)
    {
        if(duck[i].dead)
        {
            src_rect.x = 9 + 2*src_rect.w + 6;
            SDL_BlitSurface(duck_hit_img, &src_rect, screen, &dst_rect); //green duck
        }

        else
        {
            src_rect.x = 9 + src_rect.w + 3;
            SDL_BlitSurface(duck_hit_img, &src_rect, screen, &dst_rect); //red duck
        }

        dst_rect.x += dst_rect.w + 3;;
    }


    for(; i < current_wave*2; i++)
    {
        if(duck[i].dead)
        {
            src_rect.x = 9 + 2*src_rect.w + 6;
            SDL_BlitSurface(duck_hit_img, &src_rect, screen, &dst_rect); //green duck
        }

        else
        {
            src_rect.x = 9;
            SDL_BlitSurface(duck_hit_img, &src_rect, screen, &dst_rect); //display white duck
        }

        dst_rect.x += dst_rect.w + 3;
    }

    src_rect.x = 9;

    for(; i < NB_DUCK_PER_LEVEL; i++)
    {
        SDL_BlitSurface(duck_hit_img, &src_rect, screen, &dst_rect); //display white duck
        dst_rect.x += dst_rect.w + 3;
    }
}

//void sortBestScores(Player bestScores[], Player lastPlayer) //pas encore fonctionnel
//{
//    int i =0;
//    bool asChanged = false;
//    ifstream readHS("./Projet_Qt/DuckHunt/highscores.txt", ios::in);
//    if(readHS)
//    {
//        for(i=0 ; i<5 ; i++)
//        {
//            readHS >> bestScores[i].name;
//            readHS >> bestScores[i].score;
//        }

//        readHS.close();
//    }


//    else
//        return;

//    for(i=0 ; i<5 && !asChanged; i++)
//    {
//        if (bestScores[i].score < lastPlayer.score)
//        {
//            bestScores[i].score = lastPlayer.score;
//            bestScores[i].name = lastPlayer.name;
//            asChanged = true;
//        }
//    }

//    if(asChanged)
//    {
//        ofstream writeHS("./Projet_Qt/DuckHunt/highscores.txt", ios::out);
//        if(writeHS)
//        {
//            for(i=0 ; i<5 ; i++)
//            {
//                writeHS << bestScores[i].name << " ";
//                writeHS << bestScores[i].score << std::endl;
//            }
//            writeHS.close();
//        }
//    }
//}

