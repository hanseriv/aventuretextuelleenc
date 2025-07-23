#ifndef FONCTIONUTILE_H_INCLUDED
#define FONCTIONUTILE_H_INCLUDED
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

void free_liste_char(list_char phrase);
void free_liste_string(list_string *matrice);
list_char append_charptr(list_char phrase, char *aajouter);
list_char init_list_char(list_char phrase, char *acopie);
int len_string(char *str);
void copieur_str(char * tocopie, char * a_copier);
list_string stringtoliste(list_char phrase);
list_string append_str(list_string matrice, list_char phrase);
list_char append_char(list_char phrase, char letter);
int is_the_char_the_same(list_char phrase1, list_char phrase2);
list_char append_stringchar(list_char aretourner, list_char aajouter);

#endif // FONCTIONUTILE_H_INCLUDED
