

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listemots.h"


// Fonction privée pour créer un nouveau mot
struct sMot *motCreer(char *mot, int occ) 
{
  // Allocation de la mémoire pour la structure du mot
  struct sMot *nouveauMot = malloc(sizeof(struct sMot));

  // Vérification de l'allocation réussie
  if (nouveauMot == NULL) 
  {
    return NULL; // Erreur d'allocation mémoire
  }

  // Allocation de la mémoire pour le champ 'mot' (taille + 1 pour le terminateur '\0')
  nouveauMot->mot = malloc(strlen(mot) + 1);

  // Vérification de l'allocation réussie
  if (nouveauMot->mot == NULL) 
  {
    free(nouveauMot); // Libérer la mémoire allouée pour la structure
    return NULL; // Erreur d'allocation mémoire
  }

  // Copie du mot dans le champ 'mot'
  strcpy(nouveauMot->mot, mot);

  // Initialisation des autres champs de la structure
  nouveauMot->taille = strlen(mot);
  nouveauMot->occurrences = occ;
  nouveauMot->suivant = NULL;

  // Renvoyer le pointeur vers le mot créé
  return nouveauMot;
}


// Fonction privée pour libérer la mémoire occupée par un mot
void motLiberer(struct sMot *mot) 
{
    if (mot != NULL) {
        free(mot->mot); // Libération de la mémoire allouée pour la chaîne de caractères du mot
        free(mot);      // Libération de la mémoire allouée pour la structure du mot
    }
}


// Crée une liste vide de mots
tListeMots creerListeMots(void) 
{
     // Allocation de la mémoire pour la structure tListeMots
  tListeMots liste = (tListeMots)malloc(sizeof(struct sListeMots));

  // Vérification de l'allocation réussie
  if (liste == NULL) {
    return NULL; // Allocation échouée, retourner "NULLE"
  }

  // Initialisation des champs de la structure
  liste->debut = NULL;
  liste->fin = NULL;
  liste->nbMots = 0;

  // Retourner la liste créée
  return liste;
}

// Libère l'espace mémoire occupé par la liste
void detruireListeMots(tListeMots liste) {
    if (liste != NULL) {
        struct sMot *courant = liste->debut;
        while (courant != NULL) {
            struct sMot *temp = courant;
            courant = courant->suivant;
            motLiberer(temp);
        }
        free(liste);
    }
}

// Renvoie le nombre de mots dans la liste
int nombreDeMots(tListeMots liste) 
{
    if (liste != NULL) 
    {
        return liste->nbMots;
    }
    return 0;
}

// Ajoute un mot avec un nombre d'occurrences spécifié à la liste
void ajouterMotAvecOcc(tListeMots liste, char *mot, int nbOcc) 
{
    if (liste != NULL) 
    {
        struct sMot *nouveauMot = motCreer(mot, nbOcc);
        if (nouveauMot != NULL) 
        {
            if (liste->debut == NULL) 
            {
                liste->debut = nouveauMot;
                liste->fin = nouveauMot;
            } 
            else 
            {
                liste->fin->suivant = nouveauMot;
                //liste->fin = nouveauMot;
            }
            liste->nbMots++;
        }
    }
}

// Ajoute un mot à la liste avec une occurrence de 1
void ajouterMot(tListeMots liste, char *mot) 
{
    ajouterMotAvecOcc(liste, mot, 1);
}

// Écrit tous les mots de la liste dans le fichier
void ecrireListeMots(tListeMots liste, FILE *fich) 
{
    if (liste != NULL) 
    {
         if (fich != NULL) 
        {
            struct sMot *courant = liste->debut;
            while (courant != NULL) 
            {
                fprintf(fich, "%s ", courant->mot);
                courant = courant->suivant;
            }
            fprintf(fich, "\n");
        }
    }
}