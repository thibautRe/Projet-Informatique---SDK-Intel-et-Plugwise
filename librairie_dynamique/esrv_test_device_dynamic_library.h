#ifndef __INCLUDE_TEST_DEVICE__
#define __INCLUDE_TEST_DEVICE__

//-----------------------------------------------------------------------------
// headers inclusions
//-----------------------------------------------------------------------------
#include "pub_esrv.h"
//#include "pub_esrv_counters.h"
#include "gestion_configurations.h"
#include "allocation_memoire.h"
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
  /*--------------------------------------------------------------------------*/
  
  //-----------------------------------------------------------------------------
  // ESRV_API API drinition
  //-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
#ifdef _USRDLL
  // All files compiled for a DLL must be with TEMPLATE_DEVICE_EXPORTS
  // symbol defined this symbol should not be defined on any project 
  // that uses this DLL. 
#ifdef TEMPLATE_DEVICE_EXPORTS
#define ESRV_API __declspec(dllexport) extern
#else // TEMPLATE_DEVICE_EXPORTS
#define ESRV_API __declspec(dllimport) extern
#endif // TEMPLATE_DEVICE_EXPORTS
#endif // _USRDLL
#endif // __PL_WINDOWS__
  
#if (!defined(_USRDLL)) && defined(__cplusplus) 
#define ESRV_API extern "C"
#endif // (!defined(_USRDLL)) && defined(__cplusplus)
#if (!defined(_USRDLL)) && (!defined(__cplusplus)) 
#define ESRV_API extern
#endif // (!defined(_USRDLL)) && (!defined(__cplusplus))
  
  //-----------------------------------------------------------------------------
  // general definitions
  //-----------------------------------------------------------------------------
#define __PL_LINUX__
#include "constantes.h"
#define RACINE_SDK  "/home/telecom_sudparis/projet_informatique/iecsdk"
  //-----------------------------------------------------------------------------
  // messages definitions
  //-----------------------------------------------------------------------------
  // TODO: add here your device's messages' definitions (#define)
  
  //-----------------------------------------------------------------------------
  // device options structure
  //-----------------------------------------------------------------------------
  typedef struct _device_data {
    //-----------------------------------------------------------------------------
    // device options
    //-----------------------------------------------------------------------------
    /* CONFIGURATION */
    int nbConfigurations;
    NomConfiguration *tabConfigurations;
    int configurationChoisie;
    int nb_circles;
    char racineSDK[TAILLE_RACINE];
    char racinePython[TAILLE_RACINE];
    AdresseMAC *tabMAC;
    char **counters_names;
    
    /* TEMPS D'EXECUTION DU PROGRAMME */
    float nbrAnalysesParSecondes;
    
    /* EXECUTION DE PROGRAMMES EXTERNES */
    char commande[TAILLE_COMMANDE]; // pour les commandes à lancer via system ou via popen
    
    /* MENU */
    int choixMenu;
    
  } DEVICE_DATA, *PDEVICE_DATA;
  
  //-----------------------------------------------------------------------------
  // functions prototype
  //-----------------------------------------------------------------------------
  ESRV_API int init_device_extra_data(PESRV);
  ESRV_API int delete_device_extra_data(PESRV);
  ESRV_API int open_device(PESRV, void *);
  ESRV_API int close_device(PESRV, void *);
  ESRV_API int parse_device_option_string(PESRV, void *);
  //ESRV_API int read_device_all_measurements(PESRV, void *, int);
  ESRV_API int read_device_power(PESRV, void *, int);
  //ESRV_API int read_device_energy(PESRV, void *, int, int);
  // Optional functions' prototypes
  //ESRV_API int read_device_current(PESRV, void *, int);
  //ESRV_API int read_device_voltage(PESRV, void *, int);
  //ESRV_API int read_device_power_factor(PESRV, void *, int);
  //ESRV_API int read_device_voltage_frequency(PESRV, void *, int);
  //ESRV_API int read_device_current_frequency(PESRV, void *, int);
  
  /*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __INCLUDE_TEST_DEVICE__
