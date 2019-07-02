#include <string.h>
#include <ncurses.h>
#include <stdlib.h>

//string est la chaine à modifier
//strlenMax est la taille maximale que l'on peut lui donner
//x et y init sont les coordonnées du lieu où on édite
//yMax est la longeur de la zone d'édition
void editString(char* string,int strlenMax, int xInit, int yInit, int yMax);//Permet d'éditer proprement string.
void showString(char* string,int positionCurseur,int xInit,int yInit,int limiteString);//Affiche string aux positions voulues en tenant compte que l'onn a un curseur placé à positionCurseur
void delChar(char* string,int position); //Permet de suprimer le positon°ème caractère de string.
void addChar(char* string,int position,char element,int strlenMax); //permet d'nsérer un charactère dans la chaine.
void cleanInput(int xInit,int yInit,int yMax); //Permet de n"toyer la zone où l'on édite le texte.

