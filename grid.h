//
// Created by etienne on 06/05/2026.
//

#ifndef U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_GRID_H
#define U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_GRID_H
#include "jeu.h"

/**
 * Cette fonction permet de générer une grille de mots prête à l'emploi pour jouer.
 * --------------------------------------------------------------------------------
 * @param dimensions -> int *, un tableau d'entiers contenant les dimensions de la grille
 * @param diagonale -> Boolean, un booléen qui nous dit si le joueur veut des mots en diagonale
 * @return -> char**, un tableau de caractères à deux dimensions.
 */
grille_mots generation_grille(int* dimensions, Boolean diagonale);

/**
 * Cette fonction permet d'essayer de placer un mot dans la grille.
 * ----------------------------------------------------------------
 * @param grille -> char**, notre grille de mots mêlés
 * @param dimensions -> int*, notre tableau donnant les dimensions de notre grille.
 * @param mot -> char*, le mot que l'on essaie de placer dans la grille
 * @param diagonale -> Boolean*, si on souhaite que des mots apparaissent en diagonale
 * @return -> Boolean, si la fonction a réussi à placer le mot.
 */
Boolean placer_mot(char** grille, int* dimensions, char* mot, Boolean* diagonale);

/**
 * Cette fonction permet de générer un SensDirection indiquant
 * dans quel sens et dans quelle direction un mot sera généré.
 * ------------------------------------------------------------
 * @param diagonale_autorise -> Boolean*, booléen indiquant si les mots peuvent être placés en diagonale
 * @param dx -> int*, le déplacement en x
 * @param dy -> int*, le déplacement en y
 * @return -> void
 */
void choix_sens_direction(Boolean* diagonale_autorise, int* dx, int* dy);

/**
 * Cette fonction permet de renvoyer l'indice de la plus petite valeur d'un tableau d'entiers.
 * -------------------------------------------------------------------------------------------
 * @param tableau -> int*, un tableau d'entiers
 * @param size -> int, la taille du tableau
 * @return -> int
 */
int recherche_minimum(int* tableau, int size);

/**
 * Cette procédure permet de remplir une grille de mots mêlés où il reste des
 * cases qui n'ont pas pu être complétées.
 * ----------------------------------------------------------------------------
 * @param grille -> char**, un tableau de lettres à deux dimensions, la grille du jeu
 * @return -> void
 */
void complete_grille(char** grille, int* dimensions);

/**
 * Cette procédure permet d'afficher une grille de mots mêlés.
 * -----------------------------------------------------------
 * @param grille -> char**, le tableau à deux dimensions contenant les lettres du jeu
 * @param dimensions -> int*, les dimensions de la grille
 * @return -> void
 */
void affichage_grille(char** grille, int* dimensions);

/**
 * Cette fonction permet de tirer au hasard un mot de la longueur désirée.
 * -----------------------------------------------------------------------
 * @param longueur -> int, la longueur du mot souhaité
 * @return -> char*, le mot souhaité
 */
char* tirer_mot(int longueur);

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_GRID_H
