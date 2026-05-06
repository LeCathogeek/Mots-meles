//
// Created by etienne on 06/05/2026.
//
#include "parametres.h"

void parametres(int* dimensions, Boolean* diagonale, int* time) {
    printf("\033[2J\033[H");
    printf("Bonjour ! Avant de commencer une partie, veuillez nous indiquer les dimensions de votre grille de jeu.\n - Votre grille peut avoir une taille allant de 8 x 8 a 16 x 16.\n - Votre grille peut etre rectangulaire.\nAppuyez sur Entree pour continuer.\n");
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