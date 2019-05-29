#include "attoLib.h"
#include <ncurses.h>

//fonctions liées à l'affichage
void I_init(); //gère ce dont on a besoin pour la suite. À lancer une fois
void I_displayListe(struct headFile* liste,int decade,int offset); //Cette fonction permet d'afficher le contenu de la listeà partir du offset-ième élément.
void I_displayInputBar(int max,int decade,int offset); //Cette fonctio sert à dessiner la barre qui sert à entrer le texte à écrire
void I_redraw(struct headFile* liste,int offset); //Cette fonction sert à tout afficher comme il faut

//Fonctions liés aux inputs
void I_idle(struct headFile* liste,char* nom); //fonction principale qui redirige l'utilisateur à chaque fois vers les autres fonctions
void I_nouvelleLigne(struct headFile* liste); //Cette fonction permet d'écrire dans une nouvelle ligne
char* I_rename(); //permet de renomer le fichier édité
