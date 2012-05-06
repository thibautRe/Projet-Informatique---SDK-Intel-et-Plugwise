#ifndef _GESTION_CONFIGURATIONS_H
#define _GESTION_CONFIGURATIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "Memory_allocation.h"

int nb_configurations(void);
void allocation_configurations_names(int nbConfigurations, ConfigurationName *tabConfigurations[]);
void save_configurations_names(int nbConfigurations, ConfigurationName tabConfigurations[]);

int configuration_choice(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[]);
int configuration_choice_parsing(int nbConfigurations, char *token, ConfigurationName tabConfigurations[]);

void static_data_recovery(int MenuChoice, int configurationChoisie, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles);

void dynamic_data_recovery(int configurationChosen, int nb_circles, MACadress tabMAC[],char **counters_names);

void configuration_display(int configurationchosen, ConfigurationName tabConfigurations[], char rootPython[], int nb_circles, char ** counters_names, MACadress tabMAC[]);

void write_static_data(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles);
void write_dynamic_data(int MenuChoice, int nb_circles, MACadress tabMAC[], char **counters_names);

#endif
