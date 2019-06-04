#include "attoInterface.h"
#include "attoLangue.h"

void I_init(){
    initscr();
    noecho();
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLACK); //les deux lignes suivantes servent à initialiser les thèmes
        init_pair(2,COLOR_BLACK,COLOR_WHITE);
    }
    curs_set(0);
}

void I_displayListe(struct headFile* liste,int decades,int offset){ //TODO : à rendre plus propre
   for(int i=offset;i<=liste->nLignes;i++){
        mvprintw(i-offset,1,"%i",i); //Numéro de la ligne
        mvprintw(i-offset,2+decades,"|"); //séparation
        mvprintw(i-offset,3+decades,"%s",A_readListe(liste,i)); //ligne en elle même
    }
}

void I_displayInputBar(int max,int decades,int offset,char* nom){
    int col;  //les 3 lignes suivantes servent à connaitre les dimention de l'écran et ainsi écrire en bas sur toute la longueur sans problèmes
    int lig;
    getmaxyx(stdscr,lig,col);
    if(has_colors()){ //Si il y a de la couleur on fait une ligne de blanc, une  ligne de noir pour les informations , une ligne de blanc et la ligne pour les inputs
        attron(COLOR_PAIR(2));
        for(int i=0;i<col;i++){
            mvprintw(lig-4,i," ");
        }
        attron(COLOR_PAIR(1));
        for(int i=0;i<col;i++){
            mvprintw(lig-3,i," ");
        }
        attron(COLOR_PAIR(2));
        for(int i=0;i<col;i++){
            mvprintw(lig-2,i," ");
        }
        attron(COLOR_PAIR(1));
        for(int i=0;i<col;i++){
            mvprintw(lig-1,i," ");
        }
    }else{ //si il n'y a pas de couleur on remplace le blanc par des #
        for(int i=0;i<col;i++){
            mvprintw(lig-3,i," ");
            mvprintw(lig-4,i,"-");
            mvprintw(lig-1,i," ");
            mvprintw(lig-2,i,"-");
        }
    }
    mvprintw(lig-3,0,HOWTO);
    mvprintw(lig-3,NAME_PAD,nom);
    mvprintw(lig-3,col- 2 * (2+decades)," %i/%i  ",offset,max);
    move(lig-1,0);
}

void I_redraw(struct headFile* liste,int offset,char* nom){
    int decades=1; //Nombres de caractères à prévoir pour écrire le numéro de la ligne
    if(liste->nLignes > 9) decades++;
    if(liste->nLignes > 99) decades++;
    if(liste->nLignes > 999) decades++;
    if(liste->nLignes > 9999) decades++;
    clear();
    I_displayListe(liste,decades,offset);
    I_displayInputBar(liste->nLignes,decades,offset,nom);
    refresh();
}

void I_idle(struct headFile* liste,char* nomInit){
    char* nom = malloc(sizeof(char) * 1000);
    memcpy(nom,nomInit,strlen(nomInit));   
    int offset = 1;
    I_redraw(liste,offset,nom);
    int stop = 0;
    while(!stop){
        char c = getch();
      //mvprintw(1,1,"%i",c); //test
        if(c==65 && offset > 1){ //up  on bouge vers le début du fichier
            offset--;
            I_redraw(liste,offset,nom);
        }
        if(c==66 && offset < liste->nLignes){ //down on bouge vers le bas du fichier
            offset++;
            I_redraw(liste,offset,nom);
        }
        if(c==81){ //Q on arrète tout
            stop=1;
        }
        if(c==110){ //n on écrit une nouvelle ligne
            I_nouvelleLigne(liste);
            I_redraw(liste,offset,nom);
        }
        if(c==115){ //s on sauvegarde
            if(strcmp(nom,"")==0){
                I_rename(nom);
                I_redraw(liste,offset,nom);
            }
            while(A_writeFile(liste,nom)){ 
                I_redraw(liste,offset,nom);
                printw(INVALIDE);
                I_rename(nom);
            }
            I_redraw(liste,offset,nom);
        }
        if(c==101){ //e on change une ligne
            I_editLigne(liste);
            I_redraw(liste,offset,nom);
        }
    }
    echo();
    endwin();
}

void I_nouvelleLigne(struct headFile* liste){
    A_append(liste);
    curs_set(1);
    echo();
    char* ligneN = malloc(sizeof(char) * 4096);
    getstr(ligneN);
    strcat(ligneN,"\n"); //important pour réenregistrer ensuite
    A_writeListe(liste,liste->nLignes,ligneN);
    free(ligneN);
    noecho();
    curs_set(0);
}

void I_rename(char* nom){ //TODO : changer la manière dont la mémoire pour le nom est allouée pour pouvoir éviter de générer des array en boucle
    char* ret=malloc(sizeof(char) * 1024);
    printw(NAME);
    echo();
    curs_set(1);
    getstr(ret);
    noecho();
    curs_set(0);
    for(int i=0;i<1024;i++){
        *(nom+i)=0;
    }
    memcpy(nom,ret,strlen(ret));
    free(ret);
}

void I_editLigne(struct headFile* liste){
    int lignE = -1; //numero de la ligne à éditer
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    echo();
    curs_set(1);
    char* StrTmp = malloc(sizeof(char) * 4000); //sert d'abord à strocher l'input pour ne numéro de la ligne puis l'input pour le contine
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(lig-3,0,EDIT);
        move(lig-1,0); 
        getstr(StrTmp);
        lignE = atoi(StrTmp);
        for(int i=0;i<col;i++){ //On nétoie la zone d'input
            mvprintw(lig-1,i," ");
            mvprintw(lig-3,i," ");
        }
    }
    move(lig-1,0); //input pour le contenu de la ligne
    getstr(StrTmp);
    strcat(StrTmp,"\n");
    A_writeListe(liste,lignE,StrTmp);
    free(StrTmp);
    noecho();
    curs_set(0);
}

