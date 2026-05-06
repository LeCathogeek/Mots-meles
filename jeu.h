//
// Created by etienne on 29/04/2026.
//

#ifndef U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_JEU_H
#define U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_JEU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "parametres.h"
#include "grid.h"
#include "score.h"

/**
 * Cette fonction permet d'effectuer le contrôle d'acquisition au début du jeu
 * afin de savoir si l'utilisateur veut jouer, regarder les meilleurs scores ou quitter le jeu.
 * --------------------------------------------------------------------------------------------
 * @return -> void
 */
void controle_d_acquisition();

/**
 * Cette procédure permet de lancer le jeu.
 * -----------------------------------------
 * @return -> void
 */
void jeu();

/**
 * Cette procédure permet d'afficher les meilleurs scores.
 * -------------------------------------------------------
 * @return -> void
 */
void scores();

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_JEU_H
