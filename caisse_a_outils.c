//
// Created by etienne on 29/04/2026.
//
#include "caisse_a_outils.h"

void ensure_save_file() {
    FILE *file;
    file = fopen("save.txt", "r");
    if (file == NULL) {
        file = fopen("save.txt", "w");
        fputs("", file);
        fclose(file);
    }
}

int controle_d_acquisition() {
    char choix[10];
    int result = 0;
    do {
        printf("\033[2J\033[H");
        printf("Que voulez-vous faire ? (entrez comme réponse l'entier correspondant)\n  - Demarrer une partie (0)\n  - Afficher les meilleurs scores (1)\n  - Quitter (2)\n");
        fgets(choix, sizeof(choix),  stdin);
        if (choix[0] != '0' && choix[0] != '1' && choix[0] != '2') {
            printf("Attention ! Votre réponse est incorrecte !\nDonnez un entier situe entre 0 et 2 indiquant votre réponse.\n");
        }
    } while (choix[0] != '0' && choix[0] != '1' && choix[0] != '2');
    sscanf(&choix[0], "%d", &result);
    return result;
}

void jeu() {
    printf("\033[2J\033[H");
    int dimensions[2] = {8, 8};
    Boolean diagonale = false;
    int time;
    parametres(dimensions, &diagonale, &time);
    char** grille = generation_grille(dimensions, diagonale);
    affichage_grille(grille, dimensions);
}

void parametres(int* dimensions, Boolean* diagonale, int* time) {
    printf("\033[2J\033[H");
    printf("Bonjour ! Avant de commencer une partie, veuillez nous indiquer les dimensions de votre grille de jeu.\n - Votre grille peut avoir une taille allant de 8 x 8 a 16 x 16.\n - Votre grille peut etre rectangulaire.\n");
    get_dimensions(dimensions);
    get_diagonale(diagonale);
    get_time(time);
}

void get_dimensions(int* dimensions) {
    int tmp = 8;
    char dim[10] = "";
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\033[2J\033[H");
    for (int i = 1; i < 3; i++) {
        do {
            printf("Veuillez entrer la valeur de la dimension %d. (Un nombre entier situe entre 8 et 16)\n", i);
            fgets(dim, sizeof(dim), stdin);
            sscanf(dim, "%d", &tmp);
            if (tmp < 8 || tmp > 16) {
                printf("Attention ! Vous n'avez pas fourni une dimension correcte !\nEntrez un nombre entier compris entre 8 et 16 !\n");
            }
        } while (tmp < 8 || tmp > 16);
        if (i == 1) {
            dimensions[0] = tmp;
        }
        else {
            dimensions[1] = tmp;
        }
    }
    printf("Les dimensions de la grille ont bien ete configurees !\nVotre grille fait %dx%d cases.\n", dimensions[0], dimensions[1]);
}

void get_diagonale(Boolean* diagonale) {
  printf("\033[2J\033[H");
  char tmp[10];
  int choice = 2;
  do {
    printf("Voulez-vous jouer avec la regle des diagonales ? Tapez 0 pour non et 1 pour oui.\n");
      fgets(tmp, sizeof(tmp), stdin);
      sscanf(tmp, "%d", &choice);
      if (choice != 0 && choice != 1) {
          printf("Attention ! Tapez 0 pour non et 1 pour oui.\n");
      }
  } while (choice != 0 && choice != 1);
  *diagonale = choice;
    if (*diagonale == true) {
        printf("Vous avez choisi la regle des diagonales.\n");
    }
    else {
        printf("Vous avez refuse de jouer avec des mots en diagonale.\n");
    }
}

void get_time(int* time) {
    printf("\033[2J\033[H");
    char tmp[10];
    int choice = 0;
    do {
        printf("Combien de temps voulez-vous jouer ? Entrez votre réponse en secondes (entre 60 et 180 secondes)\n");
        fgets(tmp, sizeof(tmp), stdin);
        sscanf(tmp, "%d", &choice);
        if (choice < 60 || choice > 180) {
            printf("Attention ! Entrez bien un entier compris en 60 et 180.\n");
        }
    } while (choice < 60 || choice > 180);
    *time = choice;
    printf("Vous voulez jouer %d secondes.\n", choice);
}

char** generation_grille(int* dimensions, Boolean diagonale) {
    printf("\033[2J\033[H");
    printf("Generation de la grille...\nPatientez...\n");
    char** grille = (char**) malloc(dimensions[0] * sizeof(char*));
    for (int i = 0; i < dimensions[0]; i++) {
        grille[i] = malloc(dimensions[1] * sizeof(char));
    }
    for (int i = 0; i < dimensions[0]; i++) {
        for (int j = 0; j < dimensions[1]; j++) {
          grille[i][j] = '@';
        }
    }
    int nombre_de_lettres = dimensions[recherche_minimum(dimensions, 2)];
    while (nombre_de_lettres > 2) {
      nombre_de_lettres--;
    }
    complete_grille(grille, dimensions);
    return grille;
}

SensDirection choix_sens_direction() {
    SensDirection le_sens_direction;
    int direction = rand() % 3;
    le_sens_direction.direction = direction;
    int sens = rand() % 2;
    le_sens_direction.sens = sens;
    return le_sens_direction;
}

int recherche_minimum(int* tableau, int size) {
    int minimum = 0;
    for (int i = 0; i < size; i++) {
        if (tableau[minimum] < tableau[i]) {
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
    for (int i = 0; i < dimensions[0]; i++) {
        printf("--- ");
    }
    printf("\n");
    for (int k = 0; k < dimensions[0]; k++) {
        printf("|");
        for (int j = 0; j < dimensions[1]; j++) {
            printf(" %c |", grille[k][j]);
        }
        printf("\n");
        printf(" ");
        for (int i = 0; i < dimensions[0]; i++) {
            printf("--- ");
        }
        printf("\n");
    }
    printf("\n");
}

void scores() {
    printf("\033[2J\033[H");
}