//
// Created by etienne on 06/05/2026.
//
#include "grid.h"

grille_mots generation_grille(int* dimensions, Boolean diagonale) {
    //Nettoyage de l'affichage et message d'attente
    printf("\033[2J\033[H");
    printf("Generation de la grille...\nPatientez...\n");

    //Initialisation de la structure (grille, mots cachés dans la grille et nombre de mots)
    grille_mots ma_grille_mot;
    //Ainsi que des variables utilisées pour ma_grille_mot
    int index_mots = 0;
    char** liste_mots = NULL;

    //Initialisation de la grille elle-même (en 2D)
    char** grille = (char**) malloc(dimensions[0] * sizeof(char*));
    for (int i = 0; i < dimensions[0]; i++) {
        grille[i] = malloc(dimensions[1] * sizeof(char));
    }
    //On la remplit de @
    for (int i = 0; i < dimensions[0]; i++) {
        for (int j = 0; j < dimensions[1]; j++) {
          grille[i][j] = '@';
        }
    }

    //Le nombre de lettres de base est celui de la plus petite dimension du tableau
    int nombre_de_lettres = dimensions[recherche_minimum(dimensions, 2)];
    char* mot;
    Boolean succes = true;

    //Tant que nos mots font au moins 3 lettres, on essaye de les placer comme on peut
    while (nombre_de_lettres > 2) {
      mot = tirer_mot(nombre_de_lettres);
      succes = placer_mot(grille, dimensions, mot, &diagonale);
        if (succes == true) {
            liste_mots = realloc(liste_mots, sizeof(char*) * (index_mots + 1));
            liste_mots[index_mots] = mot;
            index_mots++;
        }
        else {
          nombre_de_lettres--;
      }
    }

    //On complète les trous restants de la grille (les @) avec des lettres random
    complete_grille(grille, dimensions);

    //On place nos infos dans notre structure ma_grille_mot et on la renvoie
    ma_grille_mot.grille = grille;
    ma_grille_mot.mots = liste_mots;
    ma_grille_mot.nb_mots = index_mots;
    return ma_grille_mot;
}

Boolean placer_mot(char** grille, int* dimensions, char* mot, Boolean* diagonale) {
    //Initialisation des variables de base

    //Le déplacement
    int dx = 0;
    int dy = 0;

    //La position initialie
    int start_x;
    int start_y;

    //La position actuelle
    int x;
    int y;

    //Le nombre de lettres actuellement pouvant être placées et la longueur du mot
    int lettres;
    int longueur = strlen(mot);

    //On essaie 50 fois (si on y arrive pas, on considère qu'on ne peut plus placer de mots de cette taille)
    for (int i = 0; i < 50; i++) {
        //On choisit une direction random
        choix_sens_direction(diagonale, &dx, &dy);
        if (dx == 1) {
            //Si on avance vers la droite, on place le mot entre le début et la place la plus loin possible
            x = rand() % (dimensions[0] - longueur + 1);
        } else if (dx == -1) {
            //Si on va vers la gauche, on se place vers la fin
            x = rand() % (dimensions[0] - longueur + 1) + (longueur - 1);
        } else {
            //Sinon, on se place où l'on veut
            x = rand() % dimensions[0];
        }

        if (dy == 1) {
            //On se place vers le haut de la matrice
            y = rand() % (dimensions[1] - longueur + 1);
        } else if (dy == -1) {
            //On se place vers le bas de la matrice
            y = rand() % (dimensions[1] - longueur + 1) + (longueur - 1);
        } else {
            //On se place n'importe où
            y = rand() % dimensions[1];
        }

        //On affecte nos positions initiales
        start_x = x;
        start_y = y;
        lettres = 0;

        //Tant qu'on peut placer nos lettres (que les cases traversées sont des @), on continue...
        while (((x >= 0 && x < dimensions[0]) && (y >= 0 && y < dimensions[1])) && (grille[x][y] == '@' || grille[x][y] == mot[lettres]) && lettres < longueur) {
            x += dx;
            y += dy;
            lettres++;
        }
        //Si on est arrivé au bout, alors on place vraiment notre mot
        if (lettres == longueur) {
            x = start_x;
            y = start_y;
            for (int i = 0; i < longueur; i++) {
                grille[x][y] = mot[i];
                x += dx;
                y += dy;
            }
            //Et on retourne true
            return true;
        }
    }
    //Sinon on n'a pas pu placer et on retourne false
    return false;
}

void choix_sens_direction(Boolean* diagonale_autorise, int* dx, int* dy) {
    *dx = 0;
    *dy = 0;
    SensDirection le_sens_direction;
    int direction;
    int sens;
    if (*diagonale_autorise==true) {
        direction = rand() % 3;
    }
    else {
        direction = rand() % 2;
    }
    le_sens_direction.direction = direction;
    sens = rand() % 2;
    le_sens_direction.sens = sens;
    if (le_sens_direction.direction == horizontal) {
        *dx = 1;
    }
    else {
        if (le_sens_direction.direction == vertical) {
            *dy = 1;
        }
        else {
            *dx = 1;
            *dy = 1;
        }
    }
    if (le_sens_direction.sens == envers) {
        *dx = -*dx;
        *dy = -*dy;
    }
}

int recherche_minimum(int* tableau, int size) {
    int minimum = 0;
    for (int i = 0; i < size; i++) {
        if (tableau[i] < tableau[minimum]) {
            minimum = i;
        }
    }
    return minimum;
}

void complete_grille(char** grille, int* dimensions) {
    for (int i = 0; i < dimensions[0]; i++) {
    for (int j = 0; j < dimensions[1]; j++) {
      if (grille[i][j] == '@') {
          grille[i][j] = rand() % 26 + 65;
      }
    }
    }
}

void affichage_grille(char** grille, int* dimensions) {
    printf(" ");
    for (int i = 0; i < dimensions[1]; i++) {
        printf("--- ");
    }
    printf("\n");
    for (int k = 0; k < dimensions[0]; k++) {
        printf("|");
        for (int j = 0; j < dimensions[1]; j++) {
            printf(" %c |", grille[k][j]);
        }
        printf("\n");
    }
    printf(" ");
    for (int i = 0; i < dimensions[1]; i++) {
        printf("--- ");
    }
    printf("\n");
}


char* tirer_mot(int longueur) {
    char* mots_3[] = {"ARA", "RAT", "TRI", "SUR", "BOB"};
    char* mots_4[] = {"BANC", "TROP", "TARD", "PERD", "BOIS", "CHAT", "PAPA", "ETRE", "SANS", "SANG", "AGIR"};
    char* mots_5[] = {"CLAIR", "RATON", "ARBRE", "IDIOT", "MAMAN", "ALICE", "HETER", "CHENE"};
    char* mots_6[] = {"RENARD", "OBSCUR"};
    char* mots_7[] = {"REPTILE", "ABRICOT", "GRATUIT"};
    char* mots_8[] = {"ABDIQUAT"};
    char* mots_9[] = {"ABOIERONS", "CARREMENT"};
    char* mots_10[] = {"ABOMINABLE"};
    char* mots_11[] = {"ABIMERAIENT"};
    char* mots_12[] = {"INFORMATIQUE"};
    char* mots_13[] = {"ABRUTISSANTES"};
    char* mots_14[] = {"ACCOMPLIRAIENT", "HYPOCONDRIAQUE"};
    char* mots_15[] = {"AFFRANCHISSABLE"};
    char* mots_16[] = {"ABASOURDISSAIENT"};
    if (longueur == 3) {
        return mots_3[rand() % (sizeof(mots_3) / sizeof(mots_3[0]))];
    }
    if (longueur == 4) {
        return mots_4[rand() % (sizeof(mots_4) / sizeof(mots_4[0]))];
    }
    if (longueur == 5) {
        return mots_5[rand() % (sizeof(mots_5) / sizeof(mots_5[0]))];
    }
    if (longueur == 6) {
        return mots_6[rand() % (sizeof(mots_6) / sizeof(mots_6[0]))];
    }
    if (longueur == 7) {
        return mots_7[rand() % (sizeof(mots_7) / sizeof(mots_7[0]))];
    }
    if (longueur == 8) {
        return mots_8[rand() % (sizeof(mots_8) / sizeof(mots_8[0]))];
    }
    if (longueur == 9) {
        return mots_9[rand() % (sizeof(mots_9) / sizeof(mots_9[0]))];
    }
    if (longueur == 10) {
        return mots_10[rand() % (sizeof(mots_10) / sizeof(mots_10[0]))];
    }
    if (longueur == 11) {
        return mots_11[rand() % (sizeof(mots_11) / sizeof(mots_11[0]))];
    }
    if (longueur == 12) {
        return mots_12[rand() % (sizeof(mots_12) / sizeof(mots_12[0]))];
    }
    if (longueur == 13) {
        return mots_13[rand() % (sizeof(mots_13) / sizeof(mots_13[0]))];
    }
    if (longueur == 14) {
        return mots_14[rand() % (sizeof(mots_14) / sizeof(mots_14[0]))];
    }
    if (longueur == 15) {
        return mots_15[rand() % (sizeof(mots_15) / sizeof(mots_15[0]))];
    }
    else {
        return mots_16[rand() % (sizeof(mots_16) / sizeof(mots_16[0]))];
    }
}