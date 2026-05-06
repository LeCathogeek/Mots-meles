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
    float score = 0;
    int temps;
    char* nom_utilisateur;
    parametres(dimensions, &diagonale, &temps);
    grille_mots da_grille = generation_grille(dimensions, diagonale);
    affichage_grille(da_grille.grille, dimensions);
    time_t debut = time(0);
    time_t maintenant = time(0);
    char mot_devine[16];
    Boolean mot_trouve = false;
    int nb_mots_trouves = 0;
    printf("Nombre de mots : %d\n", da_grille.nb_mots);
    char** mots_trouves_user = (char**) malloc(sizeof(char*) * da_grille.nb_mots);
    while ((int)(maintenant - debut) < temps) {
        maintenant = time(0);
        printf("C'est parti ! Entrez un mot : \n");
        fgets(mot_devine, sizeof(mot_devine), stdin);
        mot_devine[strcspn(mot_devine, "\n")] = '\0';
        for (int i = 0; i < da_grille.nb_mots; i++) {
            if (da_grille.mots[i] != NULL && strcmp(da_grille.mots[i], mot_devine) == 0) {
                mot_trouve = true;
                nb_mots_trouves++;
                mots_trouves_user[nb_mots_trouves-1] = da_grille.mots[i];
                da_grille.mots[i] = NULL;
            }
        }
        if (mot_trouve) {
            printf("Felicitations ! Vous avez trouve le mot %s.\n", mot_devine);
        }
        else {
            printf("Mot incorrect ou déjà trouve !\n");
        }
        mot_trouve = false;
    }
    printf("La partie est terminée !\n");
    free(da_grille.grille);
    free(da_grille.mots);
    for (int i = 0; i < nb_mots_trouves ;i++) {
        score += pow(strlen(mots_trouves_user[i]), 4.0/3.0);
    }
    printf("Voici votre score : %.2f.\n", score);
    printf("Quel est votre nom ? \n");
    fgets(nom_utilisateur, sizeof(nom_utilisateur), stdin);
    save_score(nom_utilisateur, score);
    printf("Merci %s ! Votre nom a ete stocke au milieu de celui des vainqueurs !\n", nom_utilisateur);
}

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

grille_mots generation_grille(int* dimensions, Boolean diagonale) {
    printf("\033[2J\033[H");
    printf("Generation de la grille...\nPatientez...\n");
    grille_mots ma_grille_mot;
    int index_mots = 0;
    char** grille = (char**) malloc(dimensions[0] * sizeof(char*));
    char** liste_mots = NULL;
    for (int i = 0; i < dimensions[0]; i++) {
        grille[i] = malloc(dimensions[1] * sizeof(char));
    }
    for (int i = 0; i < dimensions[0]; i++) {
        for (int j = 0; j < dimensions[1]; j++) {
          grille[i][j] = '@';
        }
    }
    int nombre_de_lettres = dimensions[recherche_minimum(dimensions, 2)];
    char* mot;
    Boolean succes = true;
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
    complete_grille(grille, dimensions);
    ma_grille_mot.grille = grille;
    ma_grille_mot.mots = liste_mots;
    ma_grille_mot.nb_mots = index_mots;
    return ma_grille_mot;
}

Boolean placer_mot(char** grille, int* dimensions, char* mot, Boolean* diagonale) {
    int dx = 0;
    int dy = 0;
    int start_x;
    int start_y;
    int x;
    int y;
    int lettres;
    int longueur = strlen(mot);
    for (int i = 0; i < 50; i++) {
        choix_sens_direction(diagonale, &dx, &dy);
        if (dx == 1) {
            x = rand() % (dimensions[0] - longueur + 1);
        } else if (dx == -1) {
            x = rand() % (dimensions[0] - longueur + 1) + (longueur - 1);
        } else {
            x = rand() % dimensions[0];
        }

        if (dy == 1) {
            y = rand() % (dimensions[1] - longueur + 1);
        } else if (dy == -1) {
            y = rand() % (dimensions[1] - longueur + 1) + (longueur - 1);
        } else {
            y = rand() % dimensions[1];
        }
        start_x = x;
        start_y = y;
        lettres = 0;
        while (((x >= 0 && x < dimensions[0]) && (y >= 0 && y < dimensions[1])) && (grille[x][y] == '@' || grille[x][y] == mot[lettres]) && lettres < longueur) {
            x += dx;
            y += dy;
            lettres++;
        }
        if (lettres == longueur) {
            x = start_x;
            y = start_y;
            for (int i = 0; i < longueur; i++) {
                grille[x][y] = mot[i];
                x += dx;
                y += dy;
            }
            return true;
        }
    }
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
    char* mots_7[] = {"REPTILE", "ABRICOT"};
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

void save_score(char* nom_utilisateur, float score) {
    FILE *file;
    file = fopen("save.txt", "a");
    fprintf(file, "%s %.2f\n", nom_utilisateur, score);
    fclose(file);
}

void scores() {
    printf("\033[2J\033[H");
}