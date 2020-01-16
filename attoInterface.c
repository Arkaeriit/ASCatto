#include "attoInterface.h"
#include "attoLangue.h"

void I_init(){
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    setlocale(LC_ALL,"");
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLACK); //les deux lignes suivantes servent à initialiser les thèmes
        init_pair(2,COLOR_BLACK,COLOR_WHITE);
    }
    curs_set(0);
}

void I_displayListe(const struct headFile* liste,int decades,offstruct* offset){ 
    int lig,col;
    getmaxyx(stdscr,lig,col);
    int max; //On ne veut pas avoir besoin d'afficher des lignes qui sont plus basse que l'écran.
    if(lig+offset->x -4 > liste->nLignes) max = liste->nLignes;
    else max = lig + offset->x - 4;    
    if(max == 0) return; //Nothing to do
    if(offset->x == 0) offset->x = 1; //On empèche d'accéder à des zones impossibles
    char* tmp = malloc(sizeof(char) * LINESIZE);
    for(int i=offset->x ;i<=max;i++){
        for(int j=0;j<decades+3;j++){
            mvprintw(i-offset->x ,j," ");
        }
        mvprintw(i-offset->x,1,"%i",i);//Numéro de la ligne
        mvprintw(i-offset->x,2+decades,"|"); //séparation
        memset(tmp,0, LINESIZE);
        strcpy(tmp,A_readListe(liste,i)+offset->y); //On fait en sorte de ne récupérer que ce qui nous interesse pour éviter que du texte ne dépasse sur la ligne d'en dessous
        tmp[col] = 0;
        mvprintw(i-offset->x,3+decades,"%s",tmp); //ligne en elle même
    }
    free(tmp);
}

void I_displayInputBar(int max,int decades,const offstruct* offset,const char* nom){
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

void I_redraw(const struct headFile* liste,offstruct* offset,const char* nom){
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

void I_idle(struct headFile* liste,const char* nomInit){
    bool isHelp = false;
    int HelpLigne = 0; //Permet de voir où on en est dans le menu d'aide
    char *HelpList[NUMBER_OF_HELP] = {HELP_QUIT, HELP_SAVE, HELP_NEW_LINE, HELP_DEL_LINE, HELP_OPEN_LINE, HELP_PRINT, HELP_JUMP, HELP_SWAP, HELP_ARROWS, HELP_ARROWS_SIDE};//stoque les message
    
    char* nom = malloc(sizeof(char) * FILENAMESIZE);
    strcpy(nom,nomInit);
    offstruct* offset = malloc(sizeof(offstruct));   
    offset->x = 1; //décalage haut/bas
    offset->y = 0; //décalage droite/gauche
    I_redraw(liste,offset,nom);
    int stop = 0;
    while(!stop){
        if(isHelp){
            int lig;
            int col;
            getmaxyx(stdscr,lig,col);
            I_cleanBas(col,lig);
            mvprintw(lig-3,0,HELP_INFO_HELP);
            mvprintw(lig-1,0,"%s",HelpList[HelpLigne]);
        }
        refresh();
        int c = getch();
    //mvprintw(1,1,"%i",c); //test
        if(c==KEY_UP && offset->x > 1){ //up  on bouge vers le début du fichier
            offset->x--;
            I_redraw(liste,offset,nom);
        }
        if(c==KEY_DOWN && offset->x < liste->nLignes){ //down on bouge vers le bas du fichier
            offset->x++;
            I_redraw(liste,offset,nom);
        }
        if(c==KEY_RIGHT && offset->y < LINESIZE){ //flèche droite : on se décale
            offset->y++;
            I_redraw(liste,offset,nom);
        }
        if(c==KEY_LEFT && offset->y > 0){ //flèche gauche : on se décale
            offset->y--;
            I_redraw(liste,offset,nom);
        }
        if(c=='Q'){ //Q on arrète tout
            stop=1;
        }
        if(c=='n'){ //n on écrit une nouvelle ligne
            I_nouvelleLigne(liste);
            I_redraw(liste,offset,nom);
        }
        if(c=='s'){ //s on sauvegarde
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
        if(c=='e'){ //e on change une ligne
            I_editLigne(liste);
            I_redraw(liste,offset,nom);
        }
        if(c=='d'){ //d on supprime une ligne
           I_delLigne(liste);
           I_redraw(liste,offset,nom);
        }
        if(c=='i') { //i on insère une ligne
            I_insert(liste);
            I_redraw(liste,offset,nom);
        }
        if(c=='p') { //p on affiche une ligne
            isHelp = false;
            I_redraw(liste,offset,nom);
            I_printLigne(liste, offset);
        }
        if(c=='j'){ //j on saute vers une autre ligne
            I_jumpLigne(liste,offset);
            I_redraw(liste,offset,nom);
        }
        if(c=='h') { //h on affiche l'aide
            isHelp = !isHelp;
            HelpLigne = 0; 
            I_redraw(liste,offset,nom);
        }
        if(c=='m') { //On déplace deux lignes
            I_swap(liste);
            I_redraw(liste,offset,nom);
        }
        if(c==10){ //On apuie sur enter pour voir le message d'aide suivant
            HelpLigne++;
            if(HelpLigne==9){
                 isHelp = false;
                 I_redraw(liste,offset,nom);
            }
        }
        if(c==KEY_BACKSPACE){ //on apuie sur backspace pour retourner en arrière sur l'aide
            HelpLigne--;
            if(HelpLigne<0){
                isHelp = false;
                I_redraw(liste,offset,nom);
            }
        }
    }
    echo();
    endwin();
}

void I_printLigne(const struct headFile* liste, const offstruct* offset){
    int lig = getmaxy(stdscr);
    int lignE = I_askLine(liste, PRINT);
    if(lignE == -1) return;
    mvprintw(lig-1,0,A_readListe(liste,lignE)); //On affiche la ligne
}

void I_jumpLigne(const struct headFile* liste,offstruct* offset){
    int lignE = I_askLine(liste, JUMP);
    if(lignE == -1) return;
    offset->x = lignE;
}

void I_nouvelleLigne(struct headFile* liste){
    char* ligneN = I_askTxt(LINE_TYPE);
    A_append(liste); //traitement
    A_writeListe(liste,liste->nLignes,ligneN);
    free(ligneN);
}

void I_rename(char* nom){ //TODO : changer la manière dont la mémoire pour le nom est allouée pour pouvoir éviter de générer des array en boucle
    char* ret=malloc(sizeof(char) * FILENAMESIZE);
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
    positionEdit pos = AT_autopos(LINESIZE);
    int lignE = I_askLine(liste, EDIT); //numero de la ligne à éditer
    if(lignE == -1) return;
    AT_edit(A_readListe(liste,lignE),pos);
}

void I_delLigne(struct headFile* liste){
    int lignE = I_askLine(liste, DEL);
    if(lignE == -1) return;
    A_supression(liste,lignE);
}

void I_insert(struct headFile* liste){
    int lignE = I_askLine(liste, INSERT); //position de la ligne à insérer
    if(lignE == -1) return;
    A_insertion(liste,lignE);
    char* txt = I_askTxt(LINE_TYPE);
    A_writeListe(liste,lignE,txt);
    free(txt);
}

void I_swap(struct headFile* liste){
    int ligne1 = I_askLine(liste, SWAP_1);
    if(ligne1 == -1) return;
    int ligne2 = I_askLine(liste, SWAP_2);
    if(ligne2 == -1) return;
    char* str1 = malloc(sizeof(char) * LINESIZE);
    char* str2 = malloc(sizeof(char) * LINESIZE);
    strcpy(str1, A_readListe(liste, ligne1));
    strcpy(str2, A_readListe(liste, ligne2));
    A_writeListe(liste, ligne1, str2);
    A_writeListe(liste, ligne2, str1);
    free(str1);
    free(str2);
}

void I_cleanBas(int col,int lig){   
    for(int i=0;i<col;i++){ //On nétoie la zone d'input
        mvprintw(lig-1,i," ");
        mvprintw(lig-3,i," ");
    }
}

int I_askLine(const struct headFile* liste, const char* prompt){
    I_noChut();
    char* StrTmp = malloc(sizeof(char) * LINESIZE);
    memset(StrTmp, 0, LINESIZE);
    positionEdit pos = AT_autopos(LINESIZE);
    I_cleanBas(pos.taille +1,pos.y +1);
    int lignE = -1; //position de la ligne à insérer
    while(lignE < 1 || lignE > liste->nLignes){
        mvprintw(pos.y-2,0,prompt);
        move(pos.y,0); 
        refresh();
        getstr(StrTmp);
        if(strcmp(StrTmp,"") == 0) return -1;
        lignE = atoi(StrTmp);
        I_cleanBas(pos.taille +1,pos.y +1); 
    }
    free(StrTmp);
    I_chut();
    return lignE;
}

char* I_askTxt(const char* prompt){
    I_noChut();
    char* txt = malloc(sizeof(char) * LINESIZE);
    memset(txt,0, LINESIZE);
    positionEdit pos = AT_autopos(LINESIZE);
    I_cleanBas(pos.taille +1,pos.y +1); 
    mvprintw(pos.y-2,0,prompt);
    AT_edit(txt,pos);
    I_chut();
    return txt;
}

void I_chut(){
    noecho();
    curs_set(0);
}

void I_noChut(){
    echo();
    curs_set(1);
}

