#include "memory_allocation.h"

void mac_adress_dynamic_allocation(int nb_circles, MACaddress *tabMAC[]){
  *tabMAC = malloc((nb_circles)*sizeof(MACaddress)) ;
  if(*tabMAC==NULL){
    perror("Memory allocation problem !\n");
    return exit(EXIT_FAILURE);
  }
}

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

void deallocation(int nb_circles, MACaddress *tabMAC[], char ***counters_names){
  int i;
  
  free(*tabMAC);
  for (i=0;i<nb_circles;i++){
    free((*counters_names)[i]);
  }
  free(*counters_names);
}
