#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fonctionutile.h"
#include "game_function.h"
#include "extended_game_function.h"



int pv_joueur =10;
int exp_joueur = 0;
int niveau_joueur = 0;
int att_stat = 2;
int run_stat =10;
extern list_string inventaire, objetdisponible, evenement;
extern int position[], oldposition[];
extern int world, oldworld,error;
extern short victory;



void monter_niveau(){
    att_stat *= 2;
    niveau_joueur ++;
    pv_joueur = 10;
    printf("avec tous ces combats vous avez gagne un niveau...\nbravo je suppose...\n");
}



void attaque_function(){
    srand(time(NULL));
    



    if (exp_joueur >= 100){
        exp_joueur = 0;
        monter_niveau();
    }
    
}

void sauter_function(list_char * prompt){
    char buffer[10000] = "\0";

    char word_inter[100] = "\0";
    int compteur = 0;
    int offset = 0;
    int compteur_chariot =0;
    int found = 0;
    FILE *element;
    list_char fichier_a_ouvrir;
    list_char buffer_fichier;
    list_char event;

    /*
    
        création du stream
    
    */
   
   
    
    init_list_char(&event,"");
    init_list_char(&buffer_fichier,"");
    init_list_char(&fichier_a_ouvrir, "monde/");


    int_translator(&buffer_fichier,world);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,'/');

    int_translator(&buffer_fichier,position[0]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,',');

    int_translator(&buffer_fichier,position[1]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    /*
    
        ouverture du stream
    
    */
    element = fopen(fichier_a_ouvrir.content,"r");


    while(is_word_in_string("eventobject",buffer) == False_statement){
        fgets(buffer, 10000,element);
    }
    buffer[0] ='\0';

    while(is_word_in_string("END_EVENT",buffer) == False_statement){
        if (is_word_in_string(":",buffer) == True_statement){
            compteur = 0;
            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }

            word_inter[compteur] = '\0';
            /*printf("l'element trouvé est : %s", word_inter);*/
            if (is_the_char_ptr_shwoing_the_samething(word_inter,"sauter")){
                /*
                
                    on a trouver l'objet on vérifie que l'objet utiliser est le bon 
                
                */

                found = 1;
                offset = compteur +1;
                compteur = 0;
                while(buffer[offset + compteur] !=':'){
                    word_inter[compteur] = buffer[offset + compteur];
                    compteur ++;
                }
                word_inter[compteur] = '\0';
                /*printf("l'objet a utilisé est : %s", word_inter);*/
                if (is_word_in_string(word_inter, prompt->content) && is_a_string_in_list_string(buffer,&evenement) == False_statement){
                    /*
                    
                    condition remplis donc on affiche la description si on a bien utiliser le bon objet
                    
                    */
                    offset += compteur+1;
                    compteur = 0;
                    while(buffer[offset + compteur] !=':'){
                        word_inter[compteur] = buffer[offset + compteur];
                        compteur ++;
                    }
                    word_inter[compteur] = '\0';
                    append_charptr(&event,word_inter);
                    append_str(&evenement,&event);
                    compteur = 0;
                    while(buffer[compteur] != '('){
                        /*
                        
                        on cherche le premier marqueur soit :(nonefound)

                        */
                        compteur ++;
                    }
                    compteur ++;
                    while(buffer[compteur] != '('){
                        /*
                        
                        on cherche le deuxieme marqueur soit :(iffound)

                        */
                        compteur ++;
                    }
                    while(buffer[compteur] != ':'){
                        /*
                        
                        on se place a début de ce que l'on est censer montrer
                        
                        */
                        compteur ++;
                    }
                    compteur ++;
                    compteur_chariot =0;
                    while(buffer[compteur] != ':' && buffer[compteur] != '+'&& buffer[compteur] != '*'){
                        /*
                        
                        on affiche le message jusqu'a attendre le marqueur de fin de message
                        
                        */
                        if(compteur_chariot == colonne){
                            /*
                            
                            avec cette boucle on s'assure que le message soit plus lisible
                            
                            */
                            printf("\n");
                            compteur_chariot =0;
                            if(buffer[compteur] != ' '){
                                printf("%c",buffer[compteur]);
                            }
                            compteur ++;
                                    
                        }
                        else{
                            printf("%c",buffer[compteur]);
                            compteur ++;
                            compteur_chariot ++;
                        }
                    }
                    printf("\n");
                    if (buffer[compteur] == '+'){
                        /*
                        
                        si on a comme marque de fin '+' on augmente le monde dans le quel le joueur évolue
                        
                        */
                        world ++;
                        waiting();
                    }
                    if (buffer[compteur] == '*'){
                        /*
                        
                        si on a comme marque de fin '+' on augmente le monde dans le quel le joueur évolue
                        
                        */
                        victory ++;
                        waiting();
                    }
                    break;

                }
                else if(is_word_in_string(word_inter, prompt->content) && is_a_string_in_list_string(buffer,&evenement) == True_statement){
                    /*
                    
                    si on utilise le bon objet mais l'on a déjà fais l'event...
                    
                    */
                    printf("je crois que je deviens fous a  tous faire en double...\n");
                    break;

                }
                else{
                    /*
                    
                    sinon on affiche le prompt associer a la mauvaise utilisation de l'objet...
                    
                    */
                    compteur =0;
                    while(buffer[compteur] != '('){
                        /*
                        
                        ici on se place au marqueur (nonefound)
                        
                        */
                     
                        compteur ++;
                    }
                    while(buffer[compteur] != ':'){
                        /*
                        
                        puis on se place au début de la 
                        
                        */
                       
                        compteur ++;
                    }
                    compteur ++;
                    compteur_chariot =0;
                    while(buffer[compteur] != ':'){
                        if(compteur_chariot == colonne){
                            printf("\n");
                            compteur_chariot =0;
                            if(buffer[compteur] != ' '){
                                printf("%c",buffer[compteur]);
                            }
                            compteur ++;
                                    
                        }
                        else{
                            printf("%c",buffer[compteur]);
                            compteur ++;
                            compteur_chariot ++;
                        }
                    
                    
                    }
                    printf("\n");
                    break;

            }




            }
    
        }
        fgets(buffer, 10000,element);
    } 
    if(found == 0){
        printf("je ne suis pas sur de comprendre l'objet que je suis censer saisir...\n");
    }
    

    fclose(element);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer_fichier);
    free_liste_char(&event);
}


void ouvrir_coffre_ou_porte(list_char * prompt){
    char buffer[10000] = "\0";

    char word_inter[100] = "\0";
    int compteur = 0;
    int offset = 0;
    int compteur_chariot =0;
    int found = 0;
    FILE *element;
    list_char fichier_a_ouvrir;
    list_char buffer_fichier;
    list_char event;

    /*
    
        création du stream
    
    */
   
   
    
    init_list_char(&event,"");
    init_list_char(&buffer_fichier,"");
    init_list_char(&fichier_a_ouvrir, "monde/");


    int_translator(&buffer_fichier,world);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,'/');

    int_translator(&buffer_fichier,position[0]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,',');

    int_translator(&buffer_fichier,position[1]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    /*
    
        ouverture du stream
    
    */
    element = fopen(fichier_a_ouvrir.content,"r");


    while(is_word_in_string("eventobject",buffer) == False_statement){
        fgets(buffer, 10000,element);
    }
    buffer[0] ='\0';

    while(is_word_in_string("END_EVENT",buffer) == False_statement){
        if (is_word_in_string(":",buffer) == True_statement){
            compteur = 0;
            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }

            word_inter[compteur] = '\0';
            /*printf("l'element trouvé est : %s", word_inter);*/
            if (is_the_char_ptr_shwoing_the_samething(word_inter,"ouvrir")){
                /*
                
                    on a trouver l'objet on vérifie que l'objet utiliser est le bon 
                
                */

                found = 1;
                offset = compteur +1;
                compteur = 0;
                while(buffer[offset + compteur] !=':'){
                    word_inter[compteur] = buffer[offset + compteur];
                    compteur ++;
                }
                word_inter[compteur] = '\0';
                /*printf("l'objet a utilisé est : %s", word_inter);*/
                if (is_word_in_string(word_inter, prompt->content) && is_a_string_in_list_string(buffer,&evenement) == False_statement){
                    /*
                    
                    condition remplis donc on affiche la description si on a bien utiliser le bon objet
                    
                    */
                    offset += compteur+1;
                    compteur = 0;
                    while(buffer[offset + compteur] !=':'){
                        word_inter[compteur] = buffer[offset + compteur];
                        compteur ++;
                    }
                    word_inter[compteur] = '\0';
                    append_charptr(&event,word_inter);
                    append_str(&evenement,&event);
                    compteur = 0;
                    while(buffer[compteur] != '('){
                        /*
                        
                        on cherche le premier marqueur soit :(nonefound)

                        */
                        compteur ++;
                    }
                    compteur ++;
                    while(buffer[compteur] != '('){
                        /*
                        
                        on cherche le deuxieme marqueur soit :(iffound)

                        */
                        compteur ++;
                    }
                    while(buffer[compteur] != ':'){
                        /*
                        
                        on se place a début de ce que l'on est censer montrer
                        
                        */
                        compteur ++;
                    }
                    compteur ++;
                    compteur_chariot =0;
                    while(buffer[compteur] != ':' && buffer[compteur] != '+'&& buffer[compteur] != '*'){
                        /*
                        
                        on affiche le message jusqu'a attendre le marqueur de fin de message
                        
                        */
                        if(compteur_chariot == colonne){
                            /*
                            
                            avec cette boucle on s'assure que le message soit plus lisible
                            
                            */
                            printf("\n");
                            compteur_chariot =0;
                            if(buffer[compteur] != ' '){
                                printf("%c",buffer[compteur]);
                            }
                            compteur ++;
                                    
                        }
                        else{
                            printf("%c",buffer[compteur]);
                            compteur ++;
                            compteur_chariot ++;
                        }
                    }
                    printf("\n");
                    if (buffer[compteur] == '+'){
                        /*
                        
                        si on a comme marque de fin '+' on augmente le monde dans le quel le joueur évolue
                        
                        */
                        world ++;
                        waiting();
                    }
                    if (buffer[compteur] == '*'){
                        /*
                        
                        si on a comme marque de fin '+' on augmente le monde dans le quel le joueur évolue
                        
                        */
                        victory ++;
                        waiting();
                    }
                    break;

                }
                else if(is_word_in_string(word_inter, prompt->content) && is_a_string_in_list_string(buffer,&evenement) == True_statement){
                    /*
                    
                    si on utilise le bon objet mais l'on a déjà fais l'event...
                    
                    */
                    printf("je crois que je deviens fous a  tous faire en double...\n");
                    break;

                }
                else{
                    /*
                    
                    sinon on affiche le prompt associer a la mauvaise utilisation de l'objet...
                    
                    */
                    compteur =0;
                    while(buffer[compteur] != '('){
                        /*
                        
                        ici on se place au marqueur (nonefound)
                        
                        */
                     
                        compteur ++;
                    }
                    while(buffer[compteur] != ':'){
                        /*
                        
                        puis on se place au début de la 
                        
                        */
                       
                        compteur ++;
                    }
                    compteur ++;
                    compteur_chariot =0;
                    while(buffer[compteur] != ':'){
                        if(compteur_chariot == colonne){
                            printf("\n");
                            compteur_chariot =0;
                            if(buffer[compteur] != ' '){
                                printf("%c",buffer[compteur]);
                            }
                            compteur ++;
                                    
                        }
                        else{
                            printf("%c",buffer[compteur]);
                            compteur ++;
                            compteur_chariot ++;
                        }
                    
                    
                    }
                    printf("\n");
                    break;

            }




            }
    
        }
        fgets(buffer, 10000,element);
    } 
    if(found == 0){
        printf("je ne suis pas sur de comprendre l'objet que je suis censer saisir...\n");
    }
    

    fclose(element);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer_fichier);
    free_liste_char(&event);
}



void print_pnj(FILE * streamfile){
    char buffer[10000] = "\0";
    char word_inter[100]= "\0" ;
    int compteur = 0;
    while(is_word_in_string("pnj",buffer) == False_statement){
        fgets(buffer, 10000,streamfile);
    }
    buffer[0] = '\0';
    printf("dans la pièce il y a :\n");
    while(is_word_in_string("END_PNJ",buffer) == False_statement){
        if(is_word_in_string(":",buffer) && buffer[0] !=':'){


            compteur = 0;


            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }


            word_inter[compteur] = '\0';
            if (is_a_string_in_list_string(word_inter,&inventaire) == False_statement){
                printf("%s", word_inter);
                printf("\n");
            }

            
        }
        fgets(buffer, 10000,streamfile);
    }
}


void shop(){

}
