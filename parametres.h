//
// Created by etienne on 06/05/2026.
//

#ifndef U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_PARAMETRES_H
#define U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_PARAMETRES_H
#include "jeu.h"
/*
 * Cette procédure permet de configurer le jeu pour l'utilisateur.
 * (Taille de la grille, diagonale, temps...)
 * ----------------------------------------------------------------
 * dimensions -> int *, tableau d'entiers contenant les dimensions de la grille
 * diagonale -> Boolean*, un pointeur vers un booléen informant sur le placement de mots en diagonale
 * time -> int *, un pointeur vers l'entier contenant le temps de la partie
 * return -> void
 */
void parametres(int* dimensions, Boolean* diagonale, int* time);

/*
 * Cette procédure permet de demander au joueur les dimensions de la grille
 * de mots mêlés qu'il désire.
 * -----------------------------------------------------------------------
 * dimensions -> int *, tableau d'entiers contenant les dimensions de la grille
 * return -> void
 */
void get_dimensions(int* dimensions);

/*
 * Cette procédure permet avec un controle d'acquisition de demander à l'utilisateur
 * s'il veut jouer avec des mots en diagonale.
 * ----------------------------------------------------------------------------------
 * diagonale -> Boolean*, le booléen informant de l'activation de la règle du jeu des mots en diagonale
 * return -> void
 */
void get_diagonale(Boolean* diagonale);

/*
 * Cette procédure permet avec un contrôle d'acquisition de demander à l'utilisateur le temps de sa partie.
 * ----------------------------------------------------------------------------------------------------------
 * time -> int *, un pointeur vers la variable contenant le temps de jeu désiré par le joueur
 * return -> void
 */
void get_time(int* time);
#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_PARAMETRES_H
