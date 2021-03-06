/**
 * \file esrv_plugwise_driver.c
 * \brief Plugwise dynamic library which permits to communicate with circles
 *
 * \author The PlugSdk team of Télécom SudParis
 * \version 0.9
 * \date May 17th 2012
 * 
 * This file will permit to create a dynamic library for the ESRV.
 * Its library gives to ESRV the ability to send and receive information from the "stick".
 *
 * Function call sequence by the server :
 * <ol>
 *  <li> 1/ ESRV_API int init_device_extra_data(PESRV); // first call </li>
 *  <li> 2/ ESRV_API int parse_device_option_string(PESRV, void *); </li>
 *  <li> 3/ ESRV_API int init_device_extra_data(PESRV); // second call </li>
 *  <li> 4/ ESRV_API int open_device(PESRV, void *); </li>
 *  <li> 5-N/ ESRV_API int read_device_power(PESRV, void *, int); </li>
 *  <li> N+1/ ESRV_API int close_device(PESRV, void *); </li>
 *  <li> N+2/ ESRV_API int delete_device_extra_data(PESRV); </li>
 * </ol>
 */


// headers inclusions
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <assert.h>
#include "constants.h"

#include "pub_esrv.h"
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
 * \param[in,out] PESRV Pointer to an esrv data structure.
 * \return ESRV_SUCCESS status code: ok.
 * \return ESRV_FAILURE status code: erreur.
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
    /// <h1>I - First call from driver - before device option string parsing</h1>
    memset(&data,0,sizeof(DEVICE_DATA));
    px = (void *)&data;
    
    /** 
     * Add all initializations the device may require.  Add
     * the additional data into the definition of the DEVICE_DATA
     * structure (defined in template_device_dynamic_library.h file). 
     *
     * Use statically allocated data or dynamically allocated data.
     * If the data is dynamically allocated, then it can be done either
     * at first or second call of this function.  If using dynamically 
     * allocated data, it *must* be de-allocated at program end.  There
     * is an opportunity to do so in the delete_template_device_extra_data
     * function which is called at the server's end.
     */
    
    /// <h2> a. Initialization </h2>
    /* CONFIGURATION */
    px->nbConfigurations                = 0;
    px->tabConfigurations               = NULL;
    px->chosenConfiguration            = 0;
    px->nb_circles                      = 0;
    // px->racineSDK                       = "";
    px->tabMAC                          = NULL;
    px->counters_names                  = NULL; // The name of each counter is stored in an array of strings
    
    Plugwise initPlugwise   = {"Mac address"};
    Plugwise *pInitPlugwise = &initPlugwise; 
    px->plugwise = pInitPlugwise;
            
    /* PROGRAM EXECUTION TIME */
    px->nbrAnalysesParSecondes          = 0.0 ;   
    
    // sprintf(px->commande,"");
    
    /* MENU */
    px->menuChoice			= 0 ;
    /** 
     * Set the default virtual device count (1 based).  If the device
     * integrates 3 independent power readers sharing the same interface 
     * (source), then set this variable (virtual_devices) to 3.
     * Later on, the server will use this information to query each virtual
     *  device independently, by providing the virtual device's id (0 based)
     * in the call to the read_device_power function.
     */ 
    p->device_data.virtual_devices = 1 ;
    /// The number of virtual devices is changed between the first and second call, during the parsing function
    
    /// <h2> b. Plugwise configuration loading </h2>
    /// * We get the number and configuration names
    px->nbConfigurations = nb_configurations();
    allocation_configurations_names(px->nbConfigurations, &(px->tabConfigurations));
    save_configurations_names(px->nbConfigurations,px->tabConfigurations);
    
    /*
     * Set the f_hw_energy_integration_provided flag if the device can 
     * provide  hardware power integration.  If this flag is set, then 
     * read_device_energy is called at the update frequency (1Hz by default)
     * by the server.  As for the read_device_power function, the virtual
     * device's id is provided during the read_device_energy function.
     */
    p->f_hw_energy_integration_provided = 0;
    
    
    /// (Link of the data structure into the server's data structure before the parsing function)
    p->device_data.p_device_data = (void *)&data;
    
    /* a library supported device may use a proprietary interface to 
     * communicate with the server (for example the Yokogawa WT500 uses a 
     * modified TCP/IP interface).  In this case, the device - in the 
     * init_device_extra_data library function - sets the device_interface 
     * to ESRV_DEVICE_INTERFACE_PROPRIETARY, overwriting the default 
     * ESRV_DEVICE_INTERFACE_SERIAL. It is then the device's responsibility
     * to manage its interface.  This is done in the open_device and 
     * close_device functions.  Note that the device can still use the 
     * interface_options to collect device specific options (and therefore
     * allow for the proprietary interface configuration). */
    p->device_interface = ESRV_DEVICE_INTERFACE_PROPRIETARY;
    
    // Set the first call flag to 1.  This flag is used to distinguish 
    // the first from the second call in this function.
    f_first_init_call = 1;
    printf("call1\n");
  } else {
    /// <h1> II - Second call from the driver - post device option string parsing </h1>
    /** 
     * Add all additional initializations the device may require.  Add
     * the additional data into the definition of the DEVICE_DATA
     * structure (defined in template_device_dynamic_library.h file).
     * Use statically allocated data or dynamically allocated data.
     * If using dynamically allocated data, it *must* be de-allocated at 
     * program end.
     * There is an opportunity to do so in the 
     * delete_template_device_extra_data function which is called at the 
     * server's end.
     */ 
    
    PDEVICE_DATA pd = NULL;  
    pd = (void *)&data;
    if (pd == NULL){
      goto init_device_extra_data_error;
    }

    /// *  we get data from configuration
    pd->menuChoice = 1;
    static_data_recovery(pd->menuChoice,pd->chosenConfiguration, pd->tabConfigurations, pd->racinePython,&(pd->nb_circles));
    mac_adress_dynamic_allocation(pd->nb_circles,&(pd->tabMAC));
    counters_names_dynamic_allocation(pd->nb_circles,&(pd->counters_names)); 
    dynamic_data_recovery(pd->chosenConfiguration,pd->nb_circles,pd->tabMAC,pd->counters_names);
    configuration_display(pd->chosenConfiguration,pd->tabConfigurations,pd->racinePython,pd->nb_circles,pd->counters_names,pd->tabMAC);
    
    p->device_data.virtual_devices = pd->nb_circles ;
    /// * We free tabConfigurations </h3>
    free(pd->tabConfigurations);
  }    
  
  return(ESRV_SUCCESS);
 init_device_extra_data_error:
  return(ESRV_FAILURE);
}

/**
 * \fn delete_device_extra_data(PESRV p)
 * \brief free the device's dynamically allocated data
 * \param[in] Pointer to an esrv data structure
 * \return ESRV_SUCCESS status code: ok.
 * \return ESRV_FAILURE status code: ok.
 *
 * This function is called at the end of the server's run.  It is the
 * right location to de-allocate any dynamically allocated data used by
 * the device.
 */
ESRV_API int delete_device_extra_data(PESRV p) {
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
 * \return ESRV_SUCCESS status code: ok.
 * \return ESRV_FAILURE status code: error.
 *
 * This function provides the opportunity to open the device.  It is also a
 * good location to perform device initializations.  This function can be a
 * stub function if the device doesn't require any specific configurations 
 * to work.
 */
ESRV_API int open_device(PESRV p, void *px) {
  // px can be NULL if not required by device
  if(!p) { 
    goto open_device_error; 
  }
  
  // TODO: add the device's open code here
  
  // Assert material is actually functionning. 
  // send "STATUSCHANGE ON" for exemple
  return(ESRV_SUCCESS);
 open_device_error:
  return(ESRV_FAILURE);
}

/**
 * \fn close_device(PESRV p, void *px)
 * \brief Close the device.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv
 * \param[in,out] PESRV Pointeur vers un structure de données DEVICE_DATA
 * \return ESRV_SUCCESS status code: ok.
 * \return ESRV_FAILURE status code: error.
 *
 * This function provides the opportunity to close the device. <br />
 * This function can be a stub function if the device doesn't require any 
 * specific shutdown. 
 */
ESRV_API int close_device(PESRV p, void *px) {
  // px can be NULL if not required by device
  if(!p) { 
    goto close_device_error; 
  }
  /** Do we have to shut down the devices linked to the circles ?
   * If we do not, this function is useless in our case. */
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
 * \return ESRV_SUCCESS status code: ok.
 * \return ESRV_FAILURE status code: error.
 */
ESRV_API int read_device_all_measurements(PESRV p, void *px, int vd) {
  /** This library does not use this function */
  // px can be NULL if not required by device
  if(!p) { 
    goto read_device_power_error; 
  }
  /* validity check on virtual device count.
   * Note: virtual device id is 1 based (0 has a special meaning).*/
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
 * \return ESRV_SUCCESS status code: ok.
 * \return ESRV_FAILURE status code: error.
 */
ESRV_API int read_device_power(PESRV p, void *px, int vd) {
  PDEVICE_DATA pd = NULL;
  
  // Get back of the pol.py's data
  double power = 0;
  
  // px can be NULL if not required by device
  if(!p) { 
    goto read_device_power_error; 
  }
  
  pd = (PDEVICE_DATA)px;
  if (pd == NULL){
    goto read_device_power_error;
  }
  
  /* validity check on virtual device count.
   * Note: virtual device id is 1 based (0 has a special meaning) */
  if((vd <= 0) || (vd > p->device_data.virtual_devices) ) { 
    goto read_device_power_error; 
  }
  
  /** Collect the power read by the device here and return it in 
   * (p->double_power). The (vd) integer is the id of the virtual device 
   * queried by the server.
   * (vd) can be any integer between 0 and the maximum virtual device number
   * provided in the init_device_extra_data function.  By default,
   * the max vd is equal to 0.  The power must be provided in Watts. */
  pd->plugwise->macaddress = pd->tabMAC[vd-1];
  power = (double) getPowerInfo(pd->plugwise);
  if ((power <= MAX_POWER) && (power != 0.)){
    p->double_power = power;
    printf("vd %d : %f power\n",vd,power);
  }
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
  printf("parse1\n");
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
  
  // pd can be NULL if not required by device
  if(!p) { 
    goto parse_device_option_string_error;	
  }
  
  ps = p->device_option_string;
  assert(ps);
  
  /* If the user may need to provide configuration information for the device
   * then provide a parsing function of the device option string.
   * This string is pointed by the (ps) pointer.  This function can be a stub 
   * function if the device doesn't offer user accessible options.
   * These options should be defined in the DEVICE_DATA data structure, and 
   * this function should update those options in this function. */
  
  token = strtok(ps,token_delimiter);
  sub_token = strtok(token,sub_token_delimiter);
  sub_token = strtok(NULL,sub_token_delimiter);
  // there is the configuration name in sub_token
  
  printf("# number of configuration(s) : %d\n",px->nbConfigurations);
  px->chosenConfiguration = configuration_choice_parsing(px->nbConfigurations,sub_token,px->tabConfigurations);
  printf("# chosen configuration : %d\n",px->chosenConfiguration);  
 
  return(ESRV_SUCCESS);
 parse_device_option_string_error:
  return(ESRV_FAILURE);
}
