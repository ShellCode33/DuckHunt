#include "main.h"

int main()
{
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

    bool gameStarting = true;

    Display display = MENU;

    SDL_Surface* entity_sprites = loadImageWithColorKey("res/sprites/duck.png", true, 228, 255, 0);
    SDL_Surface* background = loadImageWithColorKey("res/sprites/backGame.png", false, 0, 0, 0);
    SDL_Surface* fake_background = loadImageWithColorKey("res/sprites/backGameBlit.png", true, 0, 0, 0);

    SDL_Surface* menu_img = loadImageWithColorKey("res/sprites/menu.png", false, 0, 0, 0);


    TTF_Font* small_font = TTF_OpenFont("res/font/duck_hunt.ttf", 65);
    TTF_Font* big_font = TTF_OpenFont("res/font/duck_hunt.ttf", 90);
    SDL_Color blackcolor = {0,0,0};

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

    Duck duck;
    initDuck(entity_sprites, duck);

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

            switch(detectMouseMenu(singleplayer, quit, event))
            {
                case 1:
                    display = GAME;
                    break;

                case -1: //quitter
                    done = true;
                    break;
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

                if(gameStarting)
                {
                    processDog(screen, dog);

                    if(!dog.isComing && !dog.isWaiting && !dog.isJumping)
                        gameStarting = false;
                }

                else
                    processDuck(screen, duck);

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
    SDL_FreeSurface(background);
    SDL_FreeSurface(dog.sprite->img);
    deleteDog(dog);
    SDL_Quit();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
