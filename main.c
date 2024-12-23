#include "projet.h"

int main(void) {
    Dictionnaire dictionnaire;
    chargerDictionnaire(&dictionnaire);
    menu(&dictionnaire);
    free(dictionnaire.ligne);
    return 0;
}