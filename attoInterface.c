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

void I_displayListe(struct headFile* liste,int decades,offstruct* offset){ 
    int lig = getmaxy(stdscr);
    int max; //On ne veut pas avoir besoin d'afficher des lignes qui sont plus basse que l'écran.
    if(lig+offset->x -4 > liste->nLignes) max = liste->nLignes;
    else max = lig + offset->x - 4;    
    for(int i=offset->x ;i<=max;i++){
        for(int j=0;j<decades+3;j++){
            mvprintw(i-offset->x ,j," ");
        }
        mvprintw(i-offset->x,1,"%i",i);//Numéro de la ligne
        mvprintw(i-offset->x,2+decades,"|"); //séparation
        mvprintw(i-offset->x,3+decades,"%s",A_readListe(liste,i)+offset->y); //ligne en elle même
    }
}

void I_displayInputBar(int max,int decades,offstruct* offset,char* nom){
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
    mvprintw(lig-3,col- 2 * (2+decades)," %i/%i  ",offset->x,max);
    move(lig-1,0);
}

void I_redraw(struct headFile* liste,offstruct* offset,char* nom){
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
    offstruct* offset = malloc(sizeof(offstruct));   
    offset->x = 1; //décalage haut/bas
    offset->y = 0; //décalage droite/gauche
    I_redraw(liste,offset,nom);
    int stop = 0;
    while(!stop){
        int c = getch();
    //mvprintw(1,1,"%i",c); //test
        if(c==65 && offset->x > 1){ //up  on bouge vers le début du fichier
            offset->x--;
            I_redraw(liste,offset,nom);
        }
        if(c==66 && offset->x < liste->nLignes){ //down on bouge vers le bas du fichier
            offset->x++;
            I_redraw(liste,offset,nom);
        }
        if(c==67 && offset->y < 4000){ //flèche droite : on se décale
            offset->y++;
            I_redraw(liste,offset,nom);
        }
        if(c==68 && offset->y > 0){ //flèche gauche : on se décale
            offset->y--;
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
        if(c==100){ //d on supprime une ligne
           I_delLigne(liste);
           I_redraw(liste,offset,nom);
        }
        if(c==105) { //i on insère une ligne
            I_insert(liste);
            I_redraw(liste,offset,nom);
        }
        if(c==112) { //p on affiche une ligne
            I_printLigne(liste,offset,nom);
        }
        if(c==106){ //j on saute vers une autre ligne
            I_jumpLigne(liste,offset);
            I_redraw(liste,offset,nom);
        }
        if(c==104) { //h on affiche l'aide
            stop = I_help(liste,offset,nom);
            I_redraw(liste,offset,nom);
        } 
    }
    echo();
    endwin();
}

int I_help(struct headFile* liste,offstruct* offset,char* nom){
    int HelpIligne = 0; //Permet de voir où on en est dans le menu d'aide
    char *HelpList[9] = {HELP_QUIT,HELP_SAVE,HELP_NEW_LINE,HELP_DEL_LINE,HELP_OPEN_LINE,HELP_PRINT,HELP_JUMP,HELP_ARROWS,HELP_ARROWS_SIDE};//stoque les message d'aide pour un accès facile
    int lig;
    int col;
    getmaxyx(stdscr,lig,col);
    int stop = 0;
    while(!stop){
        I_cleanBas(col,lig);
        mvprintw(lig-3,0,HELP_INFO_HELP);
        mvprintw(lig-1,0,"%s",HelpList[HelpIligne]);
        refresh();
        int c = getch();
    //mvprintw(1,1,"%i",c); //test
        if(c==65 && offset->x > 1){ //up  on bouge vers le début du fichier
            offset->x--;
            I_redraw(liste,offset,nom);
        }
        if(c==66 && offset->x < liste->nLignes){ //down on bouge vers le bas du fichier
            offset->x++;
            I_redraw(liste,offset,nom);
        }
        if(c==67 && offset->y < 4000){ //flèche droite : on se décale
            offset->y++;
            I_redraw(liste,offset,nom);
        }
        if(c==68 && offset->y > 0){ //flèche gauche : on se décale
            offset->y--;
            I_redraw(liste,offset,nom);
        }
        if(c==81){ //Q on arrète tout
            stop=1;
            return stop;
        }
        if(c==110){ //n on écrit une nouvelle ligne
            I_cleanBas(col,lig);
            move(lig-1,0);
            I_nouvelleLigne(liste);
            I_redraw(liste,offset,nom);
            return stop;
        }
        if(c==115){ //s on sauvegarde
            I_cleanBas(col,lig);
            move(lig-1,0);
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
            return stop;
        }
        if(c==101){ //e on change une ligne
            I_cleanBas(col,lig);
            I_editLigne(liste);
            I_redraw(liste,offset,nom);
            return stop;
        }
        if(c==100){ //d on supprime une ligne
            I_cleanBas(col,lig);
           I_delLigne(liste);
           I_redraw(liste,offset,nom);
           return stop;
        }
        if(c==105) { //i on insère une ligne
            I_cleanBas(col,lig);
            I_insert(liste);
            I_redraw(liste,offset,nom);
            return stop;
        }
        if(c==112) { //p on affiche une ligne
            I_printLigne(liste,offset,nom);
        }
        if(c==106){ //j on saute vers une autre ligne
            I_jumpLigne(liste,offset);
            I_redraw(liste,offset,nom);
        }
        if(c==10){ //On apuie sur enter pour voir le message d'aide suivant
            HelpIligne++;
            if(HelpIligne==9) return stop;
        }
        if(c==127){ //on apuie sur echap pour retourner en arrière sur l'aide
            HelpIligne--;
            if(HelpIligne<0) return stop;
        }
    }
    return 0; //Si au cas où on arrive là (normalement impossible) on errète pas le programme.
}

void I_printLigne(struct headFile* liste,offstruct* offset,char* nom){
    int lignE = -1; //numero de la ligne à afficher
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    echo();
    curs_set(1);
    I_cleanBas(col,lig);
    refresh();
    char* StrTmp = malloc(sizeof(char) * 4000); //sert à strocker l'input pour ne numéro de la ligne
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(lig-3,0,PRINT);
        move(lig-1,0); 
        getstr(StrTmp);
        if(strcmp(StrTmp,"") == 0){ I_cleanBas(col,lig); return;}
        lignE = atoi(StrTmp);
        I_cleanBas(col,lig);
    }
    mvprintw(lig-1,0,A_readListe(liste,lignE)); //On affiche la ligne
    return;
}

void I_jumpLigne(struct headFile* liste,offstruct* offset){
    int lignE = -1; //numero de la ligne à atteindre
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    echo();
    curs_set(1);
    I_cleanBas(col,lig);
    refresh();
    char* StrTmp = malloc(sizeof(char) * 4000); //sert à strocker l'input pour ne numéro de la ligne
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(lig-3,0,JUMP);
        move(lig-1,0); 
        getstr(StrTmp);
        if(strcmp(StrTmp,"") == 0) return;
        lignE = atoi(StrTmp);
        I_cleanBas(col,lig);
    }
    offset->x = lignE;
    return;
}

void I_nouvelleLigne(struct headFile* liste){
    A_append(liste);
    curs_set(1);
    echo();
    char* ligneN = malloc(sizeof(char) * 4096);
    getstr(ligneN);
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
    I_cleanBas(col,lig);
    refresh();
    char* StrTmp = malloc(sizeof(char) * 4000); //sert d'abord à strocher l'input pour ne numéro de la ligne puis l'input pour le contine
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(lig-3,0,EDIT);
        move(lig-1,0); 
        getstr(StrTmp);
        if(strcmp(StrTmp,"") == 0) return;
        lignE = atoi(StrTmp);
        I_cleanBas(col,lig);
    }
    mvprintw(lig-3,0,A_readListe(liste,lignE)); //On affiche l'ancienne ligne
    move(lig-1,0); //input pour le contenu de la ligne
    editString(A_readListe(liste,lignE),4090,lig-1,0,col); 
    free(StrTmp);
    noecho();
    curs_set(0);
}

void I_delLigne(struct headFile* liste){
    int lignE = -1; //numero de la ligne à suprimer
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    echo();
    curs_set(1);
    I_cleanBas(col,lig);
    refresh();
    char* StrTmp = malloc(sizeof(char) * 4000); //sert d'abord à strocher l'input pour ne numéro de la ligne puis l'input pour le contine
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(lig-3,0,DEL);
        move(lig-1,0); 
        getstr(StrTmp);
        if(strcmp(StrTmp,"") == 0) return;
        lignE = atoi(StrTmp);
        I_cleanBas(col,lig);
    }
    A_supression(liste,lignE);
    noecho();
    curs_set(0);
    free(StrTmp);
}

void I_insert(struct headFile* liste){
    int lignE = -1; //position de la ligne à insérer
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    echo();
    curs_set(1);
    I_cleanBas(col,lig);
    refresh();
    char* StrTmp = malloc(sizeof(char) * 4000); //sert d'abord à strocher l'input pour ne numéro de la ligne puis l'input pour le contine
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(lig-3,0,INSERT);
        move(lig-1,0); 
        getstr(StrTmp);
        if(strcmp(StrTmp,"") == 0) return;
        lignE = atoi(StrTmp);
        I_cleanBas(col,lig); 
    }
    move(lig-1,0);
    getstr(StrTmp);
    noecho();
    curs_set(0);
    A_insertion(liste,lignE);
    A_writeListe(liste,lignE,StrTmp);
    free(StrTmp);
}

void I_cleanBas(int col,int lig){   
    for(int i=0;i<col;i++){ //On nétoie la zone d'input
        mvprintw(lig-1,i," ");
        mvprintw(lig-3,i," ");
    }
}

