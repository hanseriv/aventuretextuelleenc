#ifndef FONCTIONUTILE_H_INCLUDED
#define FONCTIONUTILE_H_INCLUDED
#define True_statement 1
#define False_statement 0
typedef struct list_char list_char;
struct list_char{
    unsigned int len;
    char *content;
};
typedef struct list_string list_string;

struct list_string{
    unsigned int len;
    list_char* content;
};


void input(list_char *input);

void init_list_string(list_string *str_a_init);


void free_liste_char(list_char *phrase);


void free_liste_string(list_string *matrice);


void append_charptr(list_char *phrase, char *aajouter);


void init_list_char(list_char *phrase, char *acopie);


int len_string(char *str);


void copieur_str(char * tocopie, char * a_copier);


void stringtoliste(list_string *matrice_retourner,list_char *phrase);


void append_str(list_string *matrice, list_char *phrase);


void append_char(list_char *phrase, char letter);


int is_the_char_the_same(list_char phrase1, list_char phrase2);


void append_stringchar(list_char *aretourner, list_char *aajouter);


void reec_list_char(list_char *buffer);


unsigned int is_word_in_string(char * atrouver, char * ou_chercher);


char inttochar(int choix);

void int_translator(list_char * prompt,int a_traduire);

int len_string(char *str);


int is_a_string_in_list_string(char * achercher, list_string * ou_chercher);

void print_list_string(list_string * list);

int is_the_char_ptr_shwoing_the_samething(char *phrase1, char *phrase2);
#endif 
