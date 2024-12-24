#ifndef PROJET_H
#define PROJET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LONGUEUR_MOTS_MAX 50
#define LONGUEUR_DEFINITION_MAX 100
#define TAILLE_PHYSIQUE 5

typedef struct {
    char mot[LONGUEUR_MOTS_MAX];
    char definition[LONGUEUR_DEFINITION_MAX];
    char traduction[LONGUEUR_MOTS_MAX];
} Ligne;

typedef struct {
    Ligne* ligne;
    int taille;
    int capacite;
} Dictionnaire;

//Fonctionnalités principales
void chargerDictionnaire();
void afficherDictionnaire();
void ajouterMot();
void supprimerMot();
void afficherDefinition();
void afficherTraduction();
void sauvegardeDictionnaire();
void redimensionnerDictionnaire();

//Fonctions utilitaires : Evite répétitions
void lireChaineDeCaracteres();
int rechercherMot();

//Fonctionnalité Supplémentaire : Gestion des synonymes
void ajoutSynonyme();
void supprimerSynonyme();
void modifierSynonyme();

//Fonctionnalité Supplémentaire : Jeu d'Apprentisage Linguistique
void jeuApprentissage();

//Fonctionnalité Supplémentaire : Prévention de doublons (et autres)
int preventionDepassementTailleMot();
int preventionDictionnaireVide();
int preventionCaracteresInterdits();
int preventionDoublon();
int preventionDoublonSynonyme();

//Menu et les choix (= procédures appellées par le menu)
void choix2();
void choix3();
void choix4();
void choix5();
void menu();

#endif
