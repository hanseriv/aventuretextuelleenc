#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"

void input(list_char *input){
    /*
        fonction qui lie l'input du flux stdin
    */
    char buffer = getchar();
    reec_list_char(input);
    while(buffer != '\n' && buffer != '\r' && buffer != EOF){
        input->content = realloc(input->content,(input->len + 1) * sizeof(char));
        input->content[input->len] = buffer;
        input->len ++;
        buffer = getchar();
    }
    input->content[input->len] = '\0';


}





void free_liste_char(list_char *phrase){
    /*
        entrée : pointeur de list_char
        libère l'espace stocké
    */
    free(phrase->content);
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
        free_liste_char(&pointer_buffer);
        longueur --;
    }
    free(matrice);
}

int is_the_char_the_same(list_char phrase1, list_char phrase2){
    /*
        entrée : list_char phrase1 et list_phrase2
        compare les deux string et retourne False_statement si elle sont différente
        et True_statement dans le cas contraire
    */
    if (phrase1.len != phrase2.len){
        return 0;
    }
    unsigned int compteur = 0;
    while(compteur <= phrase1.len){
        if (phrase1.content[compteur] != phrase2.content[compteur]){
            return 0;
        }
        compteur ++;
    }
    return 1;
}


void append_char(list_char *phrase, char letter){
    /*
        entrée : list_char phrase, et char lettre
        sortie : list_phrase
        le but de cette fonction est de réattribuer un pointeur
        pour pouvoir rajouter le caractère letter a la fin de la phrase
    */
    phrase->len++; /*on augmente la taille*/ 
    phrase->content = realloc(phrase->content, (phrase->len ) * sizeof(char)); /*on augmente la taille alloué a la liste*/ 
    phrase->content[phrase->len -1] = letter; /*on ajoute le nouveau contenu*/ 
    
}

void append_charptr(list_char *phrase, char *aajouter){
    /*
        entrée : list_char *phrase, et char *aajouter
        sortie : phrase
        le but de cette fonction est de réattribuer un pointeur
        pour pouvoir rajouter la string aajouter a la fin de la phrase
    */
    unsigned int longueur = len_string(aajouter);
    unsigned int compteur = 0;
    while(compteur <= longueur ){
        append_char(phrase,aajouter[compteur]);
        compteur ++;
    }
    append_char(phrase,'\0');
}



void init_list_char(list_char *phrase, char *acopie){
    /*
        entrée : list_char phrase, et pointeur de char acopie
        sortie : list_char phrase
        le but de cette fonction est de copier une phrase et d'initialiser une string dans content de la list_char
    */
    unsigned int longueur = len_string(acopie);
    phrase->len = longueur;
    phrase->content = malloc((longueur + 1)*sizeof(char));
    copieur_str(phrase->content,acopie);
}


void append_stringchar(list_char *aretourner, list_char *aajouter){
    /*
        entrée : 
    
    
    */
    unsigned int compteur = 0;
    while(compteur <= aajouter->len){
        append_char(aretourner,aajouter->content[compteur]);
        compteur ++;
    }
}


void append_str(list_string *matrice, list_char *phrase){

    matrice->len++;
    matrice->content = realloc(matrice->content, (matrice->len) * sizeof(list_char*));  
    init_list_char(&matrice->content[matrice->len - 1 ], "");
    append_stringchar(&matrice->content[matrice->len - 1 ], phrase);

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


void stringtoliste(list_string *matrice_retourner,list_char *phrase){
    list_char mot;
    mot.content = malloc(sizeof(char));
    matrice_retourner->content = malloc(sizeof(list_char));
    unsigned int compteur = 0;
    while(compteur <= phrase->len)
    {
        if (phrase->content[compteur] != ' ')
        {
            append_char(&mot,phrase->content[compteur]);
        }
        else{
            append_str(matrice_retourner, &mot);
            mot.len = 0;
        }
        compteur++;
    }
    append_str(matrice_retourner,&mot);
    free_liste_char(&mot);
}

void reec_list_char(list_char *buffer){
    free(buffer->content);
    buffer->content = malloc(1 * sizeof(char));
    buffer->len = 0;
}


unsigned int is_word_in_string(char * atrouver, char * ou_chercher){
    unsigned int compteur =0;
    unsigned int compteur_inter = 0;
    unsigned int longuer = len_string(ou_chercher);
    unsigned int longeur = len_string(atrouver); 
    while(compteur != longuer){
        if (ou_chercher[compteur] == atrouver[compteur_inter])
            {
                compteur_inter ++;
                if (compteur_inter == longeur){
                    return True_statement;
                }
            }
        else{
            compteur_inter = 0;
        }
        compteur ++;
    }
    return False_statement;
}



char inttochar(int choix){
    switch(choix){
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        case 7:
            return '7';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '9';
            break; 
        default:
            return '\0';
    }
    return '\0';


}

void translation(list_char *prompt, char a_rajouter){
    prompt->len++;
    prompt -> content = realloc(prompt->content,(prompt->len)*sizeof(char) );
    int compteur = prompt->len -1;
    while (compteur != 0){
        prompt->content[compteur] = prompt->content[compteur-1];
        compteur --;
    }
    prompt->content[0] = a_rajouter; 
}



void int_translator(list_char * prompt,int a_traduire){
    int translator = a_traduire;
    reec_list_char(prompt);
    while(translator != 0){
        translator = a_traduire % 10;
        translation(prompt, inttochar(translator));
        a_traduire -= translator;
        a_traduire /= 10;
        translator = a_traduire;
    }

}