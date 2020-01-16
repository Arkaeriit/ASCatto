#include "attoLib.h"
#include "attoType.h"
#include <ncurses.h>
#include <locale.h>
#include <stdbool.h>

#ifndef OFFSET_STRUCT
#define OFFSET_STRUCT

typedef struct Offsetxy { //structure pour stocker le décalge haut/bas et droite/gauche
    int x;
    int y;
} offstruct;

#endif

//fonctions liées à l'affichage
void I_init(); //gère ce dont on a besoin pour la suite. À lancer une fois
void I_displayListe(struct headFile* liste,int decade,offstruct* offset); //Cette fonction permet d'afficher le contenu de la listeà partir du offset-ième élément.
void I_displayInputBar(int max,int decade,const offstruct* offset,const char* nom); //Cette fonctio sert à dessiner la barre qui sert à entrer le texte à écrire
void I_redraw(struct headFile* liste,offstruct* offset,const char* nom); //Cette fonction sert à tout afficher comme il faut

//Fonctions liés aux inputs
void I_idle(struct headFile* liste,const char* nomInit); //fonction principale qui redirige l'utilisateur à chaque fois vers les autres fonctions
void I_nouvelleLigne(struct headFile* liste); //Cette fonction permet d'écrire dans une nouvelle ligne
void I_rename(char* nom); //permet de renomer le fichier édité
void I_editLigne(struct headFile* liste); //permet d'éditer une ligne
void I_delLigne(struct headFile* liste); //permet de supprimer une ligne
void I_printLigne(struct headFile* liste, offstruct* offset,char* nom);//Permet d'afficher une ligne en bas de l'écran
void I_jumpLigne(struct headFile* liste,offstruct* offset); //permet de se déplacer à une autre ligne, met à jour offset
void I_insert(struct headFile* liste); //permet d'insérer une ligne quelque part
void I_swap(struct headFile* liste); //permet de swaper 2 lignes du texte
void I_cleanBas(int col,int lig); //permet de nétoyer l'espace en bas de l'écrant pour ensuite entrer des info.
int I_askLine(struct headFile* liste, const char* prompt); //Permet de demander de nomer une des lignes du texte
char* I_askTxt(const char* prompt); //Permet d'entrer une ligne de texte
void I_chut(); //Permet de ne plus afficher le curseur
void I_noChut(); //L'inverse de I_chut
