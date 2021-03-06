#include "attoLib.h"

//vertion modifiée pour ASCatto

struct headFile* A_initialisation(void){
    struct headFile* ret = malloc(sizeof(struct headFile));
    ret->nLignes = 0;
    return ret;
}

struct ligneFile* A_recuperation(const struct headFile* liste,int element){
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
        if(liste->nLignes == 1){
            free(liste->next);
        }else{
            struct ligneFile* tmp = liste->next;
            liste->next=tmp->next;
            free(tmp->ligne);
            free(tmp);
        }
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
        liste->next->ligne = malloc(sizeof(char) * LINESIZE);
    }else{
        if(element == 1){
            struct ligneFile* tmp = liste->next;
            liste->next = malloc(sizeof(struct ligneFile));
            (liste->next)->next = tmp;
            (liste->next)->ligne = malloc(sizeof(char) * LINESIZE);
            liste->nLignes++;
        }else{
            struct ligneFile* pnt = liste->next;
            for(int i=1;i<element-1;i++){
                pnt=pnt->next;
            }
            struct ligneFile* tmp = pnt->next;
            pnt->next = malloc(sizeof(struct ligneFile));
            (pnt->next)->next = tmp;
            (pnt->next)->ligne = malloc(sizeof(char) * LINESIZE);
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
    for(int i=1;i<element;i++){ //On se place sur le bon élément
        pnt=pnt->next;
    }
    memset(pnt->ligne, 0 ,LINESIZE);
    memcpy(pnt->ligne,str,strlen(str));
}
 
char* A_readListe(const struct headFile* liste,int element){
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
struct headFile* A_readFile(const char *filename){
        FILE* fptr;
        struct headFile* ret = A_initialisation();
        ret->next = malloc(sizeof(struct ligneFile));
        struct ligneFile* pnt = ret->next;
        if( (fptr = fopen(filename,"r")) == NULL){ //on essaye de metre un pointeur vers le fichier dans fptr. Si ne marche pas on lira un NULL et donc on créer le fichier de toutes pieces. NB: ce comportement n'est pas celui avec lequel j'ai pensé la libraiie et est uniquement msi en place pour pouvoir faire marcher le programme. Sinon on va dans le else
            A_append(ret); //La fin justifie les moyens.
        }else{
            char* str = malloc(sizeof(char) * LINESIZE); //memoire tampon pour srocker une ligne
            while(fgets(str, LINESIZE, fptr) != NULL){ //On essaye de lire la nouvelle ligne de fptr. Si ça ne marche pas on arrête nos bêtises mais si ça marche on la stoque dans str
                ret->nLignes++; //Si on a réussi à lire une ligne on l'ajoute à ret
                pnt->ligne = malloc(sizeof(char) * LINESIZE);
                memcpy(pnt->ligne,str,strlen(str) -1); //le -1 sert à enlever le \n
                pnt->next = malloc(sizeof(struct ligneFile));
                pnt = pnt->next;
            }
            fclose(fptr); //On ferme le fichier
        }
    return ret;
}

int A_writeFile(const struct headFile* liste, char* filename){
    FILE* fptr;
    char* StrTmp = malloc(sizeof(char) * (LINESIZE + 1)); //On ajoute un \n à la fin des lignes donc on passe par cette chaine de caractères tampon pour ne pas salir la liste
    if( (fptr = fopen(filename,"w")) == NULL){ //on essaye de metre un pointeur vers le fichier dans fptr. Si ne marche pas on renvoie 1 pour idiquer que ça ne marche pas. Sinon on va dans le else
        return 1;
    }else{
        struct ligneFile* pnt = liste->next;
        for(int i=0;i<liste->nLignes;i++){
            memcpy(StrTmp,pnt->ligne,strlen(pnt->ligne)); //on stocke la ligne utile dans le tampon
            strcat(StrTmp,"\n"); //pour réenregister on a besoin du retour chariot
            fputs( StrTmp,fptr ); //On écrit chaque ligne de la liste dans le fichier
            pnt=pnt->next;
            memset(StrTmp, 0, LINESIZE+1);
        }
        fclose(fptr); //On ferme le fichier
        free(StrTmp); //On a plus besoin du tampon
    }
    return 0;
}


