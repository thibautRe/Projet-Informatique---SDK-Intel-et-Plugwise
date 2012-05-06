#ifndef _ALLOCATION_MEMOIRE_H
#define _ALLOCATION_MEMOIRE_H

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"

void allocation_dynamique_adresses_mac(int nb_circles, AdresseMAC *tabMAC[]);
void allocation_dynamique_noms_compteurs(int nb_circles, char ***counters_names);
void desallocation(int nb_circles, AdresseMAC *tabMAC[], char ***counters_names);

#endif
