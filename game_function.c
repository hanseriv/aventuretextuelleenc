#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"



extern list_string inventaire, objetdisponible, evenement;
extern int position[], oldposition[];
extern int world, oldworld;


int fonction_deplacement(list_char * prompt){
    list_char fichier_a_ouvrir;
    init_list_char(&fichier_a_ouvrir, "./monde");
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
        return 0;
    }

    return 0;
}

void fonction_regarder(list_char * prompt){

}
