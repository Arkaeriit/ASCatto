#include "attoInterface.h"

void I_init(){
    initscr();
    noecho();
    if(has_colors()){
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLACK);
        init_pair(2,COLOR_BLACK,COLOR_WHITE);
    }
    curs_set(0);
}

void I_displayListe(struct headFile* liste,int decades,int offset){
   for(int i=offset;i<=liste->nLignes;i++){
        mvprintw(i-offset,1,"%i",i); //Numéro de la ligne
        mvprintw(i-offset,2+decades,"|"); //séparation
        mvprintw(i-offset,3+decades,"%s",A_readListe(liste,i)); //ligne en elle même
    }
}

void I_displayInputBar(int max,int decades,int offset){
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    if(has_colors()){
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
    }else{
        for(int i=0;i<col;i++){
            mvprintw(lig-3,i," ");
            mvprintw(lig-4,i,"-");
            mvprintw(lig-1,i," ");
            mvprintw(lig-2,i,"-");
        }
    }
    char* howto = "TODO";
    mvprintw(lig-3,0,howto);
    mvprintw(lig-3,col- 2 * (2+decades)," %i/%i  ",offset,max);
    move(lig-1,0);
}

void I_redraw(struct headFile* liste,int offset){
     int decades=1; //Nombres de caractères à prévoir pour écrire le numéro de la ligne
    if(liste->nLignes > 9) decades++;
    if(liste->nLignes > 99) decades++;
    if(liste->nLignes > 999) decades++;
    if(liste->nLignes > 9999) decades++;
    clear();
    I_displayListe(liste,decades,offset);
    I_displayInputBar(liste->nLignes,decades,offset);
    refresh();
}

void I_idle(struct headFile* liste){
    int offset = 1;
    I_redraw(liste,offset);
    int stop = 0;
    while(!stop){
        char c = getch();
        mvprintw(1,1,"%i",c);
        if(c==65 && offset > 1){
            offset--;
            I_redraw(liste,offset);
        }
        if(c==66 && offset < liste->nLignes){
            offset++;
            I_redraw(liste,offset);
        }
        if(c==81){
            stop=1;
        }
    }
    endwin();
}
