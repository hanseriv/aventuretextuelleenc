#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"

#define colonne 90


extern list_string inventaire, objetdisponible, evenement;
extern int position[], oldposition[];
extern int world, oldworld,error;


void intro_reader(){
    FILE  *element;
    list_char fichier_a_ouvrir;
    list_char buffer;
    oldworld = world;
    char buffer_c;
    init_list_char(&buffer,"");
    init_list_char(&fichier_a_ouvrir, "./monde/");
    int_translator(&buffer,world);
    append_charptr(&fichier_a_ouvrir, buffer.content);
    append_char(&fichier_a_ouvrir,'/');
    append_charptr(&fichier_a_ouvrir, "intro.intro");
    element = fopen(fichier_a_ouvrir.content,"r");
    if (element == NULL){
        error = 1;
        printf("error while reading the intro from your world please make sure that every file is in order...\n");
    }
    else{
        int compteur = 0;
        buffer_c = fgetc(element);
        while(buffer_c != EOF){
            printf("%c", buffer_c);
            compteur ++;
            if(compteur == colonne){
                compteur = 0;
                printf("\n");
            }
            buffer_c = fgetc(element);
        }
        printf("\n");
    }
    free_liste_char(&buffer);
    free_liste_char(&fichier_a_ouvrir);
    fclose(element);
}






int fonction_deplacement(list_char * prompt){
    FILE *element;
    list_char fichier_a_ouvrir;
    init_list_char(&fichier_a_ouvrir, "monde");
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
    /*
        on ouvre le fichier du niveau correspondant
    */
    list_char buffer;
    init_list_char(&buffer,"");
    init_list_char(&fichier_a_ouvrir, "monde/");
    int_translator(&buffer,world);
    append_charptr(&fichier_a_ouvrir, buffer.content);
    append_char(&fichier_a_ouvrir,'/');
    int_translator(&buffer,position[0]);
    append_charptr(&fichier_a_ouvrir, buffer.content);
    append_char(&fichier_a_ouvrir,',');
    int_translator(&buffer,position[1]);
    append_charptr(&fichier_a_ouvrir, buffer.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    /*
        fin de la retranscrisption du niveau 
    */
    element = fopen(fichier_a_ouvrir.content,"r");
    if(element == NULL){
        printf("je ne pense pas pouvoir passer a travers l'univers lui-meme...\n");
        position[0] = oldposition[0];
        position[1] = oldposition[1];
    }
    else{
        oldposition[0] = position[0];
        oldposition[1] = position[1];
        fclose(element);
    }
        free_liste_char(&buffer);
        free_liste_char(&fichier_a_ouvrir);
    return 0;
}


void fonction_regarder(list_char * prompt){

}
