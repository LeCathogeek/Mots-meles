//Crée le mercredi 29 avril 2026 par Étienne Pacault

#include "jeu.h"

//Section programme principal
int main(void) {
    //Initialisation des nombres aléatoires
    srand(time(0));
    printf("Bonjour et bienvenue dans notre super jeu de mots meles !\n");
    controle_d_acquisition();
    return 0;
}