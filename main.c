//Crée le mercredi 29 avril 2026 par Étienne Pacault

#include "caisse_a_outils.h"

//Section programme principal
int main(void) {
    printf("Bonjour et bienvenue dans notre super jeu de mots meles !\n");
    int choix = controle_d_acquisition();
    if (choix == 0) {
        jeu();
    }
    else {
        if (choix == 1) {
            scores();
        }
        else {
            if (choix == 2) {
                printf("Bon tant pis. A la prochaine fois !");
                return 0;
            }
        }
    }
    return 0;
}