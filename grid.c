//
// Created by etienne on 06/05/2026.
//
#include "grid.h"

grille_mots generation_grille(int* dimensions, Boolean diagonale, Dictionnaire* dico, Mot* liste_mots_pos) {
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
    //On la remplit de caractères "@".
    for (int i = 0; i < dimensions[0]; i++) {
        for (int j = 0; j < dimensions[1]; j++) {
          grille[i][j] = '@';
        }
    }

    //Le nombre de lettres de base est celui de la plus petite dimension du tableau
    int nombre_de_lettres = dimensions[recherche_minimum(dimensions, 2)];
    char* mot;
    Boolean succes = true;
    int echecs_consecutifs = 0;  // Compteur d'échecs consécutifs

    //Tant que nos mots font au moins 3 lettres, on essaye de les placer comme on peut
    while (nombre_de_lettres > 2) {
        mot = tirer_mot_du_dico(dico, nombre_de_lettres);
        if (mot != NULL) {
            succes = placer_mot(grille, dimensions, mot, &diagonale, liste_mots_pos, index_mots);
            if (succes == true) {
                index_mots++;
                echecs_consecutifs = 0;  // Réinitialiser le compteur en cas de succès
                char** tmp = realloc(liste_mots, sizeof(char*) * index_mots);
                if (tmp == NULL) {
                    printf("Erreur lors de la réallocation.\n");
                }
                else {
                    liste_mots = tmp;
                    liste_mots[index_mots - 1] = mot;
                }
            }
            else {
                echecs_consecutifs++;
                // Si 5 échecs consécutifs, passer à une longueur inférieure
                if (echecs_consecutifs >= 5) {
                    nombre_de_lettres--;
                    echecs_consecutifs = 0;
                }
            }
        }
        else {
            echecs_consecutifs++;
            if (echecs_consecutifs >= 5) {
                nombre_de_lettres--;
                echecs_consecutifs = 0;
            }
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

Boolean placer_mot(char** grille, int* dimensions, char* mot, Boolean* diagonale, Mot* liste_mots, int index_mots) {
    //Initialisation des variables de base

    //Le déplacement
    int dx = 0;
    int dy = 0;

    //La position initiale
    int start_x;
    int start_y;

    //La position actuelle
    int x;
    int y;

    //Le nombre de lettres actuellement pouvant être placées et la longueur du mot
    int lettres;
    int longueur = strlen(mot);

    //On essaie 50 fois (si on n'y arrive pas, on considère qu'on ne peut plus placer de mots de cette taille).
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
            liste_mots = (Mot*) realloc(liste_mots, sizeof(Mot) * (index_mots + 1));
            if (liste_mots == NULL) {
                printf("Erreur lors de la réallocation !\n");
                return false;
            }
            liste_mots[index_mots].mot = mot;
            liste_mots[index_mots].longueur = longueur;
            liste_mots[index_mots].start_x = start_x;
            liste_mots[index_mots].start_y = start_y;
            liste_mots[index_mots].end_x = x;
            liste_mots[index_mots].end_y = y;
            //Et on retourne true
            return true;
        }
    }
    //Sinon on n'a pas pu placer et on retourne false
    return false;
}

void choix_sens_direction(Boolean* diagonale_autorise, int* dx, int* dy) {
    //On réinitialise nos valeurs de direction en commençant à 0 pour dx et dy
    *dx = 0;
    *dy = 0;

    //On prépare notre SensDirection
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
    //Recherche de minimum classique
    int minimum = 0;
    for (int i = 0; i < size; i++) {
        if (tableau[i] < tableau[minimum]) {
            minimum = i;
        }
    }
    return minimum;
}

void complete_grille(char** grille, int* dimensions) {
    //On parcourt notre tableau à deux dimensions, si on trouve un @ on le remplace par un caractère
    //ASCII random entre 65 et 91 (les lettres de l'alphabet en majuscule).
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

Dictionnaire* charger_dictionnaire() {
    printf("Chargement de tous les mots...\n");
    FILE* fichier = fopen("dictionnaire.txt", "r");
    if (fichier == NULL) {
        printf("Attention ! Impossible d'ouvrir le fichier !\n");
        return NULL;
    }
    //On initialise notre gros dictionnaire qui contiendra tous nos mots.
    Dictionnaire* dico = (Dictionnaire*) malloc(sizeof(Dictionnaire));
    dico->max_length = 16;
    dico->listes = (ListeMots*) malloc(dico->max_length * sizeof(ListeMots));
    char buffer[256];
    int longueur;
    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        // En fait dès que l'on voit un \n on s'arrête et on garde la première partie de la chaîne
        buffer[strcspn(buffer, "\n")] = '\0';
        longueur = strlen(buffer);
        if (longueur > 0 && longueur < dico->max_length) {
            // Réallouer l'espace pour le mot
            ListeMots* liste = &dico->listes[longueur];
            char** tmp = realloc(liste->mots, (liste->count + 1) * sizeof(char*));
            if (tmp != NULL) {
                liste->mots = tmp;
                liste->mots[liste->count] = malloc(longueur + 1);
                strcpy(liste->mots[liste->count], buffer);
                liste->count++;
            }
        }
    }
    fclose(fichier);
    return dico;
}

char* tirer_mot_du_dico(Dictionnaire* dico, int longueur) {
    if (longueur <= 0 || longueur >= dico->max_length) {
        return NULL;
    }
    ListeMots* liste = &dico->listes[longueur];
    if (liste->count == 0) {
        return NULL;
    }
    return liste->mots[rand() % liste->count];
}

void liberer_dico(Dictionnaire* dico) {
    for (int i = 0; i < dico->max_length; i++) {
        for (int j = 0; j < dico->listes[i].count; j++) {
            free(dico->listes[i].mots[j]);
        }
        free(dico->listes[i].mots);
    }
    free(dico->listes);
    free(dico);
}
