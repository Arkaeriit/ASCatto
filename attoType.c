#include "attoType.h"

void AT_edit(char* texteOrigine,positionEdit position){
    curs_set(1);
    char* texte = malloc(sizeof(char) * position.tailleMax); //On travaille sur une copie de l'origine
    memset(texte,0,position.tailleMax);
    strcpy(texte,texteOrigine);
    int positionCurseur = strlen(texte);
    int c = 0;
    while(c != 10){
        AT_showEdit(texte,position,positionCurseur); 
        c = getch();
        switch(c){
            case KEY_LEFT :
                if(positionCurseur > 0)
                    positionCurseur--;
                break;
            case KEY_RIGHT :
                if(positionCurseur < strlen(texte))
                    positionCurseur++;
                break;
            case KEY_BACKSPACE :
                AT_delChar(texte,positionCurseur - 1);
                if(positionCurseur > 0)
                    positionCurseur--;
                break;
            case KEY_DC :
                AT_delChar(texte,positionCurseur);
                break;
            case 9: //tab
                for(int i = 0;i<4;i++){
                    if(AT_insertChar(texte,' ',position,positionCurseur))
                        positionCurseur++;
                }
                break;
            case 10 : //On apuie sur enter donc on enregistre
                strcpy(texteOrigine,texte);
                break;
            case 360 : //On abandonne l'édition avec la touche "fin"
                c = 10;
            default :
                if(AT_insertChar(texte,(char) c,position,positionCurseur))
                    positionCurseur++;
        }
    }

    free(texte);
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
        debut = 0;
    }
    mvprintw(position.y,position.x,"%s",tmp);
    move(position.y,position.x + positionCurseur - debut);
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

void AT_delChar(char* texte,int positionCurseur){
    if(positionCurseur >= 0 && positionCurseur < strlen(texte)){ //On vérifie que la commande est valide
        for(int i = positionCurseur; i < strlen(texte); i++){
            char* pos = (texte + i);
            char new = *(texte+i+1);
            *(pos) = new;
        }
    }
}

int AT_insertChar(char* texte,char elem,positionEdit position,int positionCurseur){
    if(strlen(texte) < position.tailleMax && elem >= 32 && elem <= 126){ // On regarde si il reste de la place et si le cccharacère que l'on veut est effectivement un caractère
        for(int i = strlen(texte); i > positionCurseur;i--)
            *(texte + i) = *(texte + i - 1);
        *(texte+positionCurseur) = elem;
        return 1;
    }else{
        return 0;
    }
}

