#include "configuration_management.h"

int nb_configurations(void){
  
  FILE* configurations    = NULL;
  int nbConfigurations	= 0;
  char buffer[size_buffer];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return EXIT_FAILURE;
  }   
  /** The file configurations.txt has as many rows as configurations.
  * so a line is a configuration and we read it as follows:
   * configuration_name rootSDK rootPython nb_circles MACadress1 MACadress2 etc.
   */
  while (fgets(tampon, size_buffer, configurations) != NULL){
    /** we jump the line :
     * <ul>
     *  <li> corresponding to MAC adress ; </li>
     *  <li> corresponding to the counters names </li>
     * </ul>
     */
    fgets(tampon, size_buffer, configurations);
    fgets(tampon, size_buffer, configurations);
    
    nbConfigurations++;
  }
  
  rewind(configurations); // equivalent to fseek(configurations,0,SEEK_SET)
  fclose(configurations);
  
  if (nbConfigurations <= 1)
    printf("The file contains %d configuration.\n",nbConfigurations);
  else 
    printf("The file contains %d configurations.\n",nbConfigurations);
  
  return nbConfigurations;
}


void allocation_configurations_names(int nbConfigurations, ConfigurationName *tabConfigurations[]){
  *tabConfigurations = malloc(nbConfigurations*sizeof(ConfigurationName));
  if (*tabConfigurations == NULL){
    perror("Error allocating memory for tabConfigurations\n");
    return exit(EXIT_FAILURE);
  }
}


void save_configurations_names(int nbConfigurations, ConfigurationName tabConfigurations[]){
  
  int i                = 0 ;
  FILE* configurations = NULL;
  char buffer[size_buffer];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while (i < nbConfigurations){
    fscanf(configurations,"%s",tabConfigurations[i]);
    fgets(buffer, size_buffer , configurations); // to return to the end of the line
    
    // we jump the two unuseful lines
    fgets(buffer, size_buffer, configurations);
    fgets(buffer, size_buffer, configurations);
    
    i++;
  }
  rewind(configurations);
  fclose(configurations);
}


int configuration_choice(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[]){
  
  int i;
  
  printf("which configuration would you like to use?");
  if(MenuChoice == 1)
    printf("choose ?\n");
  if(MenuChoice == 3)
    printf("remove ?\n");
  
  for (i=0;i<nbConfigurations;i++)
    printf("%d : %s\n",i+1,tabConfigurations[i]);
  printf("Configuration n° : ");
  scanf("%d",&i);
  return i;
}

int configuration_choice_parsing(int nbConfigurations, char *token, ConfigurationName tabConfigurations[]){
  int i=0;
  while ((i<nbConfigurations) && (strcmp(token,tabConfigurations[i])!=0)){
    i++;
  }
  
  if (strcmp(token,tabConfigurations[i])!=0){
    perror("This configuration doesn't exist !\n");
    exit(EXIT_FAILURE);
  }
  
  return i+1;
}

void static_data_recovery(int MenuChoice, int configurationChosen, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles){
  
  int i                = 1 ; // we start reading from the first line
  FILE* configurations = NULL;
  char buffer[size_buffer];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while(i < configurationChoisie){ // to stop at the beguining of the line we want to read
    fgets(buffer, size_buffer, configurations);
    fgets(buffer, size_buffer, configurations); 
    fgets(buffer, size_buffer, configurations);
    i++; 
  }
  
  if(MenuChoice ==2){
    fscanf(configurations,"%s %s %d", tabConfigurations[configurationChoisie-1], rootPython, nb_circles);
  }
  else
    fscanf(configurations,"%s %s %d",buffer,rootPython, nb_circles);
  
  fgets(buffer, size_buffer, configurations);
  
  rewind(configurations);
  fclose(configurations);
}

void dynamic_data_recovery(int configurationChosen, int nb_circles, MACadress tabMAC[],char **counters_names){
  
  int i                = 1 ; // we start reading from the first line
  FILE* configurations = NULL;
  char buffer[size_buffer];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   

  while(i < configurationChoisie){ // to stop at the beguining of the line we want to read
    fgets(buffer, size_buffer, configurations);
    fgets(buffer, size_buffer, configurations); 
    fgets(buffer, size_buffer, configurations);
    i++; 
  }
  
  fgets(buffer, size_buffer, configurations); // we jump the line which corresponds to the dynamic data
  
  // Circles Mac adress
  for (i=0 ; i < nb_circles ; i++){
    fscanf(configurations,"%s ",tabMAC[i]); 
  }
  //  fgets(buffer, size_buffer, configurations); // it goes to line
  
  // counters names
  for (i=0 ; i < nb_circles ; i++){
    fscanf(configurations,"%s ",counters_names[2*i]);
    sprintf(counters_names[2*i+1],"%s.decimals",counters_names[2*i]);
  }
  
  rewind(configurations);
  fclose(configurations);
}


void afficher_configuration(int configurationChoisie, NomConfiguration tabConfigurations[], char racinePython[], int nb_circles, char** counters_names, AdresseMAC tabMAC[]){
  
  int i;  
  
  printf("Here is your configuration :\n");
  printf("Configuration's name: %s\n",tabConfigurations[configurationChoisie-1] );
  printf("Root Python : %s\n",racinePython);
  printf("Number of circles : %d\n",nb_circles);
  printf("Elements that you want to measure power :\n");
  for (i=0 ; i < nb_circles - 1 ; i++)
    printf("  - %s (%s) ;\n", counters_names[2*i], tabMAC[i]);
  printf("  - %s (%s).\n", counters_names[2*i], tabMAC[i]);
}

void write_static_data(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles){
  
  FILE* configurations = NULL;
  
  if (choixMenu == 2){
    printf("How do you want to call your configuration?\n");
    printf("Configuration's name : ");
    scanf("%s",tabConfigurations[nbConfigurations-1]);
    
    printf("What is the path to the application pol.py ?\n");
    printf("Path to pol : ");
    scanf("%s",rootPython);
    
    printf("How many circle (s) has your configuration?\n");
    printf("Number of circle(s) : ");
    scanf("%d",nb_circles);
  }
  
  configurations = fopen("configurations.txt","a");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  fprintf(configurations,"%s %s %d\n",tabConfigurations[nbConfigurations-1],rootPython,*nb_circles);
  
  rewind(configurations);
  fclose(configurations);
}

void write_dynamic_data(int MenuChoice, int nb_circles, MACadress tabMAC[], char **counters_names){
  
  int i                = 0;
  FILE* configurations = NULL;
  
  // Saving names and MAC addresses of circles
  for (i=0 ; i < nb_circles ; i++){
    if (MenuChoice == 2){
      printf(" * Circle's name %d : ",i+1);
      scanf("%s",counters_names[2*i]);
    }
    sprintf(counters_names[2*i+1],"%s.decimals",counters_names[2*i]);
    
    if(choixMenu ==2){
      printf(" * Mac adress is %s : ",counters_names[2*i]);
      scanf("%s",tabMAC[i]);
    }
  } 
  
  // Writing in the file
  configurations = fopen("configurations.txt","a");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  // MAC adress
  for (i=0 ; i < nb_circles ; i++){
    fprintf(configurations,"%s ",tabMAC[i]);
  }
  fprintf(configurations,"\n");
  
  // Counters
  for (i=0 ; i < nb_circles ; i++){
    fprintf(configurations,"%s ",counters_names[2*i]);
  }
  
  rewind(configurations);
  fclose(configurations);
}
