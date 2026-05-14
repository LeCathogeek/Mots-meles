//
// Created by etienne on 29/04/2026.
//
#include "jeu.h"


void controle_d_acquisition() {
    //Initialisation des variables nécessaires
    char choix[10];
    int result = 0;
    Joueur* les_joueurs[100];
    //Boucle do pour demander à l'utilisateur
    do {
        printf("Que voulez-vous faire ? (entrez comme réponse l'entier correspondant)\n  - Demarrer une partie (0)\n  - Afficher les meilleurs scores (1)\n  - Quitter (2)\n");
        fgets(choix, sizeof(choix),  stdin);
        if (choix[0] != '0' && choix[0] != '1' && choix[0] != '2') {
            printf("Attention ! Votre reponse est incorrecte !\nDonnez un entier situe entre 0 et 2 indiquant votre reponse.\n");
        }
    } while (choix[0] != '0' && choix[0] != '1' && choix[0] != '2');
    //Transformation de la réponse de l'utilisateur en int et démarrage de la partie ou affichage des scores selon son choix
    int check = sscanf(&choix[0], "%d", &result);
    if (check == 1) {
        if (result == 0) {
            jeu();
        }
        else {
            if (result == 1) {
                scores(*les_joueurs);
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
    //Effacement de la sortie
    printf("\033[2J\033[H");
    Dictionnaire* dico = charger_dictionnaire();
    //Variables pour les paramètres
    int dimensions[2] = {8, 8};
    Boolean diagonale = false;
    int temps;
    Mot* liste_mots_pos = (Mot*) malloc(sizeof(Mot) * 1);
    //Variables pour la fin de la partie
    float score = 0;
    char* nom_utilisateur;

    //Saisie des paramètres par le joueur
    parametres(dimensions, &diagonale, &temps);

    //Génération de la grille
    grille_mots da_grille = generation_grille(dimensions, diagonale, dico, liste_mots_pos);
    affichage_grille(da_grille.grille, dimensions);
    printf("Nombre de mots : %d\n", da_grille.nb_mots);

    //Gestion du temps
    time_t debut = time(0);
    time_t maintenant = time(0);

    //Variables pour le jeu
    char mot_devine[18];
    Boolean mot_trouve = false;
    int nb_mots_trouves = 0;
    char** mots_trouves_user = (char**) malloc(sizeof(char*) * da_grille.nb_mots);

    //Boucle de jeu
    while ((int)(maintenant - debut) < temps && nb_mots_trouves < da_grille.nb_mots) {
        maintenant = time(0);
        //Lecture de l'entrée utilisateur
        printf("C'est parti ! Entrez un mot : \n");
        fgets(mot_devine, sizeof(mot_devine), stdin);
        int j = 0;
        char ch;
        char tmp[18];
        while (mot_devine[j]) {
            ch = mot_devine[j];
            tmp[j] = toupper(ch);
            j++;
        }
        strcpy(mot_devine, tmp);
        mot_devine[strcspn(mot_devine, "\n")] = '\0'; //On remplace la première occurence de retour à la ligne par une fin de string

        //On vérifie si le mot entré est dans la grille
        int i = 0;
        mot_trouve = false;
        while (i < da_grille.nb_mots && mot_trouve == false) {
            if (da_grille.mots[i] != NULL && strcmp(da_grille.mots[i], mot_devine) == 0) {
                mot_trouve = true;
                nb_mots_trouves++;
                mots_trouves_user[nb_mots_trouves - 1] = da_grille.mots[i];
                da_grille.mots[i] = NULL;
            }
            i++;
        }
        if (mot_trouve) {
            printf("Felicitations ! Vous avez trouve le mot %s.\n", mot_devine);
        }
        else {
            printf("Mot incorrect ou déjà trouve !\n");
        }
        affichage_grille(da_grille.grille, dimensions);
    }
    printf("La partie est terminée !\n");
    if (nb_mots_trouves == da_grille.nb_mots) {
        printf("Tous les mots generes dans la grille ont ete trouves.\nC'est fantastique !\n");
    }

    //Libération des tableaux mallocés
    for (int i = 0; i < dimensions[0]; i++) {
        free(da_grille.grille[i]);
    }
    free(da_grille.grille);
    free(da_grille.mots);
    free(liste_mots_pos);
    //Calcul du score
    for (int i = 0; i < nb_mots_trouves ;i++) {
        score += pow(strlen(mots_trouves_user[i]), 4.0/3.0);
    }
    free(mots_trouves_user);
    printf("Voici votre score : %.2f.\n", score);

    //Enregistrement du score avec le nom d'utilisateur
    printf("Quel est votre nom ? \n");
    fgets(nom_utilisateur, sizeof(nom_utilisateur), stdin);
    save_score(nom_utilisateur, score);
    printf("Merci %s ! Votre nom a ete stocke au milieu de celui des vainqueurs !\n", nom_utilisateur);
    liberer_dico(dico);
    //Menu principal
    controle_d_acquisition();
}

void scores(Joueur* les_joueurs) {
    printf("\033[2J\033[H");
    printf("Bienvenue ! Ici vous pouvez admirer les noms des meilleurs joueurs !\n");
    FILE *file;
    file = fopen("save.txt", "r");
    fclose(file);
    controle_d_acquisition();
}