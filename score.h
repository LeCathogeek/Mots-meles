//
// Created by etienne on 06/05/2026.
//

#ifndef U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_SCORE_H
#define U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_SCORE_H
#include "jeu.h"

/*
 * Cette procédure permet d'ajouter un nouveau record à la liste des meilleurs scores.
 * -----------------------------------------------------------------------------------
 * nom_utilisateur -> char*, le nom du joueur qui vient de terminer la partie
 * score -> int, le score du joueur
 * return -> void
 */
void save_score(char* nom_utilisateur, float score);

#endif //U_P26_ETIENNE_PACAULT_JEU_DE_LETTRES_SCORE_H
