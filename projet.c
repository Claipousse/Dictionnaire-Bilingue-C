#include "projet.h"

void chargerDictionnaire(Dictionnaire* dictionnaire) {
    FILE *pf = fopen("dict.txt", "r"); //On ouvre le fichier "dict.txt" en mode lecture (pas besoin w car on veut seulement le charger)
    if (pf == NULL) { //Si le dictionnaire n'est pas trouvé, on va en créer un nouveau, via la structure Dictionnaire
        printf("dict.txt introuvable, un nouveau fichier va etre cree.\n");
        dictionnaire->ligne = malloc(TAILLE_PHYSIQUE * sizeof(Ligne));
        if (dictionnaire->ligne == NULL) {
            printf("Erreur: Echec de l'allocation de la memoire...\n");
            fclose(pf);
            exit(EXIT_FAILURE);
        }
        dictionnaire->taille = 0;
        dictionnaire->capacite = TAILLE_PHYSIQUE;
        return;
    }

    dictionnaire->ligne = malloc(TAILLE_PHYSIQUE * sizeof(Ligne));
    if (dictionnaire->ligne == NULL) {
        printf("Erreur : Echec de l'allocation memoire..\n");
        fclose(pf);
        exit(EXIT_FAILURE);
    }
    dictionnaire->taille = 0;
    dictionnaire->capacite = TAILLE_PHYSIQUE;

    char ligne[LONGUEUR_MOTS_MAX * 3]; //Une ligne contient 3 valeurs, le mot, la définition et la traduction
    while(fgets(ligne, sizeof(ligne), pf)) {
        char mot[LONGUEUR_MOTS_MAX];
        char definition[LONGUEUR_DEFINITION_MAX];
        char traduction[LONGUEUR_MOTS_MAX];
        //A chaque ligne du dictionnaire, on va extraire le mot, la définition et la traduction à chaque ligne via sscanf (le délimiteur sera ":")
        if (sscanf(ligne, "%[^:]:%[^:]:%[^\n]", mot, definition, traduction) == 3) ajouterMot(dictionnaire,mot,definition,traduction, 0);
        else printf("Ligne ignoree (format incorrect) : %s\n", ligne); //Si le format est incorrect, le programmme le fait savoir et ne la prend pas en compte
    }
    fclose(pf);
    printf("dict.txt charge avec succes! :)\n");
}

void afficherDictionnaire(Dictionnaire* dictionnaire) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    printf("Affichage du dictionnaire sous la forme: mot, definition, traduction :\n\n");
    for (int i = 0; i < dictionnaire->taille; i++) {
        printf("%s, %s, %s\n", dictionnaire->ligne[i].mot, dictionnaire->ligne[i].definition, dictionnaire->ligne[i].traduction);
    }
}

void ajouterMot(Dictionnaire* dictionnaire, char *mot, char* definition, char* traduction, int afficherMessage) {
    //La saisie du mot, definition et de la traduction se fera dans le sous-programme menu (à l'aide d'un switch)
    //Avant d'ajouter le mot, on s'assure qu'il y a sufffisament de place allouée, sinon, on réalloue l'espace nécéssaire
    if (dictionnaire->taille == dictionnaire->capacite) redimensionnerDictionnaire(dictionnaire);
    //Après toutes les précautions prises, on peut enfin ajouter le mot au dictionnaire
    strcpy(dictionnaire->ligne[dictionnaire->taille].mot, mot);
    strcpy(dictionnaire->ligne[dictionnaire->taille].definition, definition);
    strcpy(dictionnaire->ligne[dictionnaire->taille].traduction, traduction);
    dictionnaire->taille++;
    if (afficherMessage) printf("Mot ajoute avec succes ! :)\n");
}

void supprimerMot(Dictionnaire* dictionnaire, char *mot) {
    //L'index du mot à supprimer est une variable temporaire, qu'on utilisera pour décaler tous les éléments de 1 (à partir du mot qu'on souhaite supprimer)
    int index_mot_a_supprimer = rechercherMot();
    if (index_mot_a_supprimer == -1) {
        printf("Erreur : Ce mot n'est pas present dans le dictionnaire...\n");
        return;
    }
    //Décale de 1 emplacement chaque entrées situés après celle du mot à supprimer, pour combler le vide provoqué par sa suppression
    for (int i = index_mot_a_supprimer; i < dictionnaire->taille - 1; i++) {
        dictionnaire->ligne[i] = dictionnaire->ligne[i + 1];
    }
    dictionnaire->taille--; //Comme on a supprimé un élément, on supprime un emplacement de la taille
    printf("Mot supprime avec succes ! :)");
}

void afficherDefinition(Dictionnaire* dictionnaire, char *mot) {
    for (int i = 0; i < dictionnaire->taille; i++) {
        //Lorsque le mot est trouvé, on affiche la définition correspondante (.définition)
        if (strcmp(dictionnaire->ligne[i].mot, mot) == 0) {
            printf("Definition de %s : %s\n",mot,dictionnaire->ligne[i].definition);
            return;
        }
    }
    printf("Erreur : Ce mot n'est pas present dans le dictionnaire...\n");
}

void afficherTraduction(Dictionnaire* dictionnaire, char* mot) {
    for (int i = 0; i < dictionnaire->taille; i++) {
        //Lorsque le mot est trouvé, on affiche la traduction correspondante (.traduction)
        if (strcmp(dictionnaire->ligne[i].mot, mot) == 0) {
            printf("Traduction de %s : %s\n", mot, dictionnaire->ligne[i].traduction);
            return;
        }
    }
    printf("Erreur : Ce mot n'est pas present dans le dictionnaire...\n");
}

void sauvegardeDictionnaire(Dictionnaire* dictionnaire) {
    FILE *pf = fopen("dict.txt", "w");
    if (pf == NULL) {
        printf("Erreur : Le fichier n'a pas pu etre ouvert...\n");
        return;
    }
    for (int i = 0; i < dictionnaire->taille; i++) fprintf(pf, "%s:%s:%s\n", dictionnaire->ligne[i].mot, dictionnaire->ligne[i].definition, dictionnaire->ligne[i].traduction);
    fclose(pf);
    printf("Le dictionnaire a etait sauvegarde avec succes !\n");
}

void redimensionnerDictionnaire(Dictionnaire* dictionnaire) {
    dictionnaire->capacite*=2; //On multiplie la capacite par 2, pour eviter un appel trop frequent à realloc, qui pourrait nuire aux performances et à la vitesse d'execution
    dictionnaire->ligne = realloc(dictionnaire->ligne, dictionnaire->capacite * sizeof(Ligne));
    if (dictionnaire->ligne == NULL) {
        printf("Erreur: L'allocation de la memoire à echouee...\n");
        exit(EXIT_FAILURE);
    }
}

void lireChaineDeCaracteres(char* chaine, int taille_max) {
    if (fgets(chaine, taille_max, stdin) != NULL) chaine[strcspn(chaine, "\n")] = '\0';
    /* strlen(chaine) == taille_max - 1 : La chaîne lue occupe tout l'espace disponible, indique si l'utilisateur a atteint la limite possible.
     * chaine[taille_max - 2] != '\n' : Dernier caractère lu avant la limite n’est pas un saut de ligne (\n). L'abscence de \n signifie que l'utilisateur a entré trop de caractères.
     * Si ces 2 conditions sont réunis, il faut vider le tampon d'entrée */
    if (strlen(chaine) == taille_max - 1 && chaine[taille_max - 2] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); //EOF = Fin du fichier
    }
}

int rechercherMot(Dictionnaire* dictionnaire, char* mot) {
    for (int i = 0; i < dictionnaire->taille; i++) {
        if (strcmp(dictionnaire->ligne[i].mot, mot) == 0) { //Si la chaine de caractère est trouvée (est égale), on y associe l'index correspondant
            return i;
        }
    }
    return -1; //Sinon, on return -1, cela s'interpretera par la suite par un message d'erreur
}

void ajoutSynonyme(Dictionnaire* dictionnaire, char* mot) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    char synonyme[LONGUEUR_MOTS_MAX];

    printf("Le synonyme de quel mot voulez-vous ajouter ?\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;
    int index_mot = rechercherMot(dictionnaire, mot);
    if (index_mot == -1) {
        printf("Erreur : Ce mot n'est pas present dans le dictionnaire...\n");
        return;
    }
    printf("Saisissez le synonyme (anglais) :\n");
    lireChaineDeCaracteres(synonyme, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(synonyme, LONGUEUR_MOTS_MAX)) return;
    if (preventionCaracteresInterdits(synonyme)) return;
    if (preventionDoublonSynonyme(dictionnaire->ligne[index_mot].traduction, synonyme)) return;
    strcat(dictionnaire->ligne[index_mot].traduction, "/");
    strcat(dictionnaire->ligne[index_mot].traduction, synonyme);
    printf("Synonyme anglais ajoute avec succes !\n");
}

void supprimerSynonyme(Dictionnaire* dictionnaire, char* mot) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    char synonyme[LONGUEUR_MOTS_MAX];
    printf("Le synonyme de quel mot voulez-vous supprimer ?\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;
    int index_mot = rechercherMot(dictionnaire, mot);
    if (index_mot == -1) {
        printf("Erreur : Ce mot n'est pas present dans le dictionnaire...\n");
        return;
    }
    printf("Saisissez le synonyme que vous voulez supprimer :\n");
    lireChaineDeCaracteres(synonyme, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(synonyme, LONGUEUR_MOTS_MAX)) return;
    if (preventionCaracteresInterdits(synonyme)) return;
    char* debut_synonyme = strstr(dictionnaire->ligne[index_mot].traduction, synonyme);
    if (debut_synonyme == NULL) {
        printf("Erreur : Le synonyme saisi n'existe pas dans les traductions du mot...\n");
        return;
    }
    size_t longueur_synonyme = strlen(synonyme);
    if (*(debut_synonyme + longueur_synonyme) == '/') memmove(debut_synonyme, debut_synonyme + longueur_synonyme + 1, strlen(debut_synonyme + longueur_synonyme + 1) + 1);
    else if (debut_synonyme != dictionnaire->ligne[index_mot].traduction) *(debut_synonyme - 1) = '\0';
    else {
        printf("Erreur : Impossible de supprimer une traduction qui n'a pas de synonyme...\n");
        return;
    }
    printf("Synonyme supprime avec succes !\n");
}

void modifierSynonyme(Dictionnaire* dictionnaire, char* mot) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    char synonyme_a_supprimer[LONGUEUR_MOTS_MAX];
    char synonyme_a_ajouter[LONGUEUR_MOTS_MAX];
    printf("Le synonyme de quel mot voulez-vous modifier ?\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;

    int index_mot = rechercherMot(dictionnaire, mot);
    if (index_mot == -1) {
        printf("Erreur : Ce mot n'est pas present dans le dictionnaire...\n");
        return;
    }

    printf("Saisissez le synonyme que vous voulez modifier :\n");
    lireChaineDeCaracteres(synonyme_a_supprimer, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(synonyme_a_supprimer, LONGUEUR_MOTS_MAX)) return;
    if (preventionCaracteresInterdits(synonyme_a_supprimer)) return;

    char* debut_synonyme_a_supprimer = strstr(dictionnaire->ligne[index_mot].traduction, synonyme_a_supprimer);
    if (debut_synonyme_a_supprimer == NULL) {
        printf("Erreur : Le synonyme saisi n'existe pas dans les traductions du mot...\n");
        return;
    }

    printf("Saisissez le nouveau synonyme :\n");
    lireChaineDeCaracteres(synonyme_a_ajouter, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(synonyme_a_ajouter, LONGUEUR_MOTS_MAX)) return;
    if (preventionCaracteresInterdits(synonyme_a_ajouter)) return;
    if (preventionDoublonSynonyme(dictionnaire->ligne[index_mot].traduction, synonyme_a_ajouter)) return;

    size_t longueur_synonyme_a_supprimer = strlen(synonyme_a_supprimer);
    if (*(debut_synonyme_a_supprimer + longueur_synonyme_a_supprimer) == '/') memmove(debut_synonyme_a_supprimer, debut_synonyme_a_supprimer + longueur_synonyme_a_supprimer + 1, strlen(debut_synonyme_a_supprimer + longueur_synonyme_a_supprimer + 1) + 1);
    else if (debut_synonyme_a_supprimer != dictionnaire->ligne[index_mot].traduction) *(debut_synonyme_a_supprimer - 1) = '\0';
    else {
        printf("Erreur : Impossible de modifier une traduction qui n'a pas de synonyme...\n");
        return;
    }
    strcat(dictionnaire->ligne[index_mot].traduction, "/");
    strcat(dictionnaire->ligne[index_mot].traduction, synonyme_a_ajouter);
    printf("Synonyme modifie avec succes !\n");

}

void jeuApprentissage(Dictionnaire* dictionnaire) {
    char reponse[LONGUEUR_MOTS_MAX];
    if (preventionCaracteresInterdits(dictionnaire)) return;
    srand(time(NULL));
    int index_mot_a_deviner = rand() % dictionnaire->taille;
    printf("Quel est la traduction du mot %s ?\n", dictionnaire->ligne[index_mot_a_deviner].mot);
    lireChaineDeCaracteres(reponse, LONGUEUR_MOTS_MAX);
    char* liste_synonymes = dictionnaire->ligne[index_mot_a_deviner].traduction;
    char* synonyme = strtok(liste_synonymes, "/");
    while (synonyme != NULL) {
        if (strcmp(synonyme, reponse)==0) {
            printf("Bonne reponse !\n");
            return;
        }
        synonyme = strtok(NULL, "/");
    }
    printf("Mauvaise reponse... La reponse correcte etait : %s\n",dictionnaire->ligne[index_mot_a_deviner].traduction);
}

int preventionDictionnaireVide(Dictionnaire* dictionnaire) {
    if (dictionnaire->taille == 0) {
        printf("Erreur : Le dictionnaire est vide...\n");
        return 1;
    }
    return 0;
}

int preventionDepassementTailleMot(char* chaine, int taille_max) {
    if (strlen(chaine) == taille_max - 1) {
        printf("Erreur : La limite des %d caracteres est depassee...\n", taille_max);
        return 1;
    }
    return 0;
}

int preventionCaracteresInterdits(char* chaine) {
    while (*chaine != '\0') {
        if (*chaine == ',' || *chaine == '/') {
            printf("Erreur : Vous ne pouvez pas entrer ',' ou '/'.\n");
            return 1;
        }
        chaine++;
    }
    return 0;
}

int preventionDoublon(Dictionnaire* dictionnaire, char* mot) {
    for (int i = 0; i < dictionnaire->taille; i++) {
        if (strcmp(dictionnaire->ligne[i].mot, mot) == 0) {
            printf("Erreur : Le mot saisi existe deja...\n");
            return 1;
        }
    }
    return 0;
}

int preventionDoublonSynonyme(char* liste_synonymes, char* synonyme) {
    char copie_liste_synonymes[LONGUEUR_MOTS_MAX];
    strncpy(copie_liste_synonymes, liste_synonymes, LONGUEUR_MOTS_MAX);
    copie_liste_synonymes[LONGUEUR_MOTS_MAX - 1] = '\0';
    char* division_liste = strtok(copie_liste_synonymes, "/");
    while (division_liste != NULL) {
        if (strcmp(division_liste, synonyme) == 0) {
            printf("Erreur : Le synonyme existe deja...\n");
            return 1;
        }
        division_liste = strtok(NULL, "/");
    }
    return 0;
}

void choix2(Dictionnaire* dictionnaire,char* mot, char* definition, char* traduction) { //Pour eviter d'avoir trop de texte dans menu, correspond au choix N°2
    printf("Saisissez le mot que vous souhaitez ajouter (30 caracteres max) :\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;
    if (preventionCaracteresInterdits(mot)) return;
    if (preventionDoublon(dictionnaire, mot)) return;

    printf("Ajoutez sa definition (100 caracteres max) :\n");
    lireChaineDeCaracteres(definition, LONGUEUR_DEFINITION_MAX);
    if (preventionDepassementTailleMot(definition, LONGUEUR_DEFINITION_MAX)) return;
    if (preventionCaracteresInterdits(definition)) return;

    printf("Enfin, ajoutez sa traduction (30 caracteres max):\n");
    lireChaineDeCaracteres(traduction, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(traduction, LONGUEUR_MOTS_MAX)) return;
    if (preventionCaracteresInterdits(traduction)) return;
    if (strlen(mot) < LONGUEUR_MOTS_MAX - 1 && strlen(definition) < LONGUEUR_DEFINITION_MAX - 1 && strlen(traduction) < LONGUEUR_MOTS_MAX - 1) {
        ajouterMot(dictionnaire, mot, definition, traduction, 1);
    }
}

void choix3(Dictionnaire* dictionnaire, char* mot) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    printf("Saisissez le mot que vous souhaitez supprimer :\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;
    supprimerMot(dictionnaire, mot);
}

void choix4(Dictionnaire* dictionnaire, char* mot) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    printf("La definition de quel mot souhaitez-vous afficher ?\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;
    afficherDefinition(dictionnaire, mot);
}

void choix5(Dictionnaire* dictionnaire, char* mot) {
    if (preventionDictionnaireVide(dictionnaire)) return;
    printf("La traduction de quel mot souhaitez-vous afficher ?\n");
    lireChaineDeCaracteres(mot, LONGUEUR_MOTS_MAX);
    if (preventionDepassementTailleMot(mot, LONGUEUR_MOTS_MAX)) return;
    afficherTraduction(dictionnaire, mot);
}

void choix6(Dictionnaire* dictionnaire, char* mot) {
    int choix;
    if (preventionDictionnaireVide(dictionnaire)) return;
    printf("Gestion des synonymes :\n");
    printf("1. Ajouter un synonyme\n");
    printf("2. Supprimer un synonyme\n");
    printf("3. Modifier un synonyme\n");
    printf("Votre choix :\n");
    scanf("%d", &choix);
    getchar();
    switch (choix) {
        case 1:
            ajoutSynonyme(dictionnaire, mot);
            return;
        case 2:
            supprimerSynonyme(dictionnaire, mot);
            return;
        case 3:
            modifierSynonyme(dictionnaire, mot);
            return;
        default:
            printf("Erreur : Le choix saisi n'est pas valide...\n");
    }
}

void menu(Dictionnaire* dictionnaire) {
    int choix;
    char mot[LONGUEUR_MOTS_MAX];
    char definition[LONGUEUR_DEFINITION_MAX];
    char traduction[LONGUEUR_MOTS_MAX];

    do {
        printf("\nMenu :\n");
        printf("1. Afficher le dictionnaire complet\n");
        printf("2. Ajouter un mot\n");
        printf("3. Supprimer un mot\n");
        printf("4. Afficher la definition d'un mot\n");
        printf("5. Afficher la traduction d'un mot\n");
        printf("6. Gestion des synonymes\n");
        printf("7. Jeu d'Apprentissage Linguistique\n");
        printf("8. Sauvegarder et quitter\n");
        printf("Votre choix : \n");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                afficherDictionnaire(dictionnaire);
                break;
            case 2:
                choix2(dictionnaire, mot, definition, traduction);
                break;
            case 3:
                choix3(dictionnaire, mot);
                break;
            case 4:
                choix4(dictionnaire, mot);
                break;
            case 5:
                choix5(dictionnaire, mot);
                break;
            case 6:
                choix6(dictionnaire, mot);
                break;
            case 7:
                jeuApprentissage(dictionnaire);
                break;
            case 8:
                sauvegardeDictionnaire(dictionnaire);
                break;
            default:
                printf("Erreur : Le choix saisi n'est pas valide...\n");
        }
    } while (choix != 8);
}