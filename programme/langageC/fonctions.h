#ifndef _FONCTIONS_H
#define _FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

#include "constantes.h"

void initialiser_chemin_sdk(char racineSDK[]);
void initialiser_chemin_python(char racinePyhon[]);
void initialiser_plugwise(char racinePython[],int *nb_circle,adresseMAC *tabMAC[]);
void lancement_interface_graphique_sdk(char racineSDK[], char strUUID[], int *architecture);
void lancement_pl_csv_logger_sdk(char racineSDK[], char strUUID[]);
double mesure_watt(char *commande);
void commande_python(int i, char racinePython[], adresseMAC tabMAC[],char commande[]);

#endif
