/* If fr is equal to 1 the program will be in French. Otherwise it will be in english*/
#define fr 0

#if fr == 1
#define HOWTO "Apuillez sur h pour afficher l'aide"
#define INVALIDE "Nom invalide...  "
#define NAME "Nom du fichier : "
#define NAME_PAD 39
#define EDIT "Ligne à éditer :     "
#define DEL "Ligne à supprimer"
#define INSERT "position de la nouvelle ligne."
#define HELP_QUIT "Tapez Q pour quiter."
#define HELP_SAVE "Taper s pour sauvegarder."
#define HELP_NEW_LINE "Tapez n pour ajouter une nouvelle ligne."
#define HELP_DEL_LINE "Tapez d puis le numéro de la ligne à supprimer pour supprimer une ligne."
#define HELP_OPEN_LINE "Tapez i puis la position où vous voulez insérer une ligne pour en isérer une."
#define HELP_ARROWS "Si le texte est trop grand pour être complètement affichable utilisez les flèches haut et bas pour naviguer dedant."
#define HELP_INFO_HELP "Tapez Entrer pour avancer dans l'aide et echap pour reculer."

#else
#define HOWTO "Press h for help"
#define INVALIDE "Invalid name...  "
#define NAME "Filename : "
#define NAME_PAD 20
#define EDIT "Which line edit :     "
#define DEL "Which line delete"
#define INSERT "Where to put the new ligne"
#define HELP_QUIT "Press Q to quit."
#define HELP_SAVE "Press s to save."
#define HELP_NEW_LINE "Press n to write a new line."
#define HELP_DEL_LINE "Press d the the number a a line to delete it."
#define HELP_OPEN_LINE "To insert a line press i the then position where you want to insert it."
#define HELP_ARROWS "If the file is to big too be displayed use the arrows key to navigate"
#define HELP_INFO_HELP "Press Return to see the next help message, press echap to go back."

#endif

/* NAME_PAD est la position à laquelle le nom du fichier est écrit
 * Comme le messa ge NAME ne fait pas le même taille en fonction des langues il n'est pas toujour identique.*/

