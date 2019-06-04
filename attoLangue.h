/* If fr is equal to 1 the program will be in French. Otherwise it will be in english*/
#define fr 1

#if fr == 1
#define HOWTO "Apuillez sur h pour afficher l'aide"
#define INVALIDE "Nom invalide...  "
#define NAME "Nom du fichier : "
#define NAME_PAD 39
#define EDIT "Ligne à éditer :     "

#else
#define HOWTO "Press h for help"
#define INVALIDE "Invalid name...  "
#define NAME "Filename : "
#define NAME_PAD 20
#define EDIT "Which line edit :     "

#endif

/* NAME_PAD est la position à laquelle le nom du fichier est écrit*/

