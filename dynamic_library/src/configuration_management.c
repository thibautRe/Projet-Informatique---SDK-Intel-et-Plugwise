/**
 * \file configuration_management.c
 * \brief These functions permits to read and write plugwise configurations.
 * They are used by the plugwise ersv driver (library) and also by another program
 * (which was an alternative of the esrv dynamic library).
 *
 * \author The PlugSdk team of Télécom SudParis
 * \version 0.2
 * \date May 9th 2012
 * 
 * Configurations are saved in the file configurations.txt. <br />
 * Each configuration follow this model: <br />
 * line n: configuration_name /POL_ROOT circles_number <br />
 * line n+1: MACaddress1 MACaddress2 etc. <br />
 * line n+1: CircleName1 CircleName2 etc.
 * 
 */
#include "configuration_management.h"

/** 
 * \fn nb_configurations(void)
 * \brief It calculates the number of different configurations in the file configurations.txt.
 *
 * \return int the number of configurations
 */
int nb_configurations(void){
  
  FILE* configurations    = NULL;
  int nbConfigurations	= 0;
  char buffer[BUFFER_SIZE];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return EXIT_FAILURE;
  }  
  
  /** Each configuration are written on three lines.
   * We read it as follows:<br />
   * line n : configuration_name /POL_ROOT circles_number <br />
   * line n+1 : MACaddress1 MACaddress2 etc. <br />
   * line n+1 : CircleName1 CircleName2 etc.
   */
  while (fgets(buffer, BUFFER_SIZE, configurations) != NULL){
    /** We jump lines :
     * <ul>
     *  <li> corresponding to MAC adress ; </li>
     *  <li> corresponding to the counters names </li>
     * </ul>
     */
    fgets(buffer, BUFFER_SIZE, configurations);
    fgets(buffer, BUFFER_SIZE, configurations);
    
    nbConfigurations++;
  }
  
  rewind(configurations); // equivalent to fseek(configurations,0,SEEK_SET)
  fclose(configurations);
  
  return nbConfigurations;
}

/**
 * \fn allocation_configurations_names(int nbConfigurations, ConfigurationName *tabConfigurations[])
 * 
 * \brief Creation of a void configuration names table.
 *
 * \param[in] int the number of configurations
 * \param[in,out] ConfigurationName* the table which will contain the configurations names
 */
void allocation_configurations_names(int nbConfigurations, ConfigurationName *tabConfigurations[]){
  *tabConfigurations = malloc(nbConfigurations*sizeof(ConfigurationName));
  if (*tabConfigurations == NULL){
    perror("Error allocating memory for tabConfigurations\n");
    return exit(EXIT_FAILURE);
  }
}

/**
 * \fn save_configurations_names(int nbConfigurations, ConfigurationName tabConfigurations[]){
 * 
 * \brief Configurations saving in the previously created table.
 *
 * \param[in] int the number of configurations
 * \param[in,out] ConfigurationName* the table which is going to contain the configurations names
 */
void save_configurations_names(int nbConfigurations, ConfigurationName tabConfigurations[]){
  
  int i                = 0 ;
  FILE* configurations = NULL;
  char buffer[BUFFER_SIZE];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while (i < nbConfigurations){
    fscanf(configurations,"%s",tabConfigurations[i]);
    fgets(buffer, BUFFER_SIZE , configurations); // to return to the end of the line
    
    // we jump the two unuseful lines
    fgets(buffer, BUFFER_SIZE, configurations);
    fgets(buffer, BUFFER_SIZE, configurations);
    
    i++;
  }
  rewind(configurations);
  fclose(configurations);
}

/**
 * \fn configuration_choice(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[])
 *
 * \brief This function permits to return the configuration identifier
 * in order to delete or to load a configuration. Not used in the plugwise dynamic library.
 * 
 * \param[in] the menu choice identifier
 * \param[in] int the number of configurations
 * \param[in] ConfigurationName* the table which contains the configurations names
 *
 * \return int the choosen configuration
 */
int configuration_choice(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[]){
  
  int i;
  
  printf("Which configuration would you like to ");  
  /** CHOICE I : load an existant configuration */
  if(MenuChoice == 1){
    printf("choose ?\n");
  }
  /** CHOICE III : delete an existant configuration */
  if(MenuChoice == 3){
    printf("remove ?\n");
  }
  
  for (i=0;i<nbConfigurations;i++)
    printf("%d : %s\n",i+1,tabConfigurations[i]);
  
  printf("Configuration n° : ");
  scanf("%d",&i);
  return i;
}

/**
 * \fn configuration_choice_parsing(int nbConfigurations, char *token, ConfigurationName tabConfigurations[])
 *
 * \brief This function returns the configuration identifier in order to load the chosen configuration.
 * It is the configuration_choice version for the plugwise esrv dynamic library. Not used in plugSdk.
 *
 * \param[in] int the number of configurations
 * \param[in] char* the name of the chosen configuration
 * \param[in] ConfigurationName* the table which contains the configurations names
 *
 * \return int the chosen configuration
 */
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

/**
 * \fn static_data_recovery(int MenuChoice, int configurationChosen, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles)
 *
 * \brief This function saves the static datas :
 * <ul>
 *  <li> root of pol.py ; </li>
 *  <li> number of circles. </li>
 * </ul>
 *
 * \param[in] int identifier of the menu choice
 * \param[in] int identifier of the chosen configuration
 * \param[in] ConfigurationName* the table which contains the configurations names
 * \param[in,out] char* root of pol.py
 * \param[int,out] int* number of circles
 */
void static_data_recovery(int MenuChoice, int configurationChosen, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles){
  
  int i                = 1 ; // we start reading from the first line
  FILE* configurations = NULL;
  char buffer[BUFFER_SIZE];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while(i < configurationChosen){ // to stop at the beguining of the line we want to read
    fgets(buffer, BUFFER_SIZE, configurations);
    fgets(buffer, BUFFER_SIZE, configurations); 
    fgets(buffer, BUFFER_SIZE, configurations);
    i++; 
  }
  
  /** CHOICE II : creation of a new configuration <br />
   * /!\ WHY CHOICE II ?
   */
  if(MenuChoice == 2){
    fscanf(configurations,"%s %s %d", tabConfigurations[configurationChosen-1], rootPython, nb_circles);
  }
  else
    fscanf(configurations,"%s %s %d",buffer,rootPython, nb_circles);
  
  fgets(buffer, BUFFER_SIZE, configurations);
  
  rewind(configurations);
  fclose(configurations);
}

/**
 * \fn dynamic_data_recovery(int configurationChosen, int nb_circles, MACaddress tabMAC[],char **counters_names)
 *
 * \brief This function saves dynamic datas :
 * <ul>
 *  <li> MAC addresses ; </li>
 *  <li> counters names. </li>
 * </ul>
 *
 * \param[in] int identifier of chosen configuration
 * \param[in] int number of circles
 * \param[in] ConfigurationName* the table which contains the configurations names
 * \param[in,out] MACaddress* table of MAC addresses
 * \param[in,out] char** table of counters names
 */
void dynamic_data_recovery(int configurationChosen, int nb_circles, MACaddress tabMAC[],char **counters_names){
  
  int i                = 1 ; // we start reading from the first line
  FILE* configurations = NULL;
  char buffer[BUFFER_SIZE];
  
  configurations = fopen("configurations.txt","r");
  if (configurations == NULL){
    perror("Error opening the file configurations.txt\n");
    return exit(EXIT_FAILURE);
  }   
  
  while(i < configurationChosen){ // to stop at the beguining of the line we want to read
    fgets(buffer, BUFFER_SIZE, configurations);
    fgets(buffer, BUFFER_SIZE, configurations); 
    fgets(buffer, BUFFER_SIZE, configurations);
    i++; 
  }
  
  fgets(buffer, BUFFER_SIZE, configurations); // we jump the line which corresponds to the dynamic data
  
  // Circles Mac adress
  for (i=0 ; i < nb_circles ; i++){
    fscanf(configurations,"%s ",tabMAC[i]); 
  }
  //  fgets(buffer, BUFFER_SIZE, configurations); // it goes to line
  
  // counters names
  for (i=0 ; i < nb_circles ; i++){
    fscanf(configurations,"%s ",counters_names[2*i]);
    sprintf(counters_names[2*i+1],"%s.decimals",counters_names[2*i]);
  }
  
  rewind(configurations);
  fclose(configurations);
}

/**
 * \fn configuration_display(int configurationChosen, ConfigurationName tabConfigurations[], char racinePython[], int nb_circles, char** counters_names, MACaddress tabMAC[])
 *
 * \brief This display the configuration you had created, loaded or todeleted
 *
 * \param[in] int identifier of chosen configuration
 * \param[in] ConfigurationName* configuration names table
 * \param[in] char* pol.py's root
 * \param[in] int number of circles
 * \param[in] char** table of counters names
 * \param[in] MACaddress table of MAC addresses
 */
void configuration_display(int configurationChosen, ConfigurationName tabConfigurations[], char racinePython[], int nb_circles, char** counters_names, MACaddress tabMAC[]){
  
  int i;  
  
  printf("Here is your configuration :\n");
  printf("Configuration's name: %s\n",tabConfigurations[configurationChosen-1] );
  printf("Root Python : %s\n",racinePython);
  printf("Number of circles : %d\n",nb_circles);
  printf("Elements that you want to measure power :\n");
  for (i=0 ; i < nb_circles - 1 ; i++)
    printf("  - %s (%s) ;\n", counters_names[2*i], tabMAC[i]);
  printf("  - %s (%s).\n", counters_names[2*i], tabMAC[i]);
}

/**
 * \fn write_static_data(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles)
 *
 * \brief This functions is only used for create or delete a configuration.
 * It writes static datas in the file configurations.txt.
 *
 * \param[in] int identifier of the menu choice
 * \param[in] int number of configurations
 * \param[in,out] ConfigurationName* table of configurations name
 * \param[in,out] char* pol.py's root
 * \param[in,out] int* number of circles
 */
void write_static_data(int MenuChoice, int nbConfigurations, ConfigurationName tabConfigurations[], char rootPython[], int *nb_circles){
  
  FILE* configurations = NULL;
  
  /** CHOICE II : create a configuration */
  if (MenuChoice == 2){
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

/**
 * \fn write_dynamic_data(int MenuChoice, int nb_circles, MACaddress tabMAC[], char **counters_names)
 *
 * \brief This functions is only used for create or delete a configuration.
 * It writes dynamic datas in the file configurations.txt.
 *
 * \param[in] int identifier of the menu choice
 * \param[in] int number of circles
 * \param[in,out] MACaddress* table of MAC addresses
 * \param[in,out] char** table of counters names
 */
void write_dynamic_data(int MenuChoice, int nb_circles, MACaddress tabMAC[], char **counters_names){
  
  int i                = 0;
  FILE* configurations = NULL;
  
  // Saving names and MAC addresses of circles
  for (i=0 ; i < nb_circles ; i++){
    if (MenuChoice == 2){
      printf(" * Circle's name %d : ",i+1);
      scanf("%s",counters_names[2*i]);
    }
    sprintf(counters_names[2*i+1],"%s.decimals",counters_names[2*i]);
    
    if(MenuChoice ==2){
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
