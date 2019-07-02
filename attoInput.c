#include "attoInput.h"

//string est la chaine à modifier
//strlenMax est la taille maximale que l'on peut lui donner
//x et y init sont les coordonnées du lieu où on édite
//yMax est la longeur de la zone d'édition
void editString(char* string,int strlenMax, int xInit, int yInit, int yMax){
    echo();
    curs_set(1);
    int limiteString = yMax - 3; //On affiche des charactères jusqu'à 3 charactères avant la limite
    int positionCurseur = strlen(string);
    int stop=0;
    while(!stop){
        cleanInput(xInit,yInit,yMax);
        showString(string,positionCurseur,xInit,yInit,limiteString);
        char s = getchar();
        mvprintw(2,2,"     ");;mvprintw(2,2,"%u",s); //test
        switch(s) {
            case 13 : //Enter, on arrète d'éditer;
                stop=1;
                break;
            case 127 : //Backspace, on supprime le caractère avant.
                delChar(string,positionCurseur-1);
                positionCurseur--;
                break;
            case 27 ://suppr, on suprime le caractère actuel.
                delChar(string,positionCurseur);
                break;
            case 67 : if(positionCurseur<strlen(string)){ //flèche droite, on déplace le curseur
                    positionCurseur++;
                }
                break;
            case 68 : if(positionCurseur>0){ //flèche gauche
                    positionCurseur--;
                }
                break;
            default : //Sinon on insère le charactère que l'on vient de taper
                if((s>=97 && s<=122) || (s>=65 && s<=90) || (s>=48 && s<=57) || (s>=58 && s<=63) || (s>=33 && s<=55) /*??*/ || (s>=0 && s<=0) || (s>=0 && s<=0)) { //On ne veut que des charactères affichables.
                    addChar(string,positionCurseur,s,strlenMax);
                    positionCurseur++;
                }
        }
    }
}

void showString(char* string,int positionCurseur, int xInit,int yInit, int limiteString){
    if(positionCurseur < limiteString){
        mvprintw(xInit,yInit,"%s",string);
    }else{
        mvprintw(xInit,yInit,"%s",(char*) string + (positionCurseur - limiteString));
    }
    move(xInit,yInit+positionCurseur);
    refresh();
}

void delChar(char* string,int position){
    if(position == 0) return; //On ne peut rien faire.
    char* save = malloc(sizeof(char) * (strlen(string) - position)); //On savegarde la chaine de charactère à partir de la coupure.
    memcpy(save,(char*) string+position+1 , strlen(string) - position);
    memset( (char*) string+position,0,strlen(string) - position + 1); //On suprime la fin de la chaine de caractère pour que les deux morceaux que l'on a ne comprtent pas l'élément situé à position.
    strcat(string,save);
    free(save);
}

void addChar(char* string,int position,char element,int strlenMax){
    if(position == strlenMax) return; //On a plus le droit de rajouter de charactères
    char* save = malloc(sizeof(char) * strlenMax); //On y met la fin de la chaine.
    memset( (char*) string+position,0,strlenMax);//On vide mais on va tout recoller après
    char* elem = &element;
    strcat(string,elem);
    strcat(string,save);
    free(save);
}

void cleanInput(int xInit,int yInit,int yMax){
    for(int i=0;i<yMax;i++){
        mvprintw(xInit,yInit+i," ");
    }
}

