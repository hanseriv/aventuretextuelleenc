#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"
#include "game_function.h"

extern int error;

void print_logo(void){
    FILE * streamfile;
    char buffer[1000];
    streamfile = fopen("logo.logo","r");
    if (streamfile == NULL){
        printf("non readable logo...please make sure that the program can read external file...");
        error = 1;
    }
    else{
        while(fgets(buffer,1000,streamfile) != NULL) {
            printf("%s",buffer);
        }
        fclose(streamfile);
    }

}
