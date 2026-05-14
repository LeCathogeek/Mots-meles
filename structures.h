//
// Created by etienne on 06/05/2026.
//

#ifndef U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_STRUCTURES_H
#define U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_STRUCTURES_H

typedef enum {false=0, true=1} Boolean;

typedef enum {horizontal=0, vertical=1, diagonal=2} Direction;

typedef enum {endroit=0, envers=1} Sens;

typedef struct {
    Direction direction;
    Sens sens;
} SensDirection;

typedef struct {
    char** grille;
    char** mots;
    int nb_mots;
}grille_mots;

typedef struct {
    char** mots;
    int count;
} ListeMots;

typedef struct {
    ListeMots* listes;
    int max_length;
} Dictionnaire;

typedef struct {
    char* nom;
    float score;
} Joueur;

typedef struct {
    int longueur;
    char* mot;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} Mot;

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_STRUCTURES_H
