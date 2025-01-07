#ifndef PROJET_H
#define PROJET_H

//Bibliotheques utilisés pour le projet :
#include <stdio.h> // Pour les entrées et sorties (scanf, printf, ...) et pour les opérations sur fichiers (fgets, fprintf,...)
#include <stdlib.h> // Pour la gestion de la mémoire (malloc, calloc, realloc,...)
#include <string.h> // Pour gérer les chaines de caractères
#include <time.h> //Pour l'aléatoire

#define LONGUEUR_MOTS_MAX 50 //La longueur max d'un mot + de/des traduction(s) est de 50
#define LONGUEUR_DEFINITION_MAX 100 //La longueur max d'une definition est de 100
#define TAILLE_PHYSIQUE 2 //La taille physique initiale est de 2 (x2 quand la limite est atteinte)

typedef struct {
    char mot[LONGUEUR_MOTS_MAX];
    char definition[LONGUEUR_DEFINITION_MAX];
    char traduction[LONGUEUR_MOTS_MAX];
} Ligne; //On definit une ligne comme une entité composé d'un mot, une definition et une traduction via une structure

typedef struct {
    Ligne* ligne;
    int taille;
    int capacite;
} Dictionnaire; //On definit un dictionnaire une entité composé de lignes, d'une taille et d'une capacité

//Fonctionnalités principales
void chargerDictionnaire(Dictionnaire* dictionnaire);
void afficherDictionnaire(Dictionnaire* dictionnaire);
void ajouterMot(Dictionnaire* dictionnaire, char* mot, char* definition, char* traduction, int afficherMessage);
void supprimerMot(Dictionnaire* dictionnaire, char* mot);
void afficherDefinition(Dictionnaire* dictionnaire, char* mot);
void afficherTraduction(Dictionnaire* dictionnaire, char* mot);
void sauvegardeDictionnaire(Dictionnaire* dictionnaire);
void redimensionnerDictionnaire(Dictionnaire* dictionnaire);

//Fonctions utilitaires : Evite répétitions
void lireChaineDeCaracteres(char* chaine, int taille_max);
int rechercherMot(Dictionnaire* dictionnaire, char* mot);

//Fonctionnalité Supplémentaire : Gestion des synonymes
void ajoutSynonyme(Dictionnaire* dictionnaire, char* mot);
void supprimerSynonyme(Dictionnaire* dictionnaire, char* mot);
void modifierSynonyme(Dictionnaire* dictionnaire, char* mot);

//Fonctionnalité Supplémentaire : Jeu d'Apprentisage Linguistique
void jeuApprentissage(Dictionnaire* dictionnaire);

//Fonctionnalité Supplémentaire : Prévention de doublons (et autres)
int preventionDictionnaireVide(Dictionnaire* dictionnaire);
int preventionDepassementTailleMot(char* chaine, int taille_max);
int preventionCaracteresInterdits(char* chaine);
int preventionDoublon(Dictionnaire* dictionnaire, char* mot);
int preventionDoublonSynonyme(char* liste_synonymes, char* synonyme);

//Menu et les choix (= procédures appelées par le menu)
void choix2(Dictionnaire* dictionnaire, char* mot, char* definition, char* traduction);
void choix3(Dictionnaire* dictionnaire, char* mot);
void choix4(Dictionnaire* dictionnaire, char* mot);
void choix5(Dictionnaire* dictionnaire, char* mot);
void choix6(Dictionnaire* dictionnaire, char* mot);
void menu(Dictionnaire* dictionnaire); //Passerelle entre l'utilisateur et les sous-programmes

#endif
