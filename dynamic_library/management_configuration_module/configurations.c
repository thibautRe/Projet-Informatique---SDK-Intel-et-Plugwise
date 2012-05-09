/**
 * \file configurations.c
 * \brief This program permits to create, modificate and delete configurations.
 * \author The plugSdk team of Télécom SudParis
 * \version 1.3
 * \date May 9th 2012 
 */
#include <stdio.h>
#include <stdlib.h>             // EXIT_SUCCESS
#include <string.h>             // strcmp

#include "constants.h"

#include "configuration_management.h"
#include "memory_allocation.h"
/**
 * \fn main (void)
 * \brief Configuration creation and deletion. 
 * \return EXIT_SUCCESS status code: ok. 
 * \return EXIT_FAILURE status code: error.
 */
int main (void){ // char *arge[] permet d'utiliser les redirections avec la fonction popen
  /* BOUCLES */
  int i=0;
  
  /* CONFIGURATION */
  int nbConfigurations                = 0;
  ConfigurationName *tabConfigurations = NULL;
  int configurationChoisie            = 0;
  int nb_circles                      = 0;
  char racinePython[ROOT_SIZE]        = "";
  MACaddress *tabMAC                  = NULL;
  char **counters_names               = NULL; // Le nom de chaque compteurs est stocké dans un tableau de chaine de caractères 
  
  /* MENU */
  int choixMenu                       = 0;
  
  printf("Management of the plugwise configurations :\n");
  printf("\n");
  
  // MENU CONFIGURATIONS
  printf("What do you want to do?\n");
  printf("1: Create a new configuration\n");
  printf("2: Delete a configuration\n");
  
  printf("Your choice: ");
  scanf("%d",&choixMenu);
  printf("\n");
  
  if ((choixMenu != 1) && (choixMenu !=2))
    {
      perror("Error : your choice is not possible !\n");
      return EXIT_FAILURE;
    } 
  
  // Because the source code was make for another program
  choixMenu++;
  
  /// CHOIX 1 : CREATION D'UNE NOUVELLE CONFIGURATION :
  if(choixMenu==2)
    {
      allocation_configurations_names(1, &tabConfigurations);
      write_static_data(choixMenu, 1, tabConfigurations, racinePython, &nb_circles);      
      
      mac_adress_dynamic_allocation(nb_circles,&tabMAC);
      counters_names_dynamic_allocation(nb_circles,&counters_names); 
      write_dynamic_data(choixMenu, nb_circles, tabMAC, counters_names);
      
      free(tabConfigurations);
      deallocation(nb_circles, &tabMAC, &counters_names);
    }
  
  /// CHOIX 2 : SUPPRIMER UNE CONFIGURATION :
  else
    { 
      /// 1. On récupère le nombre et les noms des configurations
      nbConfigurations = nb_configurations();
      allocation_configurations_names(nbConfigurations, &tabConfigurations);
      save_configurations_names(nbConfigurations, tabConfigurations);
      
      /// 2. On demande à l'utilisateur de choisir la configuration à supprimer
      configurationChoisie = configuration_choice(choixMenu, nbConfigurations, tabConfigurations);
      
      /// 3. On récupère les données de la configuration
      system("touch configurations.tmp");
      i=1;
      while(i <= nbConfigurations){
	if(i != configurationChoisie){
	  
	  // Récupération des données
	  static_data_recovery(choixMenu, i, tabConfigurations, racinePython,&nb_circles);
	  mac_adress_dynamic_allocation(nb_circles,&tabMAC);
	  counters_names_dynamic_allocation(nb_circles,&counters_names); 
	  dynamic_data_recovery(i, nb_circles, tabMAC, counters_names);
	  
	  // Permutation fichiers
	  system("mv configurations.txt configurations.txt.tmp");
	  system("mv configurations.tmp configurations.txt");
	  
	  // Ecriture des données
	  write_static_data(choixMenu, i, tabConfigurations, racinePython, &nb_circles);      
	  write_dynamic_data(choixMenu, nb_circles, tabMAC, counters_names);
	  
	  system("mv configurations.txt configurations.tmp");
	  system("mv configurations.txt.tmp configurations.txt");
	}
	i++;
      }
      
      /// 4. On libère la mémoire et renomme le fichier temporaire en configurations.txt
      free(tabConfigurations);
      deallocation(nb_circles, &tabMAC, &counters_names);
      system("rm configurations.txt");
      system("mv configurations.tmp configurations.txt");
    } 

  return EXIT_SUCCESS;
}
