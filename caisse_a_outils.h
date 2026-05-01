//
// Created by etienne on 29/04/2026.
//

#ifndef U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_CAISSE_A_OUTILS_H
#define U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_CAISSE_A_OUTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef enum {false=0, true=1} Boolean;

/*
 * Cette fonction permet d'effectuer le contrôle d'acquisition au début du jeu
 * afin de savoir si l'utilisateur veut jouer, regarder les meilleurs scores ou quitter le jeu.
 * --------------------------------------------------------------------------------------------
 * return -> int, 0 si le joueur veut jouer, 1 s'il veut regarder les scores, 2 s'il veut quitter
 */
int controle_d_acquisition();

/*
 * Cette procédure permet de lancer le jeu.
 * -----------------------------------------
 * return -> void
 */
void jeu();

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

/*
 * Cette procédure permet d'afficher les meilleurs scores.
 * -------------------------------------------------------
 * return -> void
 */
void scores();

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_CAISSE_A_OUTILS_H
