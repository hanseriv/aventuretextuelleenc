#ifndef GAME_FUNCTION_H_INCLUDED
#define GAME_FUNCTION_H_INCLUDED
#define colonne 90

#include "fonctionutile.h"

void waiting(void);
void clear_func(void);
void fonction_deplacement(list_char* prompt);
void description_reader(FILE * streamfile);
void fonction_regarder(list_char * prompt);
void intro_reader(void);
void fonction_prendre(list_char * prompt);
void fonction_parler(list_char * prompt);
void fonction_utiliser(list_char * prompt);



#endif
