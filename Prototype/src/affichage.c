#include "affichage.h"

#include <stdio.h>       // printf
#include <stdlib.h> // system

/**
 * \file    affichage.c
 * \brief   Ce fichier crée les méthodes d'affichage du fichier affichage.h
 * \author  Thibaut REMY
 * \date    20 / 03 / 2012
 */

void effacerEcran(void){
  system("clear");
}

void afficherDebutProgramme()
{
    printf("#**************************************#\n");
    printf("#*                                    *#\n");
    printf("#*       LANCEMENT DU PROGRAMME       *#\n");
    printf("#*             D'ANALYSE              *#\n");
    printf("#*   DE LA CONSOMMATION ENERGETIQUE   *#\n");
    printf("#*                                    *#\n");
    printf("#**************************************#\n");
    printf("\n");
    printf("Le programme est en cours de lancement...\n");
}

void afficherDebugMode()
{
    printf("*************************************\n");
    printf("*                                   *\n");
    printf("*         LANCEMENT DU MODE         *\n");
    printf("*               DEBUG               *\n");
    printf("*                                   *\n");
    printf("*************************************\n");
}
