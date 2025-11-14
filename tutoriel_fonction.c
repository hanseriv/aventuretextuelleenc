#include <stdio.h>
#include <stdlib.h>
#include "tutoriel_fonction.h"
#include "game_function.h"
#include "fonctionutile.h"

extern int error;

void tutoriel(void){
    FILE * element;
    char buffer[10000];
    element = fopen("tutoriel.tutoriel","r");
    if(element != NULL){
        while(fgets(buffer,10000,element) != NULL){
            printf("%s",buffer);
        }
        fclose(element);
        waiting();
    }
    else{
        printf("unreachable tutorial please consult the manual to understand what is happening...\n");
        error = 1;
    }
}