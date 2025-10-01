#include <stdio.h>
#include "conversion.h"
#include "fonctionutile.h"
#include <stdlib.h>


int int_absolute(int number){
    /*
        fonction qui retourne la valeur absolue d'une int
    */
    if (number < 0){
        return -number;
    }
    return number;
}

int codex(char number){
    /*
        fonction qui prend en entré une char et qui retourne le chiffre associé
        si le char n'est pas [ '0','1','2','3','4','5','6','7','8','9'] il renvoie 10
        et si quelque chose ,e se passe pas correctement lors de l'execution du code,
        il renvoie 11.

        entrée : char
        sortie : int
    */

    switch (number)
    {
    case '0':
        return 0;
        break;
    case '1':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    default:
        return 10;
        break;
    }
    return 11;

}

int power(int number, int power_of_occurence){
    /*
        fonction qui prend entrée un nombre a virgule et la puissance a laquelle on veut la calculer
        et qui retourne le chiffre correspondant
    */
    int compteur = 0;
    int result = 1;
    int absolute_value = int_absolute(power_of_occurence);
    if (power_of_occurence == 0){
        return 1;
    }
    while(compteur != absolute_value){
            result *= number;
            compteur++;
    }
    if (power_of_occurence != absolute_value)
    {
        result = 1/result;
    }
    return result;
}



int string_to_int(char* string_to_translate){
    /*
        fonction transforme une chaine de caractère en double 
    */
    double result_to_return = 0;
    int compteur = 0;
    int buffer;
    int position_max;
    int decalage = 0;


    while(string_to_translate[compteur] != '\0'){
        compteur ++;
    }
    compteur --;


    position_max = compteur; 
    

    compteur = position_max;
    
    while(compteur != -1){
        buffer = codex(string_to_translate[compteur]);
        result_to_return += buffer * power(10, position_max - (compteur + decalage));
        compteur --;
    }
    return result_to_return;
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
    int compteur = prompt->len -1;
    prompt->len++;
    prompt -> content = realloc(prompt->content,(prompt->len)*sizeof(char) );
    while (compteur != 0){
        prompt->content[compteur] = prompt->content[compteur-1];
        compteur --;
    }
    prompt->content[0] = a_rajouter; 
}



void int_translator(list_char * prompt,int a_traduire){
    
    int signe = 0;
    int translator;
    if (a_traduire < 0){
        a_traduire = -a_traduire;
        signe ++;
    }

    translator = a_traduire;
    reec_list_char(prompt);
    append_char(prompt,'\0');
    if(translator != 0){
        while(translator != 0){
            translator = a_traduire % 10;
            translation(prompt, inttochar(translator));
            a_traduire -= translator;
            a_traduire /= 10;
            translator = a_traduire;
        }
        if(signe == 1){
            translation(prompt, '-');
        } 
    }
    else{
        translation(prompt, inttochar(0));
    }
}
