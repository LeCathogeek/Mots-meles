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
#include <math.h>

typedef enum {false=0, true=1} Boolean;

typedef enum {horizontal=0, vertical=1, diagonal=2} Direction;

typedef enum {endroit=0, envers=1} Sens;

typedef struct {
  Direction direction;
  Sens sens;
} SensDirection;

typedef struct {
  char** grille;
  char** mots;
  int nb_mots;
}grille_mots;

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
 * Cette fonction permet de générer une grille de mots prête à l'emploi pour jouer.
 * --------------------------------------------------------------------------------
 * dimensions -> int *, un tableau d'entiers contenant les dimensions de la grille
 * diagonale -> Boolean, un booléen qui nous dit si le joueur veut des mots en diagonale
 * return -> char**, un tableau de caractères à deux dimensions.
 */
grille_mots generation_grille(int* dimensions, Boolean diagonale);

/*
 * Cette fonction permet d'essayer de placer un mot dans la grille.
 * ----------------------------------------------------------------
 * grille -> char**, notre grille de mots mêlés
 * dimensions -> int*, notre tableau donnant les dimensions de notre grille.
 * mot -> char*, le mot que l'on essaie de placer dans la grille
 * diagonale -> Boolean*, si on souhaite que des mots apparaissent en diagonale
 * return -> Boolean, si la fonction a réussi à placer le mot.
 */
Boolean placer_mot(char** grille, int* dimensions, char* mot, Boolean* diagonale);

/*
 * Cette fonction permet de générer un SensDirection indiquant
 * dans quel sens et dans quelle direction un mot sera généré.
 * ------------------------------------------------------------
 * diagonale_autorise -> Boolean*, booléen indiquant si les mots peuvent être placés en diagonale
 * dx -> int*, le déplacement en x
 * dy -> int*, le déplacement en y
 * return -> void
 */
void choix_sens_direction(Boolean* diagonale_autorise, int* dx, int* dy);

/*
 * Cette fonction permet de renvoyer l'indice de la plus petite valeur d'un tableau d'entiers.
 * -------------------------------------------------------------------------------------------
 * tableau -> int*, un tableau d'entiers
 * size -> int, la taille du tableau
 * return -> int
 */
int recherche_minimum(int* tableau, int size);

/*
 * Cette procédure permet de remplir une grille de mots mêlés où il reste des
 * cases qui n'ont pas pu être complétées.
 * ----------------------------------------------------------------------------
 * grille -> char**, un tableau de lettres à deux dimensions, la grille du jeu
 * return -> void
 */
void complete_grille(char** grille, int* dimensions);

/*
 * Cette procédure permet d'afficher une grille de mots mêlés.
 * -----------------------------------------------------------
 * grille -> char**, le tableau à deux dimensions contenant les lettres du jeu
 * dimensions -> int*, les dimensions de la grille
 * return -> void
 */
void affichage_grille(char** grille, int* dimensions);

/*
 * Cette fonction permet de tirer au hasard un mot de la longueur désirée.
 * -----------------------------------------------------------------------
 * longueur -> int, la longueur du mot souhaité
 * return -> char*, le mot souhaité
 */
char* tirer_mot(int longueur);

/*
 * Cette procédure permet d'ajouter un nouveau record à la liste des meilleurs scores.
 * -----------------------------------------------------------------------------------
 * nom_utilisateur -> char*, le nom du joueur qui vient de terminer la partie
 * score -> int, le score du joueur
 * return -> void
 */
void save_score(char* nom_utilisateur, float score);

/*
 * Cette procédure permet d'afficher les meilleurs scores.
 * -------------------------------------------------------
 * return -> void
 */
void scores();

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_CAISSE_A_OUTILS_H
