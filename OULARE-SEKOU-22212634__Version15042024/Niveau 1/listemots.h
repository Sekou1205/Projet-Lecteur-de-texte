
#ifndef LISTEMOTS_H
#define LISTEMOTS_H

// Structure représentant un mot
struct sMot {
    char *mot;           // le mot (chaîne de caractères allouée dynamiquement)
    int taille;          // nombre de caractères du mot
    int occurrences;     // nombre d'occurrences du mot dans un texte
    struct sMot *suivant; // mot suivant dans le contexte d'une liste chaînée
};

// Structure représentant une liste de mots
struct sListeMots {
    struct sMot *debut; // pointeur vers le premier mot de la liste
    struct sMot *fin;   // pointeur vers le dernier mot de la liste
    int nbMots;         // nombre de mots de la liste
};

// Type permettant de manipuler une liste de mots
typedef struct sListeMots *tListeMots;

// Fonction privée pour créer un nouveau mot
struct sMot *motCreer(char *mot, int occ);

// Fonction privée pour libérer la mémoire occupée par un mot
void motLiberer(struct sMot *mot);



// Type permettant de manipuler une liste de mots
typedef struct sListeMots * tListeMots ;

// Fonctions publiques
tListeMots creerListeMots(void);
void detruireListeMots(tListeMots liste);
int nombreDeMots(tListeMots liste);
void ajouterMotAvecOcc(tListeMots liste, char *mot, int nbOcc);
void ajouterMot(tListeMots liste, char *mot);
void ecrireListeMots(tListeMots liste, FILE *fich);


#endif /* LISTEMOTS_H */


