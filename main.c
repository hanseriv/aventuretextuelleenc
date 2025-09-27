#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "fonctionutile.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

list_string inventaire, objetdisponible, evenement;
int position[] = {0,0};
int oldposition[] = {0,0};
int world = 0;
int oldworld = 0;














int main()
{



    list_char jean1;
    /*
    char buffer[1000];
    fgets(buffer, 1000,stdin);
    */
    init_list_char(&jean1,"");

    input(&jean1);

    printf("%s1\n",  jean1.content);

    reec_list_char(&jean1);

    append_charptr(&jean1, "coucou jean sa va ?");
    printf("%u \n",is_word_in_string("coucou",jean1.content));

    printf("%s\n",  jean1.content);

    

    /*
    //The window we'll be rendering to
    SDL_Window* window = NULL;


    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        //Destroy window

        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );

        //Fill the surface white
        SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

        //Update the surface
        SDL_UpdateWindowSurface( window );
        SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; }

    }
    }
    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();
    */
   free_liste_char(&jean1);
    return 0;
}


