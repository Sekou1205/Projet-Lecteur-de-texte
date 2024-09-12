#include <stdio.h>
#include <stdlib.h>
#include "listemots.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Ouverture du fichier en lecture
    FILE *fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Initialisation des variables pour les statistiques
    int nbPhrases = 0;
    int nbMots = 0;
    int nbCaracteres = 0;
    int longueurTotalePhrases = 0;
    int longueurPhraseMax = 0;
    char caractere;
    int estDansMot = 0;
    int longueurPhraseCourante = 0;

    // Création de la liste de mots
    tListeMots listeMots = creerListeMots();

    // Lecture et analyse du fichier caractère par caractère
    while ((caractere = fgetc(fichier)) != EOF) {
        nbCaracteres++;

        // Vérification si le caractère est dans un mot
        if (caractereDunMot(caractere)) {
            if (!estDansMot) {
                estDansMot = 1;
                nbMots++;
            }
        } else {
            if (estDansMot) {
                estDansMot = 0;
            }

            // Vérification si le caractère marque la fin d'une phrase
            if (caractereFinDePhrase(caractere)) {
                nbPhrases++;
                longueurTotalePhrases += longueurPhraseCourante;
                if (longueurPhraseCourante > longueurPhraseMax) {
                    longueurPhraseMax = longueurPhraseCourante;
                }
                longueurPhraseCourante = 0;
            }
        }

        // Incrémentation de la longueur de la phrase courante
        if (!caractereFinDePhrase(caractere)) {
            longueurPhraseCourante++;
        }
    }

    // Fermeture du fichier
    fclose(fichier);

    // Calcul de la longueur moyenne d'un mot et d'une phrase
    double longueurMoyenneMot = (double)nbCaracteres / nbMots;
    double longueurMoyennePhrase = (double)longueurTotalePhrases / nbPhrases;

    // Écriture des statistiques dans le fichier statistiques.txt
    FILE *fichierStatistiques = fopen("statistiques.txt", "w");
    if (fichierStatistiques == NULL) {
        fprintf(stderr, "Erreur: Impossible de créer le fichier statistiques.txt\n");
        detruireListeMots(listeMots);
        return EXIT_FAILURE;
    }

    fprintf(fichierStatistiques, "Texte: %s\n", argv[1]);
    fprintf(fichierStatistiques, "Nombre de phrases: %d\n", nbPhrases);
    fprintf(fichierStatistiques, "Nombre de mots: %d\n", nbMots);
    fprintf(fichierStatistiques, "Nombre de caracteres: %d\n", nbCaracteres);
    fprintf(fichierStatistiques, "Longueur moyenne d'un mot: %.2f\n", longueurMoyenneMot);
    fprintf(fichierStatistiques, "Longueur moyenne d'une phrase: %.2f\n", longueurMoyennePhrase);
    fprintf(fichierStatistiques, "Phrase la plus longue (%d mots): ", longueurPhraseMax);
    // Ici, vous pouvez ajouter la phrase la plus longue

    // Fermeture du fichier statistiques.txt
    fclose(fichierStatistiques);

    // Libération de la mémoire allouée pour la liste de mots
    detruireListeMots(listeMots);

    return EXIT_SUCCESS;
}
