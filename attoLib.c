#include "attoLib.h"

struct headFile* A_initialisation(void){
    struct headFile* ret = malloc(sizeof(struct headFile));
    ret->nLignes = 0;
    return ret;
}

struct ligneFile* A_recuperation(struct headFile* liste,int element){
    if(element > liste->nLignes || element < 1){
        printf("Erreur, mauvais indexage");
        exit(EXIT_FAILURE);
    }
    struct ligneFile* ret = liste->next;
    for(int i=1;i<element;i++){
        ret=ret->next;
    }
    return ret;
}

void A_supression(struct headFile* liste,int element){
    if(element > liste->nLignes || element < 1){
        printf("Erreur, mauvais indexage");
        exit(EXIT_FAILURE);
    }
    if(element == 1){
        struct ligneFile* tmp = liste->next;
        liste->next=tmp->next;
        free(tmp->ligne);
        free(tmp);
    }else{
        struct ligneFile* pnt = liste->next;
        for(int i=1;i<element-1;i++){
            pnt=pnt->next;
        }
        struct ligneFile* tmp = pnt->next;
        if(element!=liste->nLignes){
            pnt->next=(pnt->next)->next;
        }
        free(tmp->ligne);
        free(tmp);
    }
    liste->nLignes--;
}
    
void A_insertion(struct headFile* liste,int element){
    if(element > (liste->nLignes + 1) || element < 1){
        printf("Erreur, mauvais indexage");
        exit(EXIT_FAILURE);
    }
    if(liste->nLignes==0){
        liste->nLignes=1;
        liste->next=malloc(sizeof(struct ligneFile));
        liste->next->ligne = malloc(sizeof(char) * 4096);
    }else{
        if(element == 1){
            struct ligneFile* tmp = liste->next;
            liste->next = malloc(sizeof(struct ligneFile));
            (liste->next)->next = tmp;
            (liste->next)->ligne = malloc(sizeof(char) * 4096);
            liste->nLignes++;
        }else{
            struct ligneFile* pnt = liste->next;
            for(int i=1;i<element-1;i++){
                pnt=pnt->next;
            }
            struct ligneFile* tmp = pnt->next;
            pnt->next = malloc(sizeof(struct ligneFile));
            (pnt->next)->next = tmp;
            (pnt->next)->ligne = malloc(sizeof(char) * 4096);
            liste->nLignes++;
        }
    }
}

void A_append(struct headFile* liste){
    A_insertion(liste,liste->nLignes+1);
}

void A_writeListe(struct headFile* liste,int element,char* str){
    if(element > liste->nLignes || element < 1){
        printf("Erreur, mauvais indexage");
        exit(EXIT_FAILURE);
    }
    struct ligneFile* pnt = liste->next;
    for(int i=1;i<element;i++){
        pnt=pnt->next;
    }
    memcpy(pnt->ligne,str,strlen(str));
}
 
char* A_readListe(struct headFile* liste,int element){
    if(element > liste->nLignes || element < 1){
        printf("Erreur, mauvais indexage");
        exit(EXIT_FAILURE);
    }
    struct ligneFile* pnt = liste->next;
    for(int i=1;i<element;i++){
        pnt=pnt->next;
    }
    return pnt->ligne;
}   
struct headFile* A_readFile(char *filename){
        FILE* fptr;
        struct headFile* ret = A_initialisation();
        if( (fptr = fopen(filename,"r")) == NULL){ //on essaye de metre un pointeur vers le fichier dans fptr. Si ne marche pas on lira un NULL et donc on arretera tout. Sinon on va dans le else
            printf("Fichier non valable");
            exit(2);
        }else{
            char* str = malloc(sizeof(char) * 4096); //memoire tampon pour srocker une ligne
            while(fgets(str, 4096, fptr) != NULL){ //On essaye de lire la nouvelle ligne de fptr. Si ça ne marche pas on arrête nos bêtises mais si ça marche on la stoque dans str
                A_append(ret); //Si on a réussi à lire une ligne on l'ajoute à ret
                A_writeListe(ret,ret->nLignes,str);
            }
            fclose(fptr); //On ferme le fichier
        }
    return ret;
}

void A_writeFile(struct headFile* liste, char* filename){
    FILE* fptr;
    if( (fptr = fopen(filename,"w")) == NULL){ //on essaye de metre un pointeur vers le fichier dans fptr. Si ne marche pas on lira un NULL et donc on arretera tout. Sinon on va dans le else
        printf("Fichier non valable");
        exit(2);
    }else{
        struct ligneFile* pnt = liste->next;
        for(int i=1;i<liste->nLignes;i++){
            fputs( pnt->ligne,fptr ); //On écrit chaque ligne de la liste dans le fichier
            pnt=pnt->next;
        }
        fputs( pnt->ligne,fptr );
        fclose(fptr); //On ferme le fichier
    }
}


