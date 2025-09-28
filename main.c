#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "fonctionutile.h"
#include "game_function.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

list_string inventaire, objetdisponible, evenement;
int position[] = {1,1};
int oldposition[] = {1,1};
int world = 0;
int oldworld = -1;
int error = 0;













int jeu(){
    list_char prompt;
    list_char fichier_a_ouvrir;
    list_char buffer;
    FILE  *element;
    int compteur;
    init_list_string(&inventaire);
    init_list_string(&objetdisponible);
    init_list_string(&evenement);
    init_list_char(&fichier_a_ouvrir, "");
    init_list_char(&buffer, "");
    init_list_char(&prompt,"");
    do{
        if(world != oldworld){
            intro_reader();
            position[0] =1;
            position[1] =1;
            oldposition[0] = 1;
            oldposition[1] = 1;

            reec_list_char(&fichier_a_ouvrir);
            append_charptr(&fichier_a_ouvrir,"./monde/");
            int_translator(&buffer,world);
            append_charptr(&fichier_a_ouvrir, buffer.content);
            append_charptr(&fichier_a_ouvrir,"/1,1.piece");
            element = fopen(fichier_a_ouvrir.content,"r");
            if (element == NULL){
                printf("error missing file...");
                return -1;
            }
            description_reader(element);
            fclose(element);
        }
        printf(":>");
        input(&prompt);
        
        if(is_word_in_string("aller",prompt.content))        
        {
            /*
            
            fonction de déplacement...

            */
            fonction_deplacement(&prompt);
        }
        else if(is_word_in_string("clear", prompt.content)){
            /*

            fonction qui "efface" le texte...

            */
            compteur = 0;
            while(compteur != 1000){
                printf("\n");
                compteur ++;
            }
        }
        else if(is_word_in_string("regarder", prompt.content) ||is_word_in_string("inspecter", prompt.content) ){
            fonction_regarder(&prompt);
        }
        else if(is_word_in_string("exit",prompt.content)){
            /*
            
            fonction de fin de programme

            */
            break;
        }
        else if(is_word_in_string("prendre",prompt.content)){

            fonction_prendre(&prompt);


        }
        else if(is_word_in_string("parler",prompt.content) || is_word_in_string("discuter",prompt.content)){

            fonction_parler(&prompt);

        }
        else{
            /*
            
            ici on affiche que la commande qui n'as pas fonctionné
            
            */
            printf("unrecognise expression : %s\n", prompt.content);
        }

        if (error == 1){
            /*
            
            si on a une erreur on arrète le programme.
            
            */
            break;
        }

    }
    while(1);
    free_liste_char(&prompt);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer);
    free_liste_string(&inventaire);
    free_liste_string(&objetdisponible);
    free_liste_string(&evenement);
    return 0;

    
}







int main()
{
    jeu();
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


