/**
 * \file memory_allocation.c
 * \brief These functions permits to (de)allocate memory.
 *
 * \author The PlugSdk team of Télécom SudParis
 * \version 0.2
 * \date May 9th 2012
 */
#include "memory_allocation.h"

/**
 * \fn mac_adress_dynamic_allocation(int nb_circles, MACaddress *tabMAC[]){
 * 
 * \brief Dynamic allocation of the MAC addresses table.
 *
 * \param[in] int number of circles
 * \param[in,out] MACaddress table of MAC addresses
 */
void mac_adress_dynamic_allocation(int nb_circles, MACaddress *tabMAC[]){
  *tabMAC = malloc((nb_circles)*sizeof(MACaddress)) ;
  if(*tabMAC==NULL){
    perror("Memory allocation problem !\n");
    return exit(EXIT_FAILURE);
  }
}

/**
 * \fn counters_names_dynamic_allocation(int nb_circles, char ***counters_names)
 * 
 * \brief Dynamic allocation of the counters names table
 *
 * \param[in] int number of circles
 * \param[in,out] char*** Pointer to a table of counters names
 */
void counters_names_dynamic_allocation(int nb_circles, char ***counters_names){
  int i;
  
  *counters_names = calloc(2*nb_circles,sizeof(char*));
  if (*counters_names == NULL){
    perror("Error Calloc\n");
    return exit(EXIT_FAILURE);
  }
  
  for (i=0 ; i < 2*nb_circles ; i++){
    (*counters_names)[i] = malloc(COUNTER_NAME_SIZE*sizeof(char));
    if ((*counters_names)[i] == NULL){
      perror("Erreur du malloc \n");
      return exit(EXIT_FAILURE);
    }
  }
}

/**
 * \fn deallocation(int nb_circles, MACaddress *tabMAC[], char ***counters_names){
 * 
 * \brief Deallocation of the memory used by the table of MAC addresses and by the 
 * table of counters names.
 *
 * \param[in] int number of circles
 * \param[in,out] MACaddress table of MAC addresses
 * \param[in,out] char*** Pointer to a table of counters names
 */
void deallocation(int nb_circles, MACaddress *tabMAC[], char ***counters_names){
  int i;
  
  free(*tabMAC);
  for (i=0;i<nb_circles;i++){
    free((*counters_names)[i]);
  }
  free(*counters_names);
}
