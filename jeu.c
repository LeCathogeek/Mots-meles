//
// Created by etienne on 29/04/2026.
//
#include "jeu.h"


void controle_d_acquisition() {
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
    int check = sscanf(&choix[0], "%d", &result);
    if (check == 1) {
        if (result == 0) {
            jeu();
        }
        else {
            if (result == 1) {
                scores();
            }
            else {
                printf("Merci d'avoir joue.\nAu revoir !\n");
            }
        }
    }
    else {
        printf("Erreur lors du controle d'acquisition.\n");
    }
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
            if (mot_trouve == false && (da_grille.mots[i] != NULL && strcmp(da_grille.mots[i], mot_devine) == 0)) {
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
    free(mots_trouves_user);
    printf("Voici votre score : %.2f.\n", score);
    printf("Quel est votre nom ? \n");
    fgets(nom_utilisateur, sizeof(nom_utilisateur), stdin);
    save_score(nom_utilisateur, score);
    printf("Merci %s ! Votre nom a ete stocke au milieu de celui des vainqueurs !\n", nom_utilisateur);
    controle_d_acquisition();
}

void scores() {
    printf("\033[2J\033[H");
    printf("Bienvenue ! Ici vous pouvez admirer les noms des meilleurs joueurs !\n");
    FILE *file;
    file = fopen("save.txt", "r");
    fclose(file);
    controle_d_acquisition();
}