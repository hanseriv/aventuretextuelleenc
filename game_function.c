#include <stdlib.h>
#include <stdio.h>
#include "fonctionutile.h"

#define colonne 90


extern list_string inventaire, objetdisponible, evenement;
extern int position[], oldposition[];
extern int world, oldworld,error;

void waiting(){
    /*
    
    fonction qui stop le programme temporairement pour laisser
    le temps a l'utilisateur de lire.
    
    */
    list_char prompt;
    init_list_char(&prompt,"");
    printf("please press <enter> to continue...");
    input(&prompt);
    free_liste_char(&prompt);
}


void is_there_room_around_you(){
    FILE *element;
    list_char fichier_a_ouvrir;
    list_char buffer_fichier;
    init_list_char(&fichier_a_ouvrir, "monde");
    
    init_list_char(&buffer_fichier,"");
    init_list_char(&fichier_a_ouvrir, "monde/");
    int_translator(&buffer_fichier,world);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,'/');
    int_translator(&buffer_fichier,position[0] + 1);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,',');
    int_translator(&buffer_fichier,position[1]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    element = fopen(fichier_a_ouvrir.content,"r");


    if(element != NULL){
        printf("il y a une piece au Nord...\n") ;
        fclose(element);
    }
    reec_list_char(&buffer_fichier);
    reec_list_char(&fichier_a_ouvrir);
    append_charptr(&fichier_a_ouvrir, "monde/");
    int_translator(&buffer_fichier,world);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,'/');
    int_translator(&buffer_fichier,position[0] - 1);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,',');
    int_translator(&buffer_fichier,position[1]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    element = fopen(fichier_a_ouvrir.content,"r");

    if(element != NULL){
        printf("il y a une piece au Sud...\n") ;
        fclose(element);
    }

    reec_list_char(&buffer_fichier);
    reec_list_char(&fichier_a_ouvrir);
    append_charptr(&fichier_a_ouvrir, "monde/");
    int_translator(&buffer_fichier,world);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,'/');
    int_translator(&buffer_fichier,position[0]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,',');
    int_translator(&buffer_fichier,position[1] - 1);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    element = fopen(fichier_a_ouvrir.content,"r");

    if(element != NULL){
        printf("il y a une piece au Est...\n") ;
        fclose(element);
    }

    reec_list_char(&buffer_fichier);
    reec_list_char(&fichier_a_ouvrir);
    append_charptr(&fichier_a_ouvrir, "monde/");
    int_translator(&buffer_fichier,world);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,'/');
    int_translator(&buffer_fichier,position[0]);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_char(&fichier_a_ouvrir,',');
    int_translator(&buffer_fichier,position[1] + 1);
    append_charptr(&fichier_a_ouvrir, buffer_fichier.content);
    append_charptr(&fichier_a_ouvrir, ".piece");
    element = fopen(fichier_a_ouvrir.content,"r");

    if(element != NULL){
        printf("il y a une piece au Ouest...\n") ;
        fclose(element);
    }
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer_fichier);

}


void intro_reader(){
    /*
    
    fonction qui lie les intros du monde actuelle

    */
    FILE  *element;
    list_char fichier_a_ouvrir;
    list_char buffer;
    oldworld = world;
    char buffer_c ='\0';
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
        buffer_c = fgetc(element);
        while(buffer_c != EOF){
            printf("%c", buffer_c);
            buffer_c = fgetc(element);
        }
    }
    waiting();
    fclose(element);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer);
}


void description_reader(FILE * streamfile){
    /*
    
    fonction qui lie automatiquement les descriptions des pieces
    
    */
    char buffer[1000] ="";
    while(is_word_in_string("description",buffer) == False_statement){
        fgets(buffer, 1000,streamfile);
    }
    

    buffer[0] = '\0';
    while(is_word_in_string("END_DESC",buffer) == False_statement){
        
        printf("%s",buffer);
        
        fgets(buffer, 1000,streamfile);
    }


}

void print_object(FILE * streamfile){
    char buffer[1000] = "\0";
    char word_inter[100]= "\0" ;
    int compteur = 0;
    while(is_word_in_string("objet",buffer) == False_statement){
        fgets(buffer, 1000,streamfile);
    }
    buffer[0] = '\0';
    printf("dans la pièce il y a :\n");
    while(is_word_in_string("END_OBJ",buffer) == False_statement){
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
        fgets(buffer, 1000,streamfile);
    }

    while(is_word_in_string("eventobject",buffer) == False_statement){
        fgets(buffer, 1000,streamfile);
    }
    buffer[0] = '\0';
    while(is_word_in_string("END_EVENT",buffer) == False_statement){
        if(is_word_in_string(":",buffer) && buffer[0] !=':'){
            compteur = 0;
            while(buffer[compteur] !=':'){
                printf("%c",buffer[compteur]);
                compteur ++;
            }
            printf("\n");
        }
        fgets(buffer, 1000,streamfile);
    }

}

void print_object_description(FILE * streamfile,list_char * prompt){
    char buffer[1000] ="\0";
    char inter_buffer[20] = "";
    char word_inter[100] ="\0" ;
    int compteur = 0;
    int inter_compteur =0;
    int found = 0;
    int compteur_chariot = 0;

    /*
    
    on place le curseur sur la rebrique des objets

    */

    while(is_word_in_string("objet",buffer) == False_statement){
        fgets(buffer, 1000,streamfile);
    }
    /*
    
    on reinitialise la basile pour eviter d'afficher la dite rebirique et cassé le 4eme mur
    
    */


    buffer[0] = '\0';
    /*
    
    on lie chaque ligne jusqu'a la balise END_OBJ pour vérifier s'il y a l'objet 
    
    */
    while(is_word_in_string("END_OBJ",buffer) == False_statement){
        if(is_word_in_string(":",buffer) && buffer[0] !=':'){

            compteur = 0;
            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }

            word_inter[compteur] = '\0';



            if(is_word_in_string(word_inter,prompt->content) == True_statement && is_a_string_in_list_string(word_inter,&inventaire) == False_statement){
                buffer[0] ='\0';
                while(is_word_in_string(":",buffer)!= True_statement){
                    printf("%s", buffer);
                    fgets(buffer, 1000,streamfile);
                }
                found = 1;
                break;
            }
            else if(is_a_string_in_list_string(word_inter,&inventaire)) {
                found =1;
                printf("j\'ai pris cet objet...\n");
                break;
            }

            


        }
        fgets(buffer, 1000,streamfile);

    }
    /*
    
    on se place jusqu'a la balise eventobject
    
    */

    while(is_word_in_string("eventobject",buffer) == False_statement){
        fgets(buffer, 1000,streamfile);
    }
    /*
    
    on reinitialise la basile pour eviter d'afficher la dite rebirique et cassé le 4eme mur
    
    */
    buffer[0] = '\0';
    while(is_word_in_string("END_EVENT",buffer) == False_statement){
        if(is_word_in_string(":",buffer) && buffer[0] !=':'){

            compteur = 0;
            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }

            word_inter[compteur] = '\0';

            if(is_word_in_string(word_inter,prompt->content) == True_statement){
                /*printf("I HAVE FOUND THE OBJECT MOTHERFUCKER\n");*/
                buffer[0] ='\0';
                compteur = 0;
                inter_compteur =0;
                while(buffer[compteur] != '\n'){
                    if (buffer[compteur] == ':'){
                        inter_buffer[inter_compteur] = '\0';

                        if(is_word_in_string("description", inter_buffer)){
                            compteur ++;
                            while (buffer[compteur] !=':'){
                                
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
                            found = 1;
                            break;
                        }
                        else{
                            inter_compteur = 0;
                        }

                    }
                    else{
                        inter_buffer[inter_compteur] = buffer[compteur];
                        
                        inter_compteur ++;
                    }
                    compteur ++;


                }
            }
        }


        fgets(buffer, 1000,streamfile);
    }
    /*
    
    si on a rien trouvé on le dis a l'utilisateur.
    
    */

    if (found == 0){
        printf("je ne crois ne pas comprendre ce que je suis censer regarder...\n");
    }
}



int can_i_enter(FILE * filestream){
    /*
    
    fonction qui teste si l'on a tous les evenements necessaires pour passer une porte
    
    */
    char buffer[1000] = "";
    while(is_word_in_string("conditionentre", buffer) == False_statement){
        fgets(buffer,1000,filestream);
    }
    buffer[0] ='\0';
    while(is_word_in_string("END_COND", buffer) == False_statement){
        if(is_a_string_in_list_string(buffer,&evenement) == False_statement && buffer[0] !='\0'){
                return False_statement;
        }
        fgets(buffer,1000,filestream);
        
    }

    return True_statement;

}




int fonction_deplacement(list_char * prompt){
    /*
    
        fonction qui gèrent les déplacements

    */
    FILE *element;
    list_char fichier_a_ouvrir;

    if (is_word_in_string("nord",prompt->content)){
        position[0] ++;
    }
    else if (is_word_in_string("sud",prompt->content)){
        position[0] --;
    }
    else if (is_word_in_string("est", prompt->content) && is_word_in_string("ouest" , prompt->content) == False_statement){
        position[1] --;
    }
    else if (is_word_in_string("ouest" , prompt->content)){
        position[1] ++;
    }
    else{
        printf("deplacement non valide veuiller utiliser les coordonnees (sud, nord...)\n");
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
        if (can_i_enter(element)){
            oldposition[0] = position[0];
            oldposition[1] = position[1];
            rewind(element);
            description_reader(element);
        }
        else{
            position[0] = oldposition[0];
            position[1] = oldposition[1];
            printf("je ne crois pas pouvoir le faire malheureusment...\n");
        }
        fclose(element);
        

    }
    free_liste_char(&buffer);
    free_liste_char(&fichier_a_ouvrir);
    return 0;
}

void print_inventary(){
    /*
    
    fonction qui affiche l'inventaire de l'utilisateur
    
    */
    unsigned int compteur;
    for(compteur = 0; compteur != inventaire.len; compteur ++){
        printf("%s\n",inventaire.content[compteur].content);
    }
    if (compteur == 0){
        printf("comme toujours je n'ai rien...\n");
    }
}




void took(FILE * streamfile, list_char * prompt){
    /*
    
    fonction qui vérifie si l'utilisateur peut prendre l'objet 

    */
    char buffer[1000] = "\0";
    list_char buffer_obj ;
    init_list_char(&buffer_obj,"");
    char word_inter[20] = "\0";
    int found = 0;
    int compteur = 0;
    while(is_word_in_string("objet",buffer) == False_statement){
        fgets(buffer, 1000,streamfile);
    }
    buffer[0] = '\0';
    while(is_word_in_string("END_OBJ",buffer) == False_statement){
        if(is_word_in_string(":",buffer) && buffer[0] !=':'){

            compteur = 0;
            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }

            word_inter[compteur] = '\0';



            if(is_word_in_string(word_inter,prompt->content) == True_statement && is_a_string_in_list_string(word_inter,&inventaire) == False_statement){
                buffer[0] ='\0';
                while(is_word_in_string(":",buffer)!= True_statement){
                    fgets(buffer, 1000,streamfile);
                }
                if (is_word_in_string("1",buffer) == True_statement)
                {
                    append_charptr(&buffer_obj,word_inter);
                    
                    append_str(&inventaire,&buffer_obj);
                    found = 2;

                }
                else{
                    found = 1;
                }
                break;

            }


        }
        fgets(buffer, 1000,streamfile);

    }
    if (found == 0){
        printf("suis-je censer materialiser cet objet et le prendre ?...\n");
    }
    else if (found == 1)
    {
        printf("comment suis-je censer porter cela ? je n'en ai ni l'envie...ni la force...\n");
    }
    else{
        printf("vous avez pris l\'objet\n");
    }
    free_liste_char(&buffer_obj);
}









void fonction_prendre(list_char * prompt){
    /*
    
    fonction qui vérifie si l'utilisateur peut prendre l'objet 

    */

    FILE *element;
    list_char fichier_a_ouvrir;
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
    element = fopen(fichier_a_ouvrir.content,"r");
    if(element == NULL){
        printf("cannot open the file...please contact the programming team...\n");
        error = 1;
    }
    else{
        took(element,prompt);
        fclose(element);
    }
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer);
}








void fonction_regarder(list_char * prompt){
    /*
    
    fonction qui gèrent les descriptions de l'environement

    */

    FILE *element;
    list_char fichier_a_ouvrir;
    init_list_char(&fichier_a_ouvrir, "monde");
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
    element = fopen(fichier_a_ouvrir.content,"r");

    if(element == NULL){
        printf("impossible to open the said file...\n");
        error =1;
    }
    else if (is_word_in_string("piece" , prompt->content)){
        description_reader(element);
        
    }
    else if (is_word_in_string("objet" , prompt->content) || is_word_in_string("objets" , prompt->content)){
        print_object(element);
    }
    else if (is_word_in_string("inventaire", prompt->content) || is_word_in_string("moi", prompt->content) ||is_word_in_string("m\'", prompt->content)){
        print_inventary();
    }
    else if (is_word_in_string("alentour", prompt->content) || is_word_in_string("autour", prompt->content)){
        is_there_room_around_you();
    }
    else{
        print_object_description(element,prompt);
        
    }

    fclose(element);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer);

}



void fonction_parler(list_char * prompt){
    char buffer[1000] = "\0";

    char word_inter[100] = "\0";
    int compteur = 0;

    int found = 0;
  
    FILE *element;
    list_char fichier_a_ouvrir;

    list_char buffer_fichier;
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
    element = fopen(fichier_a_ouvrir.content,"r");

    if(element == NULL){
        printf("impossible to open the said file...\n");
        error =1;
    }
    else{
        
    while(is_word_in_string("pnj",buffer) == False_statement){
        fgets(buffer, 1000,element);
    }
    /*
    
    on lie chaque ligne jusqu'a la balise END_OBJ pour vérifier s'il y a l'objet 
    
    */
    while(is_word_in_string("END_PNJ",buffer) == False_statement){
        if(is_word_in_string(":",buffer) && buffer[0] !=':'){

            compteur = 0;
            while(buffer[compteur] !=':'){
                word_inter[compteur] = buffer[compteur];
                compteur ++;
            }

            word_inter[compteur] = '\0';



            if(is_word_in_string(word_inter,prompt->content) == True_statement){
                printf("%s :\n",word_inter);
                buffer[0] ='\0';
                while(is_word_in_string(":",buffer)!= True_statement){
                    printf("%s", buffer);
                    fgets(buffer, 1000,element);
                }
                found = 1;
                break;
            }


            


        }
        fgets(buffer, 1000,element);

    }
    if(found == 0){
        printf("je ne vois pas cette personne...peut-etre mon imagination\n");
    }
    fclose(element);
    }
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer_fichier);
}



void fonction_utiliser(list_char * prompt){
    char buffer[1000] = "\0";

    char word_inter[100] = "\0";
    int compteur = 0;
    int offset = 0;

    int found = 0;

    /*
    
        création du stream
    
    */
    FILE *element;
    list_char fichier_a_ouvrir;
    list_char buffer_fichier;
    list_char event;
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
        fgets(buffer, 1000,element);
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
            if (is_word_in_string(word_inter, prompt->content)){
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
                if (is_word_in_string(word_inter, prompt->content)){
                    offset += compteur+1;
                    compteur = 0;
                    while(buffer[offset + compteur] !=':'){
                        word_inter[compteur] = buffer[offset + compteur];
                        compteur ++;
                    }
                    word_inter[compteur] = '\0';
                    printf("l'evenement est : %s\n", word_inter);
                    append_charptr(&event,word_inter);
                    append_str(&evenement,&event);
                    compteur = 0;
                    while(buffer[compteur] != '('){
                        compteur ++;
                    }
                    compteur ++;
                    while(buffer[compteur] != '('){
                        compteur ++;
                    }
                    while(buffer[compteur] != ':'){
                        compteur ++;
                    }
                    compteur ++;
                    while(buffer[compteur] != ':'){
                        printf("%c",buffer[compteur]);
                        compteur ++;
                    }
                    printf("\n");
                    break;

                }
                else{

                    compteur =0;
                    while(buffer[compteur] != '('){
                        compteur ++;
                    }
                    while(buffer[compteur] != ':'){
                        compteur ++;
                    }
                    compteur ++;
                    while(buffer[compteur] != ':'){
                        printf("%c",buffer[compteur]);
                        compteur ++;
                    }
                    printf("\n");
                    break;
                }

            }




            }
            fgets(buffer, 1000,element);
    
        } 
    if(found == 0){
        printf("je ne suis pas sur de comprendre l'objet que je suis censer saisir...\n");
    }


    fclose(element);
    free_liste_char(&fichier_a_ouvrir);
    free_liste_char(&buffer_fichier);
    free_liste_char(&event);
}