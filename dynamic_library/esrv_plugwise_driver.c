/**
 * \file esrv_template_device_dynamic_library.c
 * \brief Le modèle de fichier à coder pour construire la librairie dynamique
 * du device/ dispositif Plugwise (communication avec le "Stick").
 *
 * \author The PlugSdk team of Télécom SudParis
 * \version 0.1
 * \date 24 avril 2012
 * 
 * Ce fichier permettra de créer une librairie dynamique contenant les informations
 * pour demander les informations énergétiques au "stick".
 *
 * Function call sequence by the server :
 * <ol>
 *  <li> 1/ ESRV_API int init_device_extra_data(PESRV); // first call </li>
 *  <li> 2/ ESRV_API int parse_device_option_string(PESRV, void *); </li>
 *  <li> 3/ ESRV_API int init_device_extra_data(PESRV); // second call </li>
 *  <li> 4/ ESRV_API int open_device(PESRV, void *); </li>
 *  <li> 5-N/ ESRV_API int read_device_power(PESRV, void *, int); </li>
 *  <li> .../ ESRV_API int read_device_energy(PESRV, void *, int); if available </li>
 *  <li> N+1/ ESRV_API int close_device(PESRV, void *); </li>
 *  <li> N+2/ ESRV_API int delete_device_extra_data(PESRV); </li>
 * </ol>
 */

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <assert.h>
#include <unistd.h> // sleep
#include "constants.h"
/**
 * Il faut inclure les fichiers .h des fonctions que l'on aura codé pour communiquer avec le "stick" (Plugwise).
 */
#include "pub_esrv.h"
//#include "pub_esrv_counters.h"
#include "esrv_plugwise_driver.h"

#ifdef __PL_WINDOWS__
// TODO: add here Windows specific header inclusions 
// the device management may require.
#endif // __PL_WINDOWS__ 

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)  
#include <stdlib.h>
// TODO: add here *NIX specific header inclusions 
// the device management may require.
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

/** 
 * \fn init_device_extra_data(PESRV p)
 * \brief initialize the device's extra data set.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \return ESRV_SUCCESS code de statut : ok.
 * \return ESRV_FAILURE code de statut : erreur.
 */
ESRV_API int init_device_extra_data(PESRV p) {
  /**
   * The device data structure is allocated in this function and 
   * is static.  The address of this structure is linked into the server's
   * data structure at the end of the first call of this function.
   */
  
  static DEVICE_DATA data;
  static int f_first_init_call = 0;
  PDEVICE_DATA px = NULL;
  if(!p) { 
    goto init_device_extra_data_error; 
  }
  
  if(f_first_init_call == 0){
    printf("1. First call initialize device extra data\n");
    //---------------------------------------------------------------------
    // first call from driver - before device option string parsing
    //---------------------------------------------------------------------
    memset(&data,0,sizeof(DEVICE_DATA));
    px = (void *)&data;
    
    //---------------------------------------------------------------------
    // Add all initializations the device may require.  Add
    // the additional data into the definition of the DEVICE_DATA
    // structure (defined in template_device_dynamic_library.h file).
    // Use statically allocated data or dynamically allocated data.
    // If the data is dynamically allocated, then it can be done either
    // at first or second call of this function.  If using dynamically 
    // allocated data, it *must* be de-allocated at program end.  There
    // is an opportunity to do so in the delete_template_device_extra_data
    // function which is called at the server's end.
    //---------------------------------------------------------------------
    
    /* CONFIGURATION */
    px->nbConfigurations                = 0;
    px->tabConfigurations               = NULL;
    px->configurationChoisie            = 0;
    px->nb_circles                      = 0;
    sprintf(px->racineSDK,RACINE_SDK);
    sprintf(px->racinePython,"");
    px->tabMAC                          = NULL;
    px->counters_names                  = NULL; // Le nom de chaque compteurs est stocké dans un tableau de chaine de caractères 
    
    /* TEMPS D'EXECUTION DU PROGRAMME */
    px->nbrAnalysesParSecondes          = 0.0 ;   
    
    /* EXECUTION DE PROGRAMMES EXTERNES */
    sprintf(px->commande,"");
    
    /* MENU */
    px->choixMenu=0;
    //---------------------------------------------------------------------
    // Set the default virtual device count (1 based).  If the device
    // integrates 3 independent power readers sharing the same interface 
    // (source), then set this variable (virtual_devices) to 3.
    // Later on, the server will use this information to query each virtual
    // device independently, by providing the virtual device's id (0 based)
    // in the call to the read_device_power function.
    //---------------------------------------------------------------------
    p->device_data.virtual_devices = 1 ;
    // the number of virtual devices is changed between the first and second call, during the parsing function
    
    /** CHARGEMENT D'UNE CONFIGURATION PLUGWISE : */
    /// 1. On récupère le nombre et les noms des configurations
    px->nbConfigurations = nb_configurations();
    allocation_configurations_names(px->nbConfigurations, &(px->tabConfigurations));
    save_configurations_names(px->nbConfigurations,px->tabConfigurations);
    
    //---------------------------------------------------------------------
    // Set the f_hw_energy_integration_provided flag if the device can 
    // provide  hardware power integration.  If this flag is set, then 
    // read_device_energy is called at the update frequency (1Hz by default)
    // by the server.  As for the read_device_power function, the virtual
    // device's id is provided during the read_device_energy function.
    //---------------------------------------------------------------------
    // TODO: position the f_hw_energy_integration_provided flag
    p->f_hw_energy_integration_provided = 0;
    
    //---------------------------------------------------------------------
    // Link of the data structure into the server's data structure
    //---------------------------------------------------------------------
    p->device_data.p_device_data = (void *)&data;
    
    //---------------------------------------------------------------------
    // a library supported device may use a proprietary interface to 
    // communicate with the server (for example the Yokogawa WT500 uses a 
    // modified TCP/IP interface).  In this case, the device - in the 
    // init_device_extra_data library function - sets the device_interface 
    // to ESRV_DEVICE_INTERFACE_PROPRIETARY, overwriting the default 
    // ESRV_DEVICE_INTERFACE_SERIAL. It is then the device's responsibility
    // to manage its interface.  This is done in the open_device and 
    // close_device functions.  Note that the device can still use the 
    // interface_options to collect device specific options (and therefore
    // allow for the proprietary interface configuration).
    //---------------------------------------------------------------------
    p->device_interface = ESRV_DEVICE_INTERFACE_PROPRIETARY;
    
    //---------------------------------------------------------------------
    // Set the first call flag to 1.  This flag is used to distinguish 
    // the first from the second call in this function.
    //---------------------------------------------------------------------
    f_first_init_call = 1;
    
  } else {
    printf("3. Second call initialize device extra data\n");
    
    //---------------------------------------------------------------------
    // Second call from the driver - post device option string parsing
    //---------------------------------------------------------------------
    
    //---------------------------------------------------------------------
    // Add all additional initializations the device may require.  Add
    // the additional data into the definition of the DEVICE_DATA
    // structure (defined in template_device_dynamic_library.h file).
    // Use statically allocated data or dynamically allocated data.
    // If using dynamically allocated data, it *must* be de-allocated at 
    // program end.
    // There is an opportunity to do so in the 
    // delete_template_device_extra_data function which is called at the 
    // server's end.
    //---------------------------------------------------------------------
    
    PDEVICE_DATA pd = NULL;  
    pd = (void *)&data;
    if (pd == NULL){
      goto init_device_extra_data_error;
    }
    
    /** CHARGEMENT D'UNE CONFIGURATION PLUGWISE : SUITE */
    /// (1. On récupère le nombre et les noms des configurations)
    // Effectué lors du premier appel
    /// (2. L'utilisateur choisi sa configuration)
    // configurationChoisie est modifiée lors du parsing
    
    /// 3. On récupère les données de la configuration
    pd->choixMenu=1;
    static_data_recovery(pd->choixMenu,pd->configurationChoisie, pd->tabConfigurations, pd->racinePython,&(pd->nb_circles));
    mac_adress_dynamic_allocation(pd->nb_circles,&(pd->tabMAC));
    counters_names_dynamic_allocation(pd->nb_circles,&(pd->counters_names)); 
    dynamic_data_recovery(pd->configurationChoisie,pd->nb_circles,pd->tabMAC,pd->counters_names);
    configuration_display(pd->configurationChoisie,pd->tabConfigurations,pd->racinePython,pd->nb_circles,pd->counters_names,pd->tabMAC);
    
    p->device_data.virtual_devices = pd->nb_circles ;
    /// 4. On libère tabConfigurations
    free(pd->tabConfigurations);
  }    
  
  return(ESRV_SUCCESS);
 init_device_extra_data_error:
  return(ESRV_FAILURE);
}

/**
 * \fn delete_device_extra_data(PESRV p)
 * \brief free the device's dynamically allocated data
 * \param[in] Pointeur vers une structure de données ESRV
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code statut erreur.
 *
 * This function is called at the end of the server's run.  It is the
 * right location to de-allocate any dynamically allocated data used by
 * the device.
 */
ESRV_API int delete_device_extra_data(PESRV p) {
  
  printf("3. Delete device extra data\n");
  if(!p) { 
    goto delete_device_extra_data_error; 
  }
  
  //TODO: add the de-allocation code here
  
  return(ESRV_SUCCESS);
 delete_device_extra_data_error:
  return(ESRV_FAILURE);
}

/**
 * \fn open_device(PESRV p, void *px)
 * \brief Open the template device.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur
 *
 * This function provides the opportunity to open the device.  It is also a
 * good location to perform device initializations.  This function can be a
 * stub function if the device doesn't require any specific configurations 
 * to work.
 */
ESRV_API int open_device(PESRV p, void *px) {
  
  printf("4. Open device\n");
  // px can be NULL if not required by device
  if(!p) { 
    goto open_device_error; 
  }
  
  // TODO: add the device's open code here
  
  // On indique le port série du stick Plugwise (par exemple /dev/ttyUSB0)
  // Ok en utilisant la libc faite par Nicolas et Thibaut sinon pas possible avec pol.py
  
  // On s'assure que le matériel est bien allumé ? ou pas ?
  // system(`python ***/pol0.2_sources/pol.py -o <macaddresse>);
  
  return(ESRV_SUCCESS);
 open_device_error:
  return(ESRV_FAILURE);
}

/**
 * \fn close_device(PESRV p, void *px)
 * \brief Close the device.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv
 * \param[in,out] PESRV Pointeur vers un structure de données DEVICE_DATA
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 *
 * This function provides the opportunity to close the device. <br />
 * This function can be a stub function if the device doesn't require any 
 * specific shutdown. 
 */
ESRV_API int close_device(PESRV p, void *px) {
  
  printf("coucou5 - close device\n");
  // px can be NULL if not required by device
  if(!p) { 
    goto close_device_error; 
  }
  /** Do we have to shut down the devices linked to the circles ?
   * If we do not, this function is useless in our case.
   */
  return(ESRV_SUCCESS);
 close_device_error:
  return(ESRV_FAILURE);
}

/**
 * \fn read_device_all_measurements(PESRV p, void *px, int vd)
 * \brief Lit les informations concernant la puissance données par le périphérique.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \param[in] int L'ID du périphérique virtuel (du "stick").
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 */
ESRV_API int read_device_all_measurements(PESRV p, void *px, int vd) {
  
  printf("5-N.  read device all \n");
  // px can be NULL if not required by device
  if(!p) { 
    goto read_device_power_error; 
  }
  /** 
   * validity check on virtual device count.
   * Note: virtual device id is 1 based (0 has a special meaning).
   */
  if( (vd <= 0) || (vd > p->device_data.virtual_devices) ) { 
    goto read_device_power_error; 
  }
  
  return(ESRV_SUCCESS);
 read_device_power_error:
  return(ESRV_FAILURE);
}

/**
 * \fn read_device_power(PESRV p, void *px, int vd)
 * \brief Read the device power.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \param[in] int The virtual device's id.
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 */
ESRV_API int read_device_power(PESRV p, void *px, int vd) {
  PDEVICE_DATA pd = NULL;
  
  // Get back of the pol.py's data
  FILE *pp = NULL;
  char tampon[BUFFER_SIZE];
  double puissance;
  
  printf("5-N. Read device power\n");
  // px can be NULL if not required by device
  if(!p) { 
    goto read_device_power_error; 
  }
  
  pd = (PDEVICE_DATA)px;
  if (pd == NULL){
    goto read_device_power_error;
  }
  
  //-------------------------------------------------------------------------
  // validity check on virtual device count.
  // Note: virtual device id is 1 based (0 has a special meaning)
  //-------------------------------------------------------------------------
  if((vd <= 0) || (vd > p->device_data.virtual_devices) ) { 
    goto read_device_power_error; 
  }
  
  //-------------------------------------------------------------------------
  // Collect the power read by the device here and return it in 
  // (p->double_power). The (vd) integer is the id of the virtual device 
  // queried by the server.
  // (vd) can be any integer between 0 and the maximum virtual device number
  // provided in the init_device_extra_data function.  By default,
  // the max vd is equal to 0.  The power must be provided in Watts.
  //-------------------------------------------------------------------------
  
  // Création de la commande d'appel à pol.py
  sprintf(pd->commande,"sudo python %s/pol.py -w %s 2> /dev/null",pd->racinePython,pd->tabMAC[vd-1]);
  
  // Exécution et écriture de la commande dans le "pipe"
  pp = popen (pd->commande, "r");
  if (pp == NULL){
    perror ("popen error !");
    exit(EXIT_FAILURE);
  }
  
  // Ecriture du résultat de la commande dans le tampon via le "pipe"
  fgets (tampon, sizeof (tampon), pp);
  
  pclose(pp);
  tampon[strlen (tampon) - 1] = '\0';
  puissance = atof(tampon);
  if (puissance <= MAX_POWER)
    p->double_power= (double) puissance;
  printf("vd %d : %f watt\n",vd,puissance);
  
  return(ESRV_SUCCESS);
 read_device_power_error:
  return(ESRV_FAILURE);
}

/** 
 * \fn read_device_energy(PESRV p, void *px, int vd, int s)
 * \brief Read energy from device.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \param[in] int The virtual device's id.
 * \param[in] int The service request :
 * <ul>
 *  <li> READ_DEVICE_ENERGY_INIT: requested once, at server start ;
 *  <li> READ_DEVICE_ENERGY_START: requested once, at server start right after ;
 *  <li> READ_DEVICE_ENERGY_INIT ;
 *  <li> READ_DEVICE_ENERGY_READ: requested at will, possibly indefinitely ;
 *  <li> READ_DEVICE_ENERGY_STOP: requested once at server stop ;
 *  <li> READ_DEVICE_ENERGY_RESET: requested at will, possibly indefinitely ;
 * </ul>
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 */
ESRV_API int read_device_energy(PESRV p, void *px, int vd, int s) {
  
  printf(".... Read device energy\n");
  // px can be NULL if not required by device
  if(!p) { 
    goto read_device_energy_error; 
  }
  
  return(ESRV_SUCCESS);
 read_device_energy_error:
  return(ESRV_FAILURE);
}

/**
 * \fn parse_device_option_string(PESRV p, void *pd)
 * \brief Read parse device option.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 *
 * This function is used if we call the esrv with the option --device_options : <br />
 * The string following the --device_options argument is passed to the parse_device_option_string() function
 * between the two consecutive calls to the init_device_extra_data() function. <br />
 * With our library the syntax is as the follow : <br />>
 * --devices_options "config=<config's name> sampling_time=<time>" 
 */
ESRV_API int parse_device_option_string(PESRV p, void *pd) {
  
  // Link of the pointer pd with the static data structure
  PDEVICE_DATA px = NULL;  
  px = (p->device_data.p_device_data);
  if (px == NULL){
    goto parse_device_option_string_error;
  }
  
  char *ps                   = NULL;
  char *token                = NULL;
  char *sub_token            = NULL;
  char *token_delimiter      = " ";
  char *sub_token_delimiter  = "=";
  
  char buffer[BUFFER_SIZE] = "";
  
  printf("2. Parse device option string\n");
  // pd can be NULL if not required by device
  if(!p) { 
    goto parse_device_option_string_error;	
  }
  
  ps = p->device_option_string;
  assert(ps);
  
  /**
   * If the user may need to provide configuration information for the device
   * then provide a parsing function of the device option string.
   * This string is pointed by the (ps) pointer.  This function can be a stub 
   * function if the device doesn't offer user accessible options.
   * These options should be defined in the DEVICE_DATA data structure, and 
   * this function should update those options in this function.
   */
  
  token = strtok(ps,token_delimiter);
  sub_token = strtok(token,sub_token_delimiter);
  sub_token = strtok(NULL,sub_token_delimiter);
  // dans sub_token se trouve le nom de la configuration
  
  printf("nb config : %d\n",px->nbConfigurations);
  px->configurationChoisie = configuration_choice_parsing(px->nbConfigurations,sub_token,px->tabConfigurations);
  printf("Configuration choisie : %d\n",px->configurationChoisie);  
  
  return(ESRV_SUCCESS);
 parse_device_option_string_error:
  return(ESRV_FAILURE);
}
