#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"

void free_liste_char(list_char phrase){
    free(phrase.content);


}

void free_liste_string(list_string *matrice){
    /*
        entrée : pointeur de structure list_string
        sortie : None
        le but de cette fonction est de libéré l'espace mémoire utilisé
        par la structure une fois que celle-ci a finie d'etre utilisé
    */
    unsigned int longueur = matrice->len;
    list_char pointer_buffer;
    while (longueur != 0){
        pointer_buffer =  matrice->content[longueur -1] ;
        free_liste_char(pointer_buffer);
        longueur --;
    }
    free(matrice);
}


list_char append_char(list_char phrase, char letter){
    /*
        entrée : list_char phrase, et char lettre
        sortie : list_phrase
        le but de cette fonction est de réattribuer un pointeur
        pour pouvoir rajouter le caractère letter a la fin de la phrase
    */
    phrase.content = realloc(phrase.content, (phrase.len + 2) * sizeof(char)); // on augmente la taille alloué a la liste
    phrase.content[phrase.len] = letter; // on ajoute le nouveau contenu
    phrase.content[phrase.len+1] = '\0'; // sans oublié l'arreteur de string
    phrase.len++; // on augmente la taille
    return phrase; // on return la nouvelle structure
}

list_char append_charptr(list_char phrase, char *aajouter){
    /*
        entrée : list_char phrase, et char *aajouter
        sortie : phrase
        le but de cette fonction est de réattribuer un pointeur
        pour pouvoir rajouter la string aajouter a la fin de la phrase
    */
    unsigned int longueur = len_string(aajouter);
    unsigned int compteur = 0;
    while(compteur < longueur ){
        phrase = append_char(phrase,aajouter[compteur]);
        compteur ++;
    }
    return phrase;
}



list_char init_list_char(list_char phrase, char *acopie){
    /*
        entrée : list_char phrase, et pointeur de char acopie
        sortie : list_char phrase
        le but de cette fonction est de copier une phrase et d'initialiser une string dans content de la list_char
    */
    unsigned int longueur = len_string(acopie);
    phrase.len = longueur;
    free(phrase.content);
    phrase.content = malloc((longueur + 1)*sizeof(char));
    copieur_str(phrase.content,acopie);
    return phrase;
}


list_string append_str(list_string matrice, list_char phrase){

    matrice.len++;
    matrice.content = realloc(matrice.content, (matrice.len) * sizeof(list_char*)); // on augmente la taille alloué a la matrice

    matrice.content[matrice.len - 1 ] =  append_charptr(matrice.content[matrice.len - 1 ], phrase.content);


    return matrice;
}




int len_string(char *str){

    unsigned int compteur = 0;

    while(str[compteur] != 0){
        compteur ++;
    }
    return compteur;
}

void copieur_str(char * tocopie, char * a_copier){

    unsigned int compteur = 0;

    while (a_copier[compteur] != '\0'){
        tocopie[compteur] = a_copier[compteur];
        compteur ++;
    }
}


char **stringtoliste( char* str){

    list_char mot;
    mot.len = 0;

    list_string phrase;
    phrase.len = 0;


    unsigned int compteur = 0;

    while(str[compteur] != '\0'){
        if(str[compteur] != ' '){
            //mot = '1';
        }
    }


}
