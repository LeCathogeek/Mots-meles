//
// Created by etienne on 06/05/2026.
//
#include "score.h"

void save_score(char* nom_utilisateur, float score) {
    FILE *file;
    file = fopen("save.txt", "a");
    fprintf(file, "%s %.2f\n", nom_utilisateur, score);
    fclose(file);
}