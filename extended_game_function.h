#ifndef EXTENDED_GAME_FUNCTION_H_INCLUDED
#define EXTENDED_GAME_FUNCTION_H_INCLUDED

void print_pnj(FILE * streamfile);

void ouvrir_coffre_ou_porte(list_char * prompt);

void sauter_function(list_char * prompt);

void attaque_function(void);

void launch_attack_sequence(FILE * element);

FILE * open_currentfile(void);

#endif
