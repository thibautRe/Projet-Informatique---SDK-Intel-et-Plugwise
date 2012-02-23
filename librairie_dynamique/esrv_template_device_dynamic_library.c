/**
 * \file esrv_template_device_dynamic_library.c
 * \brief Le modèle de fichier à coder pour construire la librairie dynamique
 * du device/ dispositif Plugwise (communication avec le "Stick").
 *
 * \author Intel©
 * \version 0.1
 * \date 2010
 * 
 * Ce fichier permettra de créer une librairie dynamique contenant les informations
 * pour demander les informations énergétiques au "stick".
 *
 * Les fonctions seronts appelées dans cet ordre par le serveur :
 * <ol>
 *  <li> ESRV_API int init_device_extra_data(PESRV); (appel 1) </li>
 *  <li> ESRV_API int parse_device_option_string(PESRV, void *); </li>
 *  <li> ESRV_API int init_device_extra_data(PESRV); (appel 2) </li>
 *  <li> ESRV_API int open_device(PESRV, void *); </li>
 *  <li> ... autres fonctions ... </li>
 *  <li> ESRV_API int read_device_power(PESRV, void *, int); </li>
 *  <li> ESRV_API int read_device_energy(PESRV, void *, int, int); (si disponible) </li>
 *  <li> ESRV_API int close_device(PESRV, void *); </li>
 *  <li> ESRV_API int delete_device_extra_data(PESRV); </li>
 * </ol>
*/
#include <string.h>
#include <assert.h>
#include <stdlib.h>
/**
 * Il faut inclure les fichiers .h des fonctions que l'on aura codé pour communiquer avec le "stick" (Plugwise).
 */
#include "pub_esrv.h"
#include "esrv_template_device_dynamic_library.h"

/** \fn init_device_extra_data(PESRV p)
 * \brief Initialisation du nouveau dispositif.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \return ESRV_SUCCESS code de statut : ok.
 * \return ESRV_FAILURE code de statut : erreur.
 */
ESRV_API int init_device_extra_data(PESRV p) {
  /** La structure de données du dispositif est créée dans cette fonction et est statique.
   * L'adresse de cette structure est écrite dans la structure de données du serveur
   * lors de la fin du premier appel de cette fonction.
   */
  static DEVICE_DATA data;
  static int f_first_init_call = 0;
  PDEVICE_DATA px = NULL;
  
  if(!p) { 
    goto init_device_extra_data_error; 
  }
  
  if(f_first_init_call == 0) {
    
    /** <h1> Premier appel par le dispositif </h1>
     * Avant la vérification de chaine de caractère optionnelle du dispositif (device option string parsing).
     */
    memset(
	   &data, 
	   0, 
	   sizeof(DEVICE_DATA)
	   );
    px = (void *)&data;
    
    /** <h2> Initialisation des structures de données où l'on stockera les informations </h2>
     * <ul>
     *  <li> Ajouter toutes les initialisations nécessaires pour utiliser Plugwise© ; </li>
     *  <li> Ajouter les données supplémentaires dans la définition de la structure DEVICE_DATA (cf. fichier .h) ; </li>
     *  <li> Utiliser des données allouées statiquement ou dynamiquement. </li>
     * </ul>
     * Si les données sont allouées de manière dynamique,
     * cela peut se faire lors du premier ou du second appel de la fonction. <br>
     * Il faut alors désallouer les données à la fin du programe. <br>
     * On peut faire cela dans la fonction delete_template_device_extra_data qui est appelée lors de l'arrêt du serveur.
     *
     * <strong> TODO: Ajouter le code d'initialisation du premier appel. </strong>
     */
    px->dummy = 0;

    /** Mettre le nombre par défault de dispositif virtuel (1 par défault).
     * Si le dispositif a trois outils de mesure énergétique, qui partagent le même interface,
     * mettre la variable virtual_devices à 3.
     * Plus tard, le serveur utilisera cette information pour gérer chaque dispositif virtuel de manière indépendante,
     * en fournissant l'ID (0 par défault) du dispositif virtuel dans l'appel de la fonction
     * read_device_power.
     *
     *  <strong> TODO: mettre la valeur par défault (1 dans notre cas)
     * du nombre de dispositif virtuel (1 par défault). </strong>
     */
    p->device_data.virtual_devices = 1;
    
    /** "Activer" la variable f_hw_energy_integration_provided flag si 
     * le dispotif fournit un matériel d'intégration énergétique (en puissance ?).
     * Si cette variable est activée, alors read_device_energy est appelée
     * à la fréquence d'actualisation (1Hz par défault) par le serveur.
     * Comme pour la fonction read_device_power l'ID du dispositif virtuel est
     * fournit pendant la fonction read_device_energy.
     * 
     * <strong> TODO : Affectation de valeur à la variable f_hw_energy_integration_provided. </strong>
     */
    p->f_hw_energy_integration_provided = 0;
    
    /** On lie la structure de données dans la structure de donnée du serveur */
    p->device_data.p_device_data = (void *)&data;
    
    /** A SUPPRIMER ? <br>
     * A library supported device may use a proprietary interface to 
     * communicate with the server (for example the Yokogawa WT500 uses a 
     * modified TCP/IP interface).  In this case, the device - in the 
     * init_device_extra_data library function - sets the device_interface 
     * to ESRV_DEVICE_INTERFACE_PROPRIETARY, overwriting the default 
     * ESRV_DEVICE_INTERFACE_SERIAL. It is then the device's responsibility
     * to manage its interface.  This is done in the open_device and 
     * close_device functions.  <br>
     * Note that the device can still use the 
     * interface_options to collect device specific options (and therefore
     * allow for the proprietary interface configuration).
     */
    p->device_interface = ESRV_DEVICE_INTERFACE_PROPRIETARY;
    
    /** Mettre la variable f_first_int_call à 1 permet de distinguer le premier appel 
     * du second appel de cette fonction .
     */
    f_first_init_call = 1;
    
  } else {
    
    /** <h1> Deuxième appel de la fonction par le dispositif </h1>
     * Après la vérification de chaine de caractère optionnelle du dispositif.
     */
    
    /** Ajouter toutes les initialisations additionnelles nécessaires pour le dispositif. <br>
     * Ajouter les données additionnelles dans la définition de la structure DEVICE_DATA
     * (définie dans le fichier templaite_device_dynamic_library.h). <br>
     * Utiliser des données allouées statiquement ou dynamiquement. <br>
     * Si on utilise des données allouées dynamiquement, il faut les désallouer lors de la fin du programme.
     * On peut le faire lors de l'appel en fin d'utilisation du serveur de la fonction
     * delete_template_device_extra_data.
     *
     * <strong> TODO: ajouter le code d'initialisation du second appel de la fonction. </strong>
     */
    ;		
    
  }
  
  return(ESRV_SUCCESS);
 init_device_extra_data_error:
  return(ESRV_FAILURE);
}

/**
 * \fn delete_device_extra_data(PESRV p)
 * \brief Libérer la mémoire allouée dynamiquement du dispositif.
 * \param[in] Pointeur vers une structure de données ESRV
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code statut erreur.
 */
ESRV_API int delete_device_extra_data(PESRV p) {
  
  if(!p) { 
    goto delete_device_extra_data_error; 
  }
  
  /** 
   * Cette fonction est appelée à la fin de l'exécution du serveur.
   * C'est le bon endroit pour désallouer toute la mémoire dynamique utilisée par le device.
   * 
   * <strong> TODO: ajouter le code de désallocation à cet endroit. </strong>
   */
  ; 
  
  return(ESRV_SUCCESS);
 delete_device_extra_data_error:
  return(ESRV_FAILURE);
}

/**
 * \fn open_device(PESRV p, void *px)
 * \brief Ouvrir le programme du device
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur
 */
ESRV_API int open_device(PESRV p, void *px) {
  
  /** px peut être NULL s'il est pas nécessaire pour le device. */
  if(!p) { 
    goto open_device_error; 
  }
  
  /**
   * Cette fonction permet d'indiquer à pol le numéro de port du stick et de lui donner l'adresse MAC des "Circle" (?).
   * C'est aussi le bon endroit pour vérifier les initialisations du device.
   * 
   * <strong> TODO: Ajouter le code d'ouverture du "stick" à cet endroit. </strong>
   */
  ;

   // On indique le port série du stick Plugwise (par exemple /dev/ttyUSB0
    system(`python ***/pol0.2_sources/pol.py -p <port>);

    // On "allume le stick" avec la bonne adresse MAC
    system(`python ***/pol0.2_sources/pol.py -o <macaddresse>);

  return(ESRV_SUCCESS);
 open_device_error:
  return(ESRV_FAILURE);
}

/**
 * \fn close_device(PESRV p, void *px)
 * \brief Fermeture du programme du device.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv
 * \param[in,out] PESRV Pointeur vers un structure de données DEVICE_DATA
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 */
ESRV_API int close_device(PESRV p, void *px) {
  
  /** px peut être NULL s'il n'est pas nécessaire pour le device. */
  if(!p) { 
    goto close_device_error; 
  }
  
  /** 
   * Cette fonction permet d'éteindre le stick.
   *
   * <strong> TODO: Ajouter le code de fermeture du device ici. </strong>
   */
  
  // On "allume le stick" avec la bonne adresse MAC
    system(`python ***/pol0.2_sources/pol.py -f <macaddresse>);
  
  return(ESRV_SUCCESS);
 close_device_error:
  return(ESRV_FAILURE);
}

/**
 * \fn read_device_power(PESRV p, void *px, int vd)
 * \brief Lit les informations concernant la puissance données par le périphérique.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \param[in] int L'ID du périphérique virtuel (du "stick").
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 */
ESRV_API int read_device_power(PESRV p, void *px, int vd) {
  
  /** px peut être NULL s'il n'est pas nécessaire pour le device. */
  if(!p) { 
    goto read_device_power_error; 
  }
  
  /**
   * Vérification de l'ID  du "stick". <br>
   * On pourrait supprimer cette étape puisque dans tous les cas on aura qu'un périphérique. <br>
   *N.B. : L'ID des périphériques virtuels est par défault 1 (0 a un rôle spécifique).
   */
  if(
     (vd <= 0) || 
     (vd > p->device_data.virtual_devices)
     ) { 
    goto read_device_power_error; 
  }
  
  /** Collecte la puissance par le device et la retourne dans p->double_power.
   * L'entier vd est l'ID tu périphérique virtuel donné par le serveur.
   * vd peut être n'importe quel entier compri entre 0 et le nombre maximum
   * de périphériques virtuels donné par la fonction init_device_extra_data.<br>
   * Par défault, le vd max est égal à 0. <br>
   * La puissance doit être fournie en Watts.
   *
   * <strong> TODO : Il faut ajouter le code de lecture de la puissance du device ici. </strong>
   */
  
  // On appel pol.py pour collecter la puissance
  p->double_power = system(`python ***/pol0.2_sources/pol.py -w <macaddresse>);
  
  return(ESRV_SUCCESS);
 read_device_power_error:
  return(ESRV_FAILURE);
}

/**
 * \fn parse_device_option_string(PESRV p, void *pd)
 * \brief Analyse de la chaine de caractère optionnelle du device et configuration de la structure esrv.
 * \param[in,out] PESRV Pointeur vers une structure de données esrv.
 * \param[in,out] void* Pointeur vers une structure de données DEVICE_DATA.
 * \return ESRV_SUCCESS : code de statut ok.
 * \return ESRV_FAILURE : code de statut erreur.
 */
ESRV_API int parse_device_option_string(PESRV p, void *pd) {
  
  char *ps = NULL;
  
  /** pd peut être NULL s'il n'est pas nécessaire pour le device. */
  if(!p) { 
    goto parse_device_option_string_error;	
  }
  
  ps = p->device_option_string;
  assert(ps);
  
  /** 
   * Si l'utilisateur a besoin de fournir des informations de configuration pour le device,
   * alors il doit fournir une fonction d'analyse de la syntaxe de la chaine de caractère optionnelle du device.
   * Cette chaine de caractère est pointée par le pointeur ps.
   * Cette fonction peut être une "stub function" si le device n'offre pas à l'utilisateur d'options
   * accessibles.
   *
   * Ces options devraient être défini dans la structure de données DEVICE_DATA, et cette fonction
   * devrait mettre à jour ces options dans cette fonction.
   *
   * <strong> TODO: ajouter le code l'analyse syntaxique de la chaine de caractère optionnel du device ici </strong>
   */
  ;
  
  return(ESRV_SUCCESS);
 parse_device_option_string_error:
  return(ESRV_FAILURE);
}
