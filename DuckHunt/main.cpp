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
    int level = 1; //niveau courant en commencant la partie
    int bullet_left = 3;

    Display display = MENU;
    GameState gs = DOG;

    SDL_Surface* entity_sprites = loadImageWithColorKey("res/sprites/duck.png", true, 228, 255, 0);
    SDL_Surface* background = loadImageWithColorKey("res/sprites/backGame.png", false, 0, 0, 0);
    SDL_Surface* fake_background = loadImageWithColorKey("res/sprites/backGameBlit.png", true, 0, 0, 0);

    SDL_Surface* menu_img = loadImageWithColorKey("res/sprites/menu.png", false, 0, 0, 0);

    SDL_Surface* cursor_img = loadImageWithColorKey("res/sprites/viseur.png", true, 0, 0, 0);

    SDL_Surface* bullet_img = loadImageWithColorKey("res/sprites/shot.png", true, 255, 255, 255);

    SDL_Surface* duck_hit_img = loadImageWithColorKey("res/sprites/hit.png", true, 5, 5, 5);


    TTF_Font* vsmall_font = TTF_OpenFont("res/font/duck_hunt.ttf", 30);
    TTF_Font* small_font = TTF_OpenFont("res/font/duck_hunt.ttf", 65);
    TTF_Font* big_font = TTF_OpenFont("res/font/duck_hunt.ttf", 90);
    SDL_Color blackcolor = {0, 0, 0, 0};

    Button singleplayer;
    singleplayer.surface = TTF_RenderText_Solid(small_font, "Play", blackcolor);
    singleplayer.x = SCREEN_WIDTH/2;
    singleplayer.y = SCREEN_HEIGHT/3;
    singleplayer.select = true;

    Button quit;
    quit.surface = TTF_RenderText_Solid(small_font, "Quit", blackcolor);
    quit.x = SCREEN_WIDTH/2;
    quit.y = SCREEN_HEIGHT/2;
    quit.select = false;

    SDL_Rect dst_background;
    dst_background.x = dst_background.y = 0;
    dst_background.w = background->w;
    dst_background.h = background->h;

    Dog dog;
    initDog(entity_sprites, dog);

    Duck duck[NB_DUCK_PER_LEVEL]; //tableau de cannards (10 par niveau)

    int i;
    for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
        initDuck(entity_sprites, duck[i], i%3);

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

            else if(event.type == SDL_MOUSEBUTTONDOWN && display == GAME && gs == DUCK && bullet_left > 0)
            {
                if(!duck[current_wave*2-1].dead && killDuck(duck[current_wave*2-1], event))
                    score += (duck[current_wave*2-1].type+1)*500;

                else if(!duck[current_wave*2-2].dead && killDuck(duck[current_wave*2-2], event))
                    score += (duck[current_wave*2-2].type+1)*500;

                bullet_left--;
            }

        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        switch(display)
        {
            case MENU:
            {
                showMenu(screen, menu_img, small_font, big_font, singleplayer, quit);
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

                        SDL_Surface *text_level = TTF_RenderText_Shaded(small_font, text.c_str(), blackcolor, color);

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

                        //si les canards sont morts et plus à l'écran, alors la vague est terminée (ou s'il n'y a plus de balle)
                        if((duck[current_wave*2-1].dead && duck[current_wave*2 - 2].dead && !duck[current_wave*2-1].displayed && !duck[current_wave*2-2].displayed) || (!bullet_left && (!duck[current_wave*2-1].dead || !duck[current_wave*2-2].dead)))
                            wave_finished = true;

                        if(wave_finished)
                        {
                             //si des canards ont été tués
                            if(duck[current_wave*2-1].dead || duck[current_wave*2-2].dead)
                            {
                                changeDogAnimation(dog, 4);
                                dog.state = 4;
                            }

                            else
                            {
                                changeDogAnimation(dog, 5);
                                dog.state = 5;
                            }

                            current_wave++;
                            bullet_left = 3;

                            //on change de niveau
                            if(current_wave > 5)
                            {
                                level++;

                                //reset ducks
                                int i;
                                for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
                                    deleteDuck(duck[i]);

                                for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
                                    initDuck(entity_sprites, duck[i], i%3);

                                current_wave = 1;
                                new_level = true;
                            }

                            gs = DOG;
                            wave_finished = false;
                        }

                        //----------------------------------------------------------------------

                        SDL_Delay(12);
                        break;
                    }
                }

                if(dog.state != 1 && dog.state != 2 && dog.state != 3)
                    SDL_BlitSurface(fake_background, NULL, screen, &dst_background); //on affiche l'image de fond

                break;
            }
        } //end switch display

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
        SDL_Delay(10);
    } // end main loop

    TTF_CloseFont(small_font);
    TTF_CloseFont(big_font);
    SDL_FreeSurface(entity_sprites);
    SDL_FreeSurface(menu_img);
    SDL_FreeSurface(cursor_img);
    SDL_FreeSurface(bullet_img);
    SDL_FreeSurface(background);
    SDL_FreeSurface(fake_background);
    deleteDog(dog);

    for(i = 0; i < NB_DUCK_PER_LEVEL; i++)
        deleteDuck(duck[i]);

    SDL_Quit();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
