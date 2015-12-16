#include "main.h"

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        //easter egg ?
    }

    // initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    if(TTF_Init() < 0)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(!screen)
    {
        printf("Unable to set %ix%i video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        return 1;
    }

    srand(time(NULL)); //Initialise la generation aleatoire

    //-------------------- init variables ------------------------

    int score = 0;
    int current_wave = 1; //contient la vague courrante, 1 vague = 2 canards, il y a 5 vagues par niveau
    bool wave_finished = false; //Permet de savoir quand afficher le chien qui rigole ou alors celui avec les canards dans la/les main(s)
    bool new_level = true; //Permet de savoir si on démarre un nouveau niveau afin de ne pas afficher le niveau à chaque fin de wave
    bool duckIsDead1 = false, duckIsDead2 = false;
    int level = 1; //niveau courant en commencant la partie
    int bullet_left = 3;
    int tot_duck_killed = 0; //nbr de canards tués pendant 1 level

    int levels_copy[NB_LEVEL][3]; //on créé une copie des niveaux pour ne pas modifier l'original

    int i, j;
    for(i = 0; i < NB_LEVEL; i++)
        for(j = 0; j < 3; j++)
            levels_copy[i][j] = levels[i][j];



    Display display = GAME;
    GameState gs = DOG;

    SDL_Surface* entity_sprites = loadImageWithColorKey("res/sprites/duck.png", true, 228, 255, 0);
    SDL_Surface* background = loadImageWithColorKey("res/sprites/backGame.png", false, 0, 0, 0);
    SDL_Surface* fake_background = loadImageWithColorKey("res/sprites/backGameBlit.png", true, 0, 0, 0);
    SDL_Surface* menu_img = loadImageWithColorKey("res/sprites/menu.png", false, 0, 0, 0);
    SDL_Surface* cursor_img = loadImageWithColorKey("res/sprites/viseur.png", true, 0, 0, 0);
    SDL_Surface* bullet_img = loadImageWithColorKey("res/sprites/shot.png", true, 255, 255, 255);
    SDL_Surface* duck_hit_img = loadImageWithColorKey("res/sprites/hit.png", true, 5, 5, 5);
    SDL_Surface* boss_bg[5];
    SDL_Surface *user_name = NULL;


    string path_to_boss_bg = "res/sprites/boss_bg_";
    string ext = ".png";

    for(i = 0; i < 5; i++)
        boss_bg[i] = loadImageWithColorKey((path_to_boss_bg + to_string(i) + ext).c_str(), true, 255, 255, 0);

    TTF_Font* vsmall_font = TTF_OpenFont("res/font/duck_hunt.ttf", 30);
    TTF_Font* small_font = TTF_OpenFont("res/font/duck_hunt.ttf", 35);
    TTF_Font* normal_font = TTF_OpenFont("res/font/duck_hunt.ttf", 65);
    TTF_Font* big_font = TTF_OpenFont("res/font/duck_hunt.ttf", 90);
    SDL_Color blackcolor = {0, 0, 0, 0};

    Button singleplayer;
    singleplayer.surface = TTF_RenderText_Solid(normal_font, "Play", blackcolor);
    singleplayer.x = SCREEN_WIDTH/2;
    singleplayer.y = SCREEN_HEIGHT/3;
    singleplayer.select = true;

    Button quit;
    quit.surface = TTF_RenderText_Solid(normal_font, "Quit", blackcolor);
    quit.x = SCREEN_WIDTH/2;
    quit.y = SCREEN_HEIGHT/2;
    quit.select = false;

    Button ok; //bouton de retour au menu lorsque Game Over
    ok.surface = TTF_RenderText_Solid(vsmall_font, "Retour au menu", blackcolor);
    ok.x = SCREEN_WIDTH / 2;
    ok.y = SCREEN_HEIGHT / 2;
    ok.select = false;

    SDL_Rect dst_background;
    dst_background.x = dst_background.y = 0;
    dst_background.w = background->w;
    dst_background.h = background->h;

    SDL_Rect user_name_dst;
    user_name_dst.w = SCREEN_WIDTH / 4;
    user_name_dst.h = 35;
    user_name_dst.x = (SCREEN_WIDTH) / 2 - user_name_dst.w;
    user_name_dst.y = (SCREEN_HEIGHT) / 3;

    Dog dog;
    initDog(entity_sprites, dog);

    Duck duck[NB_DUCK_PER_LEVEL]; //tableau de cannards (10 par niveau)
    DuckScore duckScore[2]; //1 pour chaque canard

    for(i = 0; i < 2; i++)
    {
        duckScore[i].sprite = new Sprite;
        duckScore[i].sprite->rect_dst = new SDL_Rect;
        duckScore[i].sprite->rect_src = new SDL_Rect;
        duckScore[i].sprite->img = loadImageWithColorKey("res/sprites/points.png", true, 0, 0, 0);
    }

    for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
        initDuck(entity_sprites, duck[i], levels_copy, level);

    Boss boss;
    initBoss(entity_sprites, boss);

    Player current_user;
    current_user.name = "Pseudo: _ _ _ _ _ _ _ _ _";
    int nb_lettres_entrees = 0;

    Player bestScores[5];
    bool nameEntered = false; //booléen qui test si le nom du joueur a été entré à la fin

    //------------------------------------------------------------

    // program main loop
    bool done = false;

    while(!done)
    {
        // message processing loop
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            // check for messages
            switch(event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                // check for keypresses
                case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;

                    break;
                }
            } // end switch

            if(display == MENU)
            {
                switch(detectMouseMenu(singleplayer, quit, event))
                {
                    case 1:
                        display = GAME;
                        SDL_ShowCursor(SDL_DISABLE); //cache le curseur
                        break;

                    case -1: //quitter
                        done = true;
                        break;
                }
            }

            else if(display == GAME_OVER)
            {
                if(event.motion.x < (ok.x + ok.surface->w) && event.motion.x > ok.x && event.motion.y < (ok.y + ok.surface->h) && event.motion.y > ok.y)
                {
                    ok.select = true;

                    if(event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        display = MENU;
                        nameEntered = true;
                    }
                }

                else
                    ok.select = false;

                if(event.type == SDL_KEYDOWN && nb_lettres_entrees <= MAX_LENGTH_USERNAME)
                {
                    if(event.key.keysym.sym == SDLK_BACKSPACE && nb_lettres_entrees > 0)
                    {
                        nb_lettres_entrees--;
                        current_user.name.replace(8+(nb_lettres_entrees)*2, 1, "_");
                    }

                    else if(nb_lettres_entrees < MAX_LENGTH_USERNAME-1)
                    {
                        string key = "";
                        key += event.key.keysym.sym;
                        current_user.name.replace(8+nb_lettres_entrees*2, 1, key.c_str());
                        nb_lettres_entrees++;
                    }
                }

                user_name = TTF_RenderText_Solid(small_font, current_user.name.c_str(), blackcolor);
            }

            else if(event.type == SDL_MOUSEBUTTONDOWN && display == GAME && gs == DUCK && bullet_left > 0)
            {
                if(!duck[current_wave*2-1].dead && killDuck(duck[current_wave*2-1], event))
                {
                    score += (duck[current_wave*2-1].type+1)*500;
                    tot_duck_killed++;
                    duckIsDead1 = true;
                    duckScore[0].cooldown = 50;
                    duckScore[0].alpha = 255;
                }

                else if(!duck[current_wave*2-2].dead && killDuck(duck[current_wave*2-2], event))
                {
                    score += (duck[current_wave*2-2].type+1)*500;
                    tot_duck_killed++;
                    duckIsDead2 = true;
                    duckScore[1].cooldown = 50;
                    duckScore[1].alpha = 255;
                }

                bullet_left--;
            }

        } // end of message processing

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        switch(display)
        {
            case MENU:
            {
                showMenu(screen, menu_img, normal_font, big_font, singleplayer, quit);
                break;
            }

            case GAME:
            {
                SDL_BlitSurface(background, NULL, screen, &dst_background); //on affiche l'image de fond

                switch(gs) //GameState
                {
                    case DOG: //display dog
                    {
                        processDog(screen, dog);

                        if(!dog.state && new_level)
                            gs = LEVEL;

                        else if(!dog.state)
                            gs = DUCK;

                        break;
                    }

                    case LEVEL: //display level n°
                    {
                        SDL_Color color = {0, 193, 255, 0};
                        string text = "Level ";
                        text += to_string(level);

                        SDL_Surface *text_level = TTF_RenderText_Shaded(normal_font, text.c_str(), blackcolor, color);

                        SDL_Rect text_rect;
                        text_rect.w = text_level->w;
                        text_rect.h = text_level->h;
                        text_rect.x = (SCREEN_WIDTH - text_level->w) / 2;
                        text_rect.y = (SCREEN_HEIGHT - text_level->h) / 3;

                        SDL_BlitSurface(text_level, NULL, screen, &text_rect);

                        gs = DUCK;
                        SDL_Flip(screen);
                        SDL_Delay(2000); //On peut se permettre de faire ca, car durant l'affichage du niveau, l'utilisateur ne peut rien faire

                        new_level = false;

                        break;
                    }

                    case DUCK: //display the game with ducks
                    {
                        processDuck(screen, duck[current_wave*2-2]);
                        processDuck(screen, duck[current_wave*2-1]);

                        //Gestion du curseur
                        int x_mouse, y_mouse;
                        SDL_GetMouseState(&x_mouse, &y_mouse);

                        SDL_Rect cursor_pos;
                        cursor_pos.x = x_mouse - cursor_img->w / 2;
                        cursor_pos.y = y_mouse - cursor_img->h / 2;
                        cursor_pos.h = cursor_img->h;
                        cursor_pos.w = cursor_img->w;

                        SDL_BlitSurface(cursor_img, NULL, screen, &cursor_pos); //on affiche l'image de la cible à la position de la souris
                        //------------------

                        //Afficher les infos "balles restantes" "score" et "canards tués ou non"
                        displayBulletLeft(screen, bullet_img, bullet_left);

                        displayScore(screen, vsmall_font, score);

                        displayDuckHit(screen, duck, current_wave, duck_hit_img);

                        if(duckIsDead1 && duck[current_wave*2-1].dead)
                        {
                            if(duckScore[0].cooldown >= 0)
                            {
                                displayDuckScore(duck[current_wave*2-1], duckScore[0], screen);
                                duckScore[0].cooldown--;
                                if(duckScore[0].alpha > 0)
                                    duckScore[0].alpha -= 5;
                            }

                            else
                                duckIsDead1 = false;


                        }

                        if(duckIsDead2 && duck[current_wave*2-2].dead)
                        {
                            if(duckScore[1].cooldown >= 0)
                            {
                                displayDuckScore(duck[current_wave*2-2], duckScore[1], screen);
                                duckScore[1].cooldown--;
                                if(duckScore[1].alpha > 0)
                                    duckScore[1].alpha -= 5;
                            }

                            else
                                duckIsDead2 = false;
                        }

                        if(!bullet_left && (!duck[current_wave*2-1].dead || !duck[current_wave*2-2].dead) && (duck[current_wave*2-1].displayed || duck[current_wave*2-2].displayed)) // s'il n'y a plus de balle et qu'un des deux canards n'est pas mort, il faut le faire sortir
                        {
                            if(!duck[current_wave*2-1].dead)
                                fadeOutDuck(duck[current_wave*2-1]);

                            if(!duck[current_wave*2-2].dead)
                                fadeOutDuck(duck[current_wave*2-2]);
                        }

                        //si les canards sont morts et plus à l'écran, alors la vague est terminée (ou s'il n'y a plus de balle)
                        else if((duck[current_wave*2-1].dead && duck[current_wave*2 - 2].dead && !duck[current_wave*2-1].displayed && !duck[current_wave*2-2].displayed) || (!bullet_left && (!duck[current_wave*2-1].dead || !duck[current_wave*2-2].dead)))
                            wave_finished = true;

                        if(wave_finished)
                        {
                             //si des canards ont été tués
                            if(duck[current_wave*2-1].dead || duck[current_wave*2-2].dead)
                            {
                                changeDogAnimation(dog, 4);
                                dog.state = 4;

                                //2 canards ont été tués
                                if(duck[current_wave*2-1].dead && duck[current_wave*2-2].dead)
                                {
                                    dog.sprite->w = 115;
                                    dog.sprite->rect_src->w = dog.sprite->w;

                                    if(duck[current_wave*2-1].type == 0 && duck[current_wave*2-2].type == 0)
                                        dog.sprite->rect_src->x = 579;

                                    else if(duck[current_wave*2-1].type == 1 && duck[current_wave*2-2].type == 1)
                                        dog.sprite->rect_src->x = 694;

                                    else if(duck[current_wave*2-1].type == 2 && duck[current_wave*2-2].type == 2)
                                        dog.sprite->rect_src->x = 1042;

                                    else if( (duck[current_wave*2-1].type == 0 && duck[current_wave*2-2].type == 1) || (duck[current_wave*2-2].type == 0 && duck[current_wave*2-1].type == 1) )
                                        dog.sprite->rect_src->x = 1157;

                                    else if( (duck[current_wave*2-1].type == 0 && duck[current_wave*2-2].type == 2) || (duck[current_wave*2-2].type == 0 && duck[current_wave*2-1].type == 2) )
                                        dog.sprite->rect_src->x = 808;

                                    else if( (duck[current_wave*2-1].type == 1 && duck[current_wave*2-2].type == 2) || (duck[current_wave*2-2].type == 1 && duck[current_wave*2-1].type == 2) )
                                        dog.sprite->rect_src->x = 927;
                                }

                                //1 canard a été tué
                                else if(duck[current_wave*2-1].dead)
                                {
                                    switch(duck[current_wave*2-1].type)
                                    {
                                        case 0:
                                            dog.sprite->rect_src->x = 488;
                                            break;

                                        case 1:
                                            dog.sprite->rect_src->x = 305;
                                            break;

                                        case 2:
                                            dog.sprite->rect_src->x = 396;
                                            break;
                                    }
                                }

                                //1 canard (l'autre) a été tué
                                else if(duck[current_wave*2-2].dead)
                                {
                                    switch(duck[current_wave*2-2].type)
                                    {
                                        case 0:
                                            dog.sprite->rect_src->x = 488;
                                            break;

                                        case 1:
                                            dog.sprite->rect_src->x = 305;
                                            break;

                                        case 2:
                                            dog.sprite->rect_src->x = 396;
                                            break;
                                    }
                                }

                            }

                            else
                            {
                                changeDogAnimation(dog, 5);
                                dog.state = 5;
                            }

                            current_wave++;
                            bullet_left = 3;

                            //on change de niveau si on a tué minimum 6 canards
                            if(current_wave > 5 && tot_duck_killed > 5)
                            {
                                level++;
                                tot_duck_killed = 0;

                                //reset ducks
                                int i;
                                for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
                                    deleteDuck(duck[i]);

                                for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
                                    initDuck(entity_sprites, duck[i], levels_copy, level);

                                current_wave = 1;
                                new_level = true;

                                if(level > 5)
                                    gs = BOSS;
                            }

                            //Si la vague est terminée mais que pas assez de canards ont été tués, alors on affiche gameover
                            else if(current_wave > 5)
                            {
                                SDL_ShowCursor(SDL_ENABLE); //On réactive la souris
                                display = GAME_OVER;

                                //ON RESET TOUT AU LEVEL 1 au cas où l'utilisateur voudrait rejouer une fois dans le menu
                                level = 1;
                                current_wave = 1;
                                score = 0;
                                tot_duck_killed = 0;
                                new_level = true;

                                //reset la copie de levels
                                for(i = 0; i < NB_LEVEL; i++)
                                    for(j = 0; j < 3; j++)
                                        levels_copy[i][j] = levels[i][j];

                                //reset ducks
                                int i;
                                for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
                                    deleteDuck(duck[i]);

                                for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
                                    initDuck(entity_sprites, duck[i], levels_copy, level);

                                //reset dog
                                changeDogAnimation(dog, 0);
                                dog.state = 1;
                            }

                            gs = DOG;
                            wave_finished = false;
                        }

                        SDL_Delay(12);
                        break;
                    }

                    case BOSS:
                    {
                        SDL_BlitSurface(boss_bg[0], NULL, screen, NULL);

                        boss.dogs[0]->sprite->rect_dst->x = boss.dogs[0]->sprite->rect_dst->y = 55*2;
                        SDL_BlitSurface(boss.dogs[0]->sprite->img, boss.dogs[0]->sprite->rect_src, screen, boss.dogs[0]->sprite->rect_dst);
                        SDL_BlitSurface(boss_bg[1], NULL, screen, NULL);

                        boss.dogs[1]->sprite->rect_dst->x = boss.dogs[1]->sprite->rect_dst->y = 110*2;
                        SDL_BlitSurface(boss.dogs[1]->sprite->img, boss.dogs[1]->sprite->rect_src, screen, boss.dogs[1]->sprite->rect_dst);
                        SDL_BlitSurface(boss_bg[2], NULL, screen, NULL);

                        boss.dogs[2]->sprite->rect_dst->x = boss.dogs[2]->sprite->rect_dst->y = 165*2;
                        SDL_BlitSurface(boss.dogs[2]->sprite->img, boss.dogs[2]->sprite->rect_src, screen, boss.dogs[2]->sprite->rect_dst);
                        SDL_BlitSurface(boss_bg[3], NULL, screen, NULL);

                        boss.dogs[3]->sprite->rect_dst->x = boss.dogs[3]->sprite->rect_dst->y = 220*2;
                        SDL_BlitSurface(boss.dogs[3]->sprite->img, boss.dogs[3]->sprite->rect_src, screen, boss.dogs[3]->sprite->rect_dst);
                        SDL_BlitSurface(boss_bg[4], NULL, screen, NULL);

                        break;
                    }
                }

                if(dog.state != 1 && dog.state != 2 && dog.state != 3)
                    SDL_BlitSurface(fake_background, NULL, screen, &dst_background); //on affiche l'image de fond

                break;
            }

            case GAME_OVER:
            {
                SDL_BlitSurface(background, NULL, screen, &dst_background); //on affiche l'image de fond
                SDL_Color background_color = {0, 193, 255, 0};
                SDL_Color text_color = {255, 50, 50, 0};
                string text = "Game Over";

                SDL_Surface *text_game_over = TTF_RenderText_Shaded(normal_font, text.c_str(), text_color, background_color);

                SDL_Rect text_rect;
                text_rect.w = text_game_over->w;
                text_rect.h = text_game_over->h;
                text_rect.x = (SCREEN_WIDTH - text_game_over->w) / 2;
                text_rect.y = (SCREEN_HEIGHT - text_game_over->h) / 4;

                SDL_BlitSurface(text_game_over, NULL, screen, &text_rect);
                if(user_name != NULL)
                    SDL_BlitSurface(user_name, NULL, screen, &user_name_dst);


                if(ok.select)
                {
                    ok.surface = TTF_RenderText_Solid(small_font, "Ok", blackcolor);

                    if(nameEntered)
                        sortBestScores(bestScores, current_user);
                }

                else
                    ok.surface = TTF_RenderText_Solid(vsmall_font, "Ok", blackcolor);


                ok.x = (SCREEN_WIDTH-ok.surface->w) / 2;
                ok.y = (SCREEN_HEIGHT-ok.surface->h) / 2;
                text_rect.x = ok.x;
                text_rect.y = ok.y;
                SDL_BlitSurface(ok.surface, NULL, screen, &text_rect);



                break;
            }
        } //end switch display

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
        SDL_Delay(10);
    } // end main loop

    TTF_CloseFont(normal_font);
    TTF_CloseFont(big_font);
    SDL_FreeSurface(entity_sprites);
    SDL_FreeSurface(menu_img);
    SDL_FreeSurface(cursor_img);
    SDL_FreeSurface(bullet_img);
    SDL_FreeSurface(background);
    SDL_FreeSurface(fake_background);
    deleteDog(dog);

    //------ Remove DuckScore struct ------
    for(i = 0; i < 2; i++)
    {
        delete duckScore[i].sprite->rect_src;
        delete duckScore[i].sprite->rect_dst;
        delete duckScore[i].sprite->img;
        delete duckScore[i].sprite;
    }
    //-------------------------------------


    for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
        deleteDuck(duck[i]);

    SDL_Quit();
    printf("Exited cleanly\n");
    return 0;
}
