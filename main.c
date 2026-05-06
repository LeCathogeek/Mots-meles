//Crée le mercredi 29 avril 2026 par Étienne Pacault

#include "jeu.h"

//Section programme principal
int main(void) {
    //Initialisation des nombres aléatoires
    srand(time(0));
    int dimensions[2] = {6, 8};
    printf("Bonjour et bienvenue dans notre super jeu de mots meles !\n");
    affichage_grille(generation_grille(dimensions, true).grille, dimensions);
    return 0;
}