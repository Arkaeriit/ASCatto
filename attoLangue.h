/* If fr is equal to 1 the program will be in French. Otherwise it will be in english*/
#define fr 0

#define NUMBER_OF_HELP 10

#if fr == 1
#define HOWTO "Apuillez sur h pour afficher l'aide"
#define INVALIDE "Nom invalide...  "
#define NAME "Nom du fichier : "
#define NAME_PAD 39
#define EDIT "Ligne à éditer :     "
#define DEL "Ligne à supprimer."
#define INSERT "Position de la nouvelle ligne."
#define LINE_TYPE "Tapez la nouvelle ligne."
#define JUMP "Position de la destination."
#define PRINT "Ligne à afficher."
#define SWAP_1 "Première ligne à échanger."
#define SWAP_2 "Avec quelle ligne l'échanger ?"
#define HELP_QUIT "Tapez Q pour quiter."
#define HELP_SAVE "Tapez s pour sauvegarder."
#define HELP_NEW_LINE "Tapez n pour ajouter une nouvelle ligne."
#define HELP_DEL_LINE "Tapez d puis le numéro de la ligne à supprimer pour supprimer une ligne."
#define HELP_OPEN_LINE "Tapez i puis la position où vous voulez insérer une ligne pour en isérer une."
#define HELP_ARROWS "Si le texte est trop grand pour être complètement affichable utilisez les flèches haut et bas pour naviguer dedant."
#define HELP_ARROWS_SIDE "Si les lignes sont trop longues utilisez les flèches droite et gauche pour faire défiler le texte."
#define HELP_INFO_HELP "Tapez Entrer pour avancer dans l'aide et backspace pour reculer. Tapez h pour quiter l'aide."
#define HELP_JUMP "Pour vous rendre à une ligne tapez j puis le numéro de la ligne."
#define HELP_PRINT "Pour afficher une ligne toute seule tapez p puis le numéro de la ligne."
#define HELP_SWAP "Pour echanger deux lignes taper s puis le numéro de chacune des lignes."

#else
#define HOWTO "Press h for help"
#define INVALIDE "Invalid name...  "
#define NAME "Filename : "
#define NAME_PAD 20
#define EDIT "Which line edit :     "
#define DEL "Which line delete?"
#define INSERT "Where to put the new ligne?"
#define LINE_TYPE "Type the new line."
#define JUMP "Where to jump?"
#define PRINT "Which line print?"
#define SWAP_1 "First line to swap."
#define SWAP_2 "Second line to swap."
#define HELP_QUIT "Press Q to quit."
#define HELP_SAVE "Press s to save."
#define HELP_NEW_LINE "Press n to write a new line."
#define HELP_DEL_LINE "Press d then the number of a line to delete it."
#define HELP_OPEN_LINE "To insert a line press i then the position where you want to insert it."
#define HELP_ARROWS "If the file is to big too be displayed use the up and down arrows key to navigate."
#define HELP_ARROWS_SIDE "If the lines are too long use the left and right arrows to navigate."
#define HELP_INFO_HELP "Press Return to see the next help message, press backspace to go back. Press h to toggle help."
#define HELP_JUMP "To go to any line press j then the nuber of the line."
#define HELP_PRINT "To print any line on the bottom of the screen press p then the number of the line."
#define HELP_SWAP "To swap two lines press s then enter the number of the two lines."

#endif

/* NAME_PAD est la position à laquelle le nom du fichier est écrit
 * Comme le message NAME ne fait pas le même taille en fonction des langues il n'est pas toujour identique.*/

