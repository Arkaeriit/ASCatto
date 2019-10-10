//Ces fonctions servent à lédition de texte

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct positionEdit{
    int x; 
    int y;//Coordonées xy de l'endroit où on édite.
    int taille;
    int tailleMax;
} positionEdit;

void AT_edit(char* texte,positionEdit position); //On modifie la chaine texte
void AT_showEdit(char* texte,positionEdit position,int positionCurseur); //Permet d'afficher le texte que l'on édite
positionEdit AT_autopos(int tailleMax); //permet d'avoir une position en fin de page automatiquement
void AT_delChar(char* texte,int positionCurseur); //Supprime le charactère à la position voulue
int AT_insertChar(char* texte,char elem,positionEdit position,int positionCurseur); //Insère le char elem, on a besoin de posision pour voir si il nous reste de la place. renvoie 1 si on a réussi à le placer, sinon renvoie 0;
