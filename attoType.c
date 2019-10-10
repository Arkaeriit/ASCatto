#include "attoType.h"

void AT_edit(char* texte,positionEdit position){
    curs_set(1);
    echo();
    int positionCurseur = strlen(texte);
    AT_showEdit(texte,position,positionCurseur); 
    getch();



    noecho();
    curs_set(0);
}

void AT_showEdit(char* texte,positionEdit position,int positionCurseur){
    for(int i=0;i<position.taille;i++){ //netoyage
        mvprintw(position.y,position.x+i," ");
    }
    int debut = positionCurseur - position.taille + 3; //À partir d'où on affiche la ligne
    char* tmp = malloc(sizeof(char) * position.tailleMax); //O créé une sous-chaine qui contint ce que l'on peut afficher.
    if(debut > 0){ //On doit déplacer le début
        strcpy(tmp,texte + positionCurseur - position.taille + 3);
        *(tmp + position.taille) = 0;
    }else{ //On peut afficher toute la chaine
        strcpy(tmp,texte);
        *(tmp + position.taille) = 0;
    }
    mvprintw(3,3,"%s",tmp);
    mvprintw(position.y,position.x,"%s",tmp);
    refresh();
    free(tmp);
}

positionEdit AT_autopos(int tailleMax){
    int col;
    int lig;
    getmaxyx(stdscr,lig,col);
    positionEdit ret;
    ret.y = lig - 1;
    ret.x = 0;
    ret.taille = col - 1;
    ret.tailleMax = tailleMax;
    return ret;
}
