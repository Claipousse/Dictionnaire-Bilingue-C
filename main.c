#include "projet.h"

int main(void) {
    Dictionnaire dictionnaire; //On crée une variable dictionnaire (de type Dictionnaire)
    chargerDictionnaire(&dictionnaire);//On charge le contenu de dict.txt dans la variable dictionnaire
    menu(&dictionnaire); //Le menu sert de passerelle entre l'utilisateur et tous les sous-programmes dans projet.c
    free(dictionnaire.ligne); //Lorsque que l'on a finit, on libere l'espace alloué pour le tableau dynamique
    return 0;
}