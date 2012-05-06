#include "gestion_configurations.h"

int nb_configurations(void){
  
  FILE* configurations    = NULL;
  int nbConfigurations	= 0;
  char tampon[TAILLE_TAMPON];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Erreur lors de l'ouverture du fichier configurations.txt\n");
    return EXIT_FAILURE;
  }   
  /** Le fichier configurations.txt comporte autant de lignes que de configurations.
   * Ainsi une ligne constitue une configuration ; elle se lit de la manière suivante :
   * nom_configuration racineSDK racinePython nb_circles adresseMAC1 adresseMAC2 etc.
   */
  while (fgets(tampon, TAILLE_TAMPON, configurations) != NULL){
    /** On saute la ligne :
     * <ul>
     *  <li> correspondante aux adresses MAC ; </li>
     *  <li> correspondante aux noms des compteurs. </li>
     * </ul>
     */
    fgets(tampon, TAILLE_TAMPON, configurations);
    fgets(tampon, TAILLE_TAMPON, configurations);
    
    nbConfigurations++;
  }
  
  rewind(configurations); // équivalent à fseek(configurations,0,SEEK_SET)
  fclose(configurations);
  
  if (nbConfigurations <= 1)
    printf("Le fichier comporte %d configuration.\n",nbConfigurations);
  else 
    printf("Le fichier comporte %d configurations.\n",nbConfigurations);
  
  return nbConfigurations;
}


void allocation_noms_configurations(int nbConfigurations, NomConfiguration *tabConfigurations[]){
  *tabConfigurations = malloc(nbConfigurations*sizeof(NomConfiguration));
  if (*tabConfigurations == NULL){
    perror("Erreur d'allocation mémoire pour tabConfigurations\n");
    return exit(EXIT_FAILURE);
  }
}


void enregistrer_noms_configurations(int nbConfigurations, NomConfiguration tabConfigurations[]){
  
  int i                = 0 ;
  FILE* configurations = NULL;
  char tampon[TAILLE_TAMPON];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Erreur lors de l'ouverture du fichier configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while (i < nbConfigurations){
    fscanf(configurations,"%s",tabConfigurations[i]);
    fgets(tampon, TAILLE_TAMPON, configurations); // pour retourner à la fin de la ligne
    
    // On saute les deux lignes inutiles
    fgets(tampon, TAILLE_TAMPON, configurations);
    fgets(tampon, TAILLE_TAMPON, configurations);
    
    i++;
  }
  rewind(configurations);
  fclose(configurations);
}


int choix_configuration(int choixMenu, int nbConfigurations, NomConfiguration tabConfigurations[]){
  
  int i;
  
  printf("Quelle configuration souhaitez-vous");
  if(choixMenu == 1)
    printf("choisir ?\n");
  if(choixMenu == 3)
    printf("supprimer ?\n");
  
  for (i=0;i<nbConfigurations;i++)
    printf("%d : %s\n",i+1,tabConfigurations[i]);
  printf("Configuration n° : ");
  scanf("%d",&i);
  return i;
}



void recuperation_donnees_statiques(int choixMenu, int configurationChoisie, NomConfiguration tabConfigurations[], char racinePython[], int *nb_circles){
  
  int i                = 1 ; // On commence à lire dès la première ligne
  FILE* configurations = NULL;
  char tampon[TAILLE_TAMPON];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Erreur lors de l'ouverture du fichier configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while(i < configurationChoisie){ // pour s'arrêter juste avant la ligne à lire
    fgets(tampon, TAILLE_TAMPON, configurations);
    fgets(tampon, TAILLE_TAMPON, configurations);
    fgets(tampon, TAILLE_TAMPON, configurations);
    i++; 
  }
  
  if(choixMenu ==2){
    fscanf(configurations,"%s %s %d", tabConfigurations[configurationChoisie-1], racinePython, nb_circles);
  }
  else
    fscanf(configurations,"%s %s %d",tampon,racinePython, nb_circles);
  
  fgets(tampon, TAILLE_TAMPON, configurations);

  rewind(configurations);
  fclose(configurations);
}

void recuperation_donnees_dynamiques(int configurationChoisie, int nb_circles, AdresseMAC tabMAC[],char **counters_names){
  
  int i                = 1 ; // On commence à lire dès la première ligne
  FILE* configurations = NULL;
  char tampon[TAILLE_TAMPON];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Erreur lors de l'ouverture du fichier configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   

  while(i < configurationChoisie){ // pour s'arrêter juste avant la ligne à lire
    fgets(tampon, TAILLE_TAMPON, configurations);
    fgets(tampon, TAILLE_TAMPON, configurations);
    fgets(tampon, TAILLE_TAMPON, configurations);
    i++; 
  }
  
  fgets(tampon, TAILLE_TAMPON, configurations); // On saute la ligne correspondante aux données statiques
  
  // adresse(s) MAC des circle
  for (i=0 ; i < nb_circles ; i++){
    fscanf(configurations,"%s ",tabMAC[i]); 
  }
  //  fgets(tampon, TAILLE_TAMPON, configurations); // on va à la ligne
  
  // noms des compteurs
  for (i=0 ; i < nb_circles ; i++){
    fscanf(configurations,"%s ",counters_names[2*i]);
    sprintf(counters_names[2*i+1],"%s.decimals",counters_names[2*i]);
  }
  
  rewind(configurations);
  fclose(configurations);
}


void afficher_configuration(int configurationChoisie, NomConfiguration tabConfigurations[], char racinePython[], int nb_circles, char** counters_names, AdresseMAC tabMAC[]){
  
  int i;  
  
  printf("Voici votre configuration :\n");
  printf("Nom configuration : %s\n",tabConfigurations[configurationChoisie-1] );
  printf("Racine Python : %s\n",racinePython);
  printf("Nombre de circles : %d\n",nb_circles);
  printf("Elements dont vous souhaitez mesurer la puissance :\n");
  for (i=0 ; i < nb_circles - 1 ; i++)
    printf("  - %s (%s) ;\n", counters_names[2*i], tabMAC[i]);
  printf("  - %s (%s).\n", counters_names[2*i], tabMAC[i]);
}

void ecrire_donnees_statiques(int choixMenu, int nbConfigurations, NomConfiguration tabConfigurations[], char racinePython[], int *nb_circles){
  
  FILE* configurations = NULL;
  
  if (choixMenu == 2){
    printf("Comment voulez-vous appeler votre configuration ?\n");
    printf("Nom configuration : ");
    scanf("%s",tabConfigurations[nbConfigurations-1]);
    
    printf("Quel est le chemin menant à l'application pol.py ?\n");
    printf("Chemin pol : ");
    scanf("%s",racinePython);
    
    printf("Combien de circle(s) comporte votre configuration ?\n");
    printf("Nombre de circle(s) : ");
    scanf("%d",nb_circles);
  }
  
  configurations = fopen("configurations.txt","a");
  if (configurations == NULL){
    perror("Erreur lors de l'ouverture du fichier configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  fprintf(configurations,"%s %s %d\n",tabConfigurations[nbConfigurations-1],racinePython,*nb_circles);
  
  rewind(configurations);
  fclose(configurations);
}

void ecrire_donnees_dynamiques(int choixMenu, int nb_circles, AdresseMAC tabMAC[], char **counters_names){
  
  int i                = 0;
  FILE* configurations = NULL;
  
  // Enregistrement des noms et des adresses MAC des circles
  for (i=0 ; i < nb_circles ; i++){
    if (choixMenu == 2){
      printf(" * Nom du circle %d : ",i+1);
      scanf("%s",counters_names[2*i]);
    }
    sprintf(counters_names[2*i+1],"%s.decimals",counters_names[2*i]);
    
    if(choixMenu ==2){
      printf(" * Adresse MAC de %s : ",counters_names[2*i]);
      scanf("%s",tabMAC[i]);
    }
  } 
  
  // Ecriture dans le fichier
  configurations = fopen("configurations.txt","a");
  if (configurations == NULL){
    perror("Erreur lors de l'ouverture du fichier configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  // Adresses MAC
  for (i=0 ; i < nb_circles ; i++){
    fprintf(configurations,"%s ",tabMAC[i]);
  }
  fprintf(configurations,"\n");
  
  // Compteurs
  for (i=0 ; i < nb_circles ; i++){
    fprintf(configurations,"%s ",counters_names[2*i]);
  }
  
  rewind(configurations);
  fclose(configurations);
}
