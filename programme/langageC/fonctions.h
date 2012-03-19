#ifndef _HEADER_POH_H
#define _HEADER_POH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TAMPON (10+1)
#define TAILLE_RACINE (256+1)
#define TAILLE_ADRESSE_MAC (16+1)
#define TAILLE_COMMANDE (400+1)
#define TAILLE_NOM_COMPTEUR (20+1)

typedef char adresseMAC[TAILLE_ADRESSE_MAC];

void initialiser_chemin_sdk(char racineSDK[]);
void initialiser_chemin_python(char racinePyhon[]);
void initialiser_plugwise(char racinePython[],int *nb_circle,adresseMAC *tabMAC[]);
void lancement_interface_graphique_sdk(char commande[], char racineSDK[], int *architecture);
unsigned long long mesure_watt(int i, char *commande);
void commande_python(int i, char racinePython[], adresseMAC tabMAC[],char commande[]);

#endif