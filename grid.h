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
 * @param dico -> Dictionnaire* un pointeur vers notre dictionnaire
 * @param liste_mots_pos -> Mot**, un pointeur vers une liste de Mot contenant les mots de la grille et leurs positions
 * @return -> char**, un tableau de caractères à deux dimensions.
 */
grille_mots generation_grille(int* dimensions, Boolean diagonale, Dictionnaire* dico, Mot** liste_mots_pos);

/**
 * Cette fonction permet d'essayer de placer un mot dans la grille.
 * ----------------------------------------------------------------
 * @param grille -> char**, notre grille de mots mêlés
 * @param dimensions -> int*, notre tableau donnant les dimensions de notre grille.
 * @param mot -> char*, le mot que l'on essaie de placer dans la grille
 * @param diagonale -> Boolean*, si on souhaite que des mots apparaissent en diagonale
 * @param liste_mots -> Mot**, un pointeur vers un ensemble de mots qui contient les différents mots placés dans la grille et leur position
 * @param index_mots -> int, le nombre de mots déjà placés dans la grille
 * @return -> Boolean, si la fonction a réussi à placer le mot.
 */
Boolean placer_mot(char** grille, int* dimensions, char* mot, Boolean* diagonale, Mot** liste_mots, int index_mots);

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
 * Cette fonction permet de générer le dictionnaire qui contient tous les mots possibles
 * à partir du fichier dictionnaire.txt.
 * ----------------------------------------------------------------------------------------
 * @return -> Dictionnaire*
 */
Dictionnaire* charger_dictionnaire();

/**
 * Cette fonction permet de scanner le dictionnaire passé en paramètre
 * et de retourner un mot au hasard de la longueur souhaitée.
 * ---------------------------------------------------------------------
 * @param dico -> Dictionnaire*, un pointeur vers notre dicitonnaire
 * @param longueur -> int, la longueur du mot souhaité
 * @return -> char*, un mot de la longueur souhaitée.
 */
char* tirer_mot_du_dico(Dictionnaire* dico, int longueur);

/**
 * Cette procédure permet de libérer l'espace mémoire associé au dictionnaire.
 * ---------------------------------------------------------------------------
 * @param dico -> Dictionnaire*, un pointeur vers notre dictionnaire.
 * @return -> void
 */
void liberer_dico(Dictionnaire* dico);

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_GRID_H
