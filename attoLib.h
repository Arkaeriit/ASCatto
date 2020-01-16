/*-----------------------------------------------------------------------------------------------------------------------\
|Cette librairie sert à gérer des listes chainées de charactères et s'en sert pour simuler des fichiers.                 |
|Il est important de noter que les chaines de caractères de la liste doivent se terminer par \n pour simuler des fichiers|
\-----------------------------------------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCTURES_ATTO
#define STRUCTURES_ATTO

//Les deux structures suivantes servent à former une liste liée qui contient chacune des lignes du fichier à éditer

struct ligneFile {
    char* ligne;
    struct ligneFile* next;
};

struct headFile {
    int nLignes;
    struct ligneFile* next;
};

#endif

#define LINESIZE 4096

//Fonctions de gestions des listes liés
struct headFile* A_initialisation(void); 
struct ligneFile* A_recuperation(struct headFile* liste,int element); //récupère le pointeur vers l'élément d'indice voulu
void A_supression(struct headFile* liste,int element); //suprime l'élément d'undice voulu
void A_insertion(struct headFile* liste,int element); //insère un élément à la position voulue
void A_append(struct headFile* liste); //ajoute un élément à la fin de la liste
void A_writeListe(struct headFile* liste,int element,char* str); //copie str dans l'élément voulu de liste
char* A_readListe(struct headFile* liste,int element); //renvoie la chaine de charactère stockée à la place voulue de liste

//Fonctions de gestion des fichiers
struct headFile* A_readFile(char* fichier); //met chaque ligne de fichier dans un élément d'une liste
int A_writeFile(struct headFile* liste,char* fichier); //écrit le contenu de la liste dans fichier

