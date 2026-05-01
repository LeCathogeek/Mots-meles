//
// Created by etienne on 29/04/2026.
//
#include "caisse_a_outils.h"


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
    char dim[10] = "25";
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
  char tmp[10];
  int choice = 2;
  do {
    printf("Voulez-vous jouer avec la regle des diagonales ? Tapez 0 pour non et 1 pour oui.\n");
      fgets(tmp, sizeof(tmp), stdin);
      sscanf(tmp, "%d", &choice);
      if (choice != 0 && choice != 1) {
          printf("Voulez-vous jouer avec la regle des diagonales ? Tapez 0 pour non et 1 pour oui.\n");
      }
  } while (choice != 0 && choice != 1);
  *diagonale = choice;
    if (*diagonale == true) {
        printf("Vous avez choisi la regle des diagonales.");
    }
    else {
        printf("Vous avez refuse de jouer avec des mots en diagonale.");
    }
}

void get_time(int* time) {

}

void scores() {
    printf("\033[2J\033[H");
}