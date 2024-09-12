#include <stdio.h>
#include "listemots.h"

int main() 
{
    // Création d'une liste de mots
    tListeMots liste = creerListeMots();

    // Ajout de quelques mots à la liste
    ajouterMot(liste, "Hello");
    ajouterMot(liste, "World");
    ajouterMot(liste, "Bonjour");

    // Affichage du contenu de la liste
    printf("Contenu de la liste de mots :\n");
    ecrireListeMots(liste, stdout);

    // Destruction de la liste pour libérer la mémoire
    detruireListeMots(liste);

    FILE *fich = fopen("liste_mots.txt", "w");
    if (fich != NULL) {
      ecrireListeMots(liste, fich);
      fclose(fich);
    } else {
      printf("Erreur d'ouverture du fichier.\n");
    }
    return 0;
}
