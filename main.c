#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "fonctionutile.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;





int main()
{
    list_char jean1;
    if (0){
        printf("hello sale con \n");
    }
    if(1){
        printf("enrevoir \n");
    }

    jean1 = append_charptr(jean1,"hello world je ne comprend pas" );

    printf("l'addresse precedente etait %s1\n",  jean1.content);
    
    list_string jean2 = stringtoliste(jean1);
    unsigned int compteur = 0;
    while (compteur <= jean2.len){
        printf("%s \n", jean2.content[compteur]);
        compteur ++;
    } 

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
    return 0;
}


