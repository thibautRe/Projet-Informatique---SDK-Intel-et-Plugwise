#ifndef _FONCTIONS_H
#define _FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

#include "allocation_memoire.h"

#define DEBUG_MODE

#define ADRESSE_MAC_CIRCLE1     "000D6F0000998BF3"
#define ADRESSE_MAC_CIRCLE2     "000D6F000098??F2"

#define PUISSANCE_MAX 100
typedef char adresseMAC[TAILLE_ADRESSE_MAC];
#include "constantes.h"

void initialiser_chemin_sdk(char racineSDK[]);
void initialiser_chemin_python(char racinePyhon[]);
void initialiser_plugwise(char racinePython[],int *nb_circles,AdresseMAC *tabMAC[], char **counters_names[]);
void lancement_interface_graphique_sdk(char racineSDK[], char strUUID[], int *architecture, int *pid_pl_gui_monitor);
void lancement_pl_csv_logger_sdk(char racineSDK[], char strUUID[], int *pid_pl_csv_logger);
double mesure_watt(char *commande);
void commande_python(int i, char racinePython[], AdresseMAC tabMAC[],char commande[]);
int recuperer_pid(char processus[]);
#endif
