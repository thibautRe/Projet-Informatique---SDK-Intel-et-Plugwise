#ifndef _GESTION_CONFIGURATIONS_H
#define _GESTION_CONFIGURATIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"

int nb_configurations(void);
void allocation_noms_configurations(int nbConfigurations, NomConfiguration *tabConfigurations[]);
void enregistrer_noms_configurations(int nbConfigurations, NomConfiguration tabConfigurations[]);

int choix_configuration(int choixMenu, int nbConfigurations, NomConfiguration tabConfigurations[]);

void recuperation_donnees_statiques(int choixMenu, int configurationChoisie, NomConfiguration tabConfigurations[], char racinePython[], int *nb_circles);

void allocation_dynamique_adresses_mac(int nb_circles, AdresseMAC *tabMAC[]);
void allocation_dynamique_noms_compteurs(int nb_circles, char ***counters_names);

void recuperation_donnees_dynamiques(int configurationChoisie, int nb_circles, AdresseMAC tabMAC[],char **counters_names);

void afficher_configuration(int configurationChoisie, NomConfiguration tabConfigurations[], char racinePython[], int nb_circles, char ** counters_names, AdresseMAC tabMAC[]);

void desallocation(int nb_circles, NomConfiguration *tabConfigurations[], AdresseMAC *tabMAC[], char ***counters_names);

void ecrire_donnees_statiques(int choixMenu, int nbConfigurations, NomConfiguration tabConfigurations[], char racinePython[], int *nb_circles);
void ecrire_donnees_dynamiques(int choixMenu, int nb_circles, AdresseMAC tabMAC[], char **counters_names);

#endif
