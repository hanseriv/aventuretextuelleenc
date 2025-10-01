#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "fonctionutile.h"
#include "game_function.h"
#include "extended_game_function.h"



int pv_joueur_max =10;
int pv_joueur = 10; 
int exp_joueur = 0;
int niveau_joueur = 0;
int att = 2;
int att_stat = 20;
int run_stat =10;
extern list_string inventaire, objetdisponible, evenement;
extern int position[], oldposition[];
extern int world, oldworld,error;
extern short victory;



void monter_niveau(void){
    att_stat += 2;
    niveau_joueur ++;
    pv_joueur_max += 1;
    if (niveau_joueur%5 == 0){
        att += 1;
    }
    printf("avec tous ces combats vous avez gagne un niveau...\nbravo je suppose...\n");
}

void get_monster(int *pv_ennemi,int* att_enn, list_char * nom ){
    /*
    
        création du stream
    
    */
    char buffer_lecture[10000];
    char word_buf[100];
    int compteur =0;
   
    FILE *element;
    list_char fichier_a_ouvrir;
    list_char buffer_fichier;

    list_string monster;
    init_list_string(&monster);
    
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
    free_liste_char(&buffer_fichier);
    init_list_char(&buffer_fichier,"");
    while(!is_word_in_string("ennemy",buffer_lecture)){
        fgets(buffer_lecture,10000,element);
    }
    buffer_lecture[0] ='\0';
    while(!is_word_in_string("END_ENNEMY",buffer_lecture)){
        if(is_word_in_string(":",buffer_lecture) && buffer_lecture[0] != ':'){
            compteur =0;
            while(buffer_lecture[compteur]!= ':'){
                word_buf[compteur] = buffer_lecture[compteur];
                compteur++;
            }
            word_buf[compteur]='\0';
            append_charptr(&buffer_fichier,word_buf);
            append_str(&monster,&buffer_fichier);
        }
        fgets(buffer_lecture,10000,element);
    }
    append_charptr(nom, monster.content[rand()%(monster.len-2)].content);
    free_liste_string(&monster);
    rewind(element);
    while(!is_word_in_string("ennemy",buffer_lecture)){
        fgets(buffer_lecture,10000,element);
    }
    buffer_lecture[0] ='\0';
    while(!is_word_in_string("END_ENNEMY",buffer_lecture)){
        if(is_word_in_string(nom->content,buffer_lecture) && is_word_in_string(":",buffer_lecture)){
            buffer_lecture[0]= '\0';
            while(!is_word_in_string(":",buffer_lecture)){
                printf("%s", buffer_lecture);
                fgets(buffer_lecture,10000,element);
            }
            break;
        }
        fgets(buffer_lecture,10000,element);
    }
    fclose(element);
    element = fopen("monster.monster","r");
    if(element == NULL){
        printf("unavailability of the monster bible...please make sure that all file were download or are in the same file...\n");
        error = 1;
    }
    else{
        buffer_lecture[0] ='\0';
        while(!is_word_in_string(nom->content,buffer_lecture)){
            fgets(buffer_lecture,10000,element);
        }
        
    }


    /*
    
    fermeture du stream...
    
    */
    fclose(element);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer_fichier);
}




void attaque_function(void){
    char prompt[2];
    int chance = 0;
    short end_combat = 0;
    int pv_enne;
    int att_enn;
    list_char nom_ennemi;
    init_list_char(&nom_ennemi,"");

    get_monster(&pv_enne,&att_enn,&nom_ennemi);
    srand(time(NULL));
    
    






    /*
    
    action joueur

    */
   while(1){
    do
    {
        printf("(1)attaquer (2)fuir\n");
        printf(":>");
        fgets(prompt,1,stdin);
    } while (prompt[0] != '1' && prompt[0] != '2');
    chance = rand()%100;

    if(prompt[0] == '1'){
        
        if(chance < run_stat){
            end_combat ++;
        }
    } 
    else{
        if(chance < att_stat && chance>5){
            printf("vous infligez %i dégat...\n",att);
            pv_enne -= att;
            
        }
        else if(chance <= 5){
            printf("c\'est une attaque critique !!!\nvous infligez %i dégat...\n",2* att);
            pv_enne -= 2* att;
        }
        else{
            printf("votre attaque rate...\nvous infligez 0 dégat...\n");
        }
        if(pv_enne <= 0){
            end_combat = 2;
        }
    }
    if (end_combat != 0){
        break;
    }
    printf("c'est au tour de %s...\n",nom_ennemi.content );
    chance = rand()%100;
    if(pv_enne < 2){
        printf("%s essaie de fuir\nla peur de mourir l'envahie...\n", nom_ennemi.content);
        if(chance < 20){
            printf("prenant ses jambes a son coup %s parvient a fuir vous laissant seul...\n", nom_ennemi.content);
            end_combat = 3;
        }
        else{
            printf("malgres tous ces effort...l'effroi empeche %s de fuir\nil ne parvient pas a se resaisir pour fuir...\n", nom_ennemi.content);
        }
    }
    else{
        if(chance < -niveau_joueur >> 1){
            printf("votre jour de chance n'est pas aujourd'hui...\n%s vous inflige %i dégats...\n", nom_ennemi.content, att_enn);
            pv_joueur -= att_enn;
        }
        else{
            printf("malgres tous ces effort...%s ne vous atteint pas\nla chance semble etre de votre cote...\n", nom_ennemi.content);
        }
        if(pv_joueur <= 0){
            end_combat = 4;
        }
    }
}
    free_liste_char(&nom_ennemi);


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


void shop(void){

}
