#ifndef _ALLOCATION_MEMOIRE_H
#define _ALLOCATION_MEMOIRE_H

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

void mac_adress_dynamic_allocation(int nb_circles, MACaddress *tabMAC[]);
void counters_names_dynamic_allocation(int nb_circles, char ***counters_names);
void deallocation(int nb_circles, MACaddress *tabMAC[], char ***counters_names);

#endif
