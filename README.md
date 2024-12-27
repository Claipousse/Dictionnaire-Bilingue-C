Ce document décrit les consignes / le cahier des charges de ce projet de soutenance :

Projet : Gestionnaire d’un dictionnaire bilingue

L’objectif est de développer une application en C qui permet de gérer un dictionnaire
bilingue. Chaque ligne du dictionnaire est composée d’un mot en français, sa définition
et sa traduction en anglais. Le programme doit être capable de charger les mots, leurs
définitions et leurs traductions depuis un fichier texte, de les afficher, de permettre
l'ajout et la suppression de mots, ainsi que d'afficher les définitions et les traductions
d'un mot spécifique. Finalement, le programme doit pouvoir sauvegarder les mises à
jour, apportées au dictionnaire par le programme (ajout ou suppression d’un mot), dans
le fichier texte.

Description détaillée :

1. Structure des Données :

Le dictionnaire est sauvegardé en mémoire dans un fichier texte. Dans le programme, il
sera représenté par un tableau dynamique de structures. Ainsi, au lancement du
programme, le contenu du dictionnaire, présent dans le fichier texte, doit être chargé
dans le tableau dynamique.
Après chaque modification du dictionnaire, le contenu du fichier doit être synchronisé.

2. Fonctionnalités Principales :

Le programme demandé doit permettre de :
• Charger le dictionnaire depuis le fichier texte (dict.txt).
• Afficher tout le contenu du dictionnaire.
• Ajouter un nouveau mot avec sa définition et sa traduction.
• Supprimer un mot du dictionnaire (avec sa définition et sa traduction).
• Afficher la définition d'un mot spécifique.
• Afficher la traduction d'un mot spécifique.
• Sauvegarder le dictionnaire mis à jour dans un fichier texte (dict.txt).

3. Fichier d'entrée (dict.txt) :

Chaque ligne du fichier contient un mot, sa définition et sa traduction, séparés par des
deux-points (:). Voici un exemple de ligne dans le fichier "dict.txt" :
Voiture : moyen de transport terrestre : car

4. Interface Utilisateur :

Le programme doit afficher un menu avec les options disponibles et attend que
l'utilisateur choisisse une action. Les options du menu incluent :
• Afficher le dictionnaire complet.
• Ajouter un mot.
• Supprimer un mot.
• Afficher la définition d'un mot.
• Afficher la traduction d'un mot.
• Sauvegarder et quitter.

5. Gestion de la Mémoire :

Le programme doit gérer dynamiquement la mémoire pour le tableau de mots. Si le
tableau atteint sa capacité maximale, il doit être redimensionné pour accueillir plus de
mots.

BONUS

Améliorations fonctionnelles :

1. Prévention des doublons : Intégration d'une fonctionnalité permettant
d’empêcher l’enregistrement d’un mot déjà existant dans la base de données.
Cela garantit l’unicité des entrées et améliore la qualité des données.

2. Gestion des synonymes : Ajout de la possibilité d’associer plusieurs traductions
à un même mot, ce qui permet une gestion plus riche et flexible des
correspondances linguistiques.

Ajout d’une dimension ludique :
Jeu d’apprentissage linguistique : Développement d’une fonctionnalité
interactive où un mot en français est affiché, et l’utilisateur doit fournir sa
traduction. Le programme vérifiera la réponse et indiquera si elle est correcte ou
incorrecte, favorisant ainsi une expérience d’apprentissage engageante.
