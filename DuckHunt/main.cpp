#include "utils.h"

int main(int argc, char** argv)
{
    // initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);

    if (!screen)
    {
        printf("Unable to set %ix%i video: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        return 1;
    }

    // program main loop
    bool done = false;

    while(!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
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
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

