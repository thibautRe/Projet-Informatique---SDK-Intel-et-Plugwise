#include "allocation_memoire.h"

void allocation_dynamique_adresses_mac(int nb_circles, AdresseMAC *tabMAC[]){
  *tabMAC = malloc((nb_circles)*sizeof(AdresseMAC)) ;
  if(*tabMAC==NULL){
    perror("Problème d'allocation mémoire des adresses MAC !\n");
    return exit(EXIT_FAILURE);
  }
}

void allocation_dynamique_noms_compteurs(int nb_circles, char ***counters_names){
  int i;
  
  *counters_names = calloc(2*nb_circles,sizeof(char*));
  if (*counters_names == NULL){
    perror("Erreur lors du calloc\n");
    return exit(EXIT_FAILURE);
  }
  
  for (i=0 ; i < 2*nb_circles ; i++){
    (*counters_names)[i] = malloc(TAILLE_NOM_COMPTEUR*sizeof(char));
    if ((*counters_names)[i] == NULL){
      perror("Erreur du malloc \n");
      return exit(EXIT_FAILURE);
    }
  }
}

void desallocation(int nb_circles, AdresseMAC *tabMAC[], char ***counters_names){
  int i;
  
  free(*tabMAC);
  for (i=0;i<nb_circles;i++){
    free((*counters_names)[i]);
  }
  free(*counters_names);
}
