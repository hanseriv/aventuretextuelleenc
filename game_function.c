#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"



extern list_string inventaire, objetdisponible, evenement;
extern int position[], oldposition[];
extern int world, oldworld;


void fonction_deplacement(list_char * prompt){
    if (is_word_in_string("nord",prompt->content)){
        position[0] ++;
    }
    else if (is_word_in_string("sud",prompt->content)){
        position[1] --;
    }
    else if (is_word_in_string("est", prompt->content)){
        position[2] --;
    }
    else if (is_word_in_string("ouest" , prompt->content)){
        position[2] --;
    }
    else{
        printf("deplacement non valide veuiller utiliser les coordonnees (n, nord...)\n");
    }
}

void fonction_regarder(list_char * prompt){
    
}
