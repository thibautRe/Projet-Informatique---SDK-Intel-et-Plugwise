/**
 * \file plugSdk.c
 * \brief Ce programme permet d'importer les données des wattmètres Plugwise© dans un productivity link et de lancer des applications du SDK.
 * \author L'équipe TSP SDK / Plugwise
 * \version 1.2
 * \date 9 avril 2012
 * 
 * Dans un premier temps le programme initialise le(s) compteur(s) et importe les adresses MAC.<br>
 * Après avoir demandé pendant combien de temps on voulait effectuer l'analyse énergétique, <br>
 * les données de puissance sont collectées puis écrites dans le(s) compteur(s). <br>
 * Avant que le programme s'arrête, il ferme le productivity link.
 */
#include <stdio.h>
#include <uuid/uuid.h>          // pour identifier le compteur "plugwise".
#include <stdlib.h>             // EXIT_SUCCESS
#include <string.h>             // strcmp
#include <time.h>               // Timer pour l'arrêt du programme.
#include <unistd.h>             // Pour mettre en veille le programme.

#include "constantes.h"

#include "productivity_link.h"  // les fonctions spécifiques aux compteurs.
#include "fonctions.h"
#include "affichage.h"          // Les fonctions d'affichage ASCII
#include "gestion_configurations.h"

/**
 * \fn void main (void)
 * \brief Création du compteur "plugwise" dans /opt/productivity_link
 * \return EXIT_SUCCESS code de statut : ok. 
 * \return EXIT_FAILURE code de statut : erreur.
 */
int main (int argc, char *argv[], char *arge[]){ // char *arge[] permet d'utiliser les redirections avec la fonction popen
  /* BOUCLES */
  int i=0, j=0;
  
  /* CONFIGURATION */
  int nbConfigurations                = 0;
  NomConfiguration *tabConfigurations = NULL;
  int configurationChoisie            = 0;
  int nb_circles                      = 0;
  char racineSDK[TAILLE_RACINE]       = RACINE_SDK; // défini par le makefile
  char racinePython[TAILLE_RACINE]    = "";
  AdresseMAC *tabMAC                  = NULL;
  char **counters_names               = NULL; // Le nom de chaque compteurs est stocké dans un tableau de chaine de caractères 
  
  /* COMPTEUR */
  uuid_t uuid; // L'uuid (universal unique identifier) permettra d'identifier le productivity link "plugwise"
  char strUUID[TAILLE_UUID]; // pour pouvoir utiliser l'uuid on le convertie en chaine de charactères
  
  unsigned long long decimales        = NOMBRE_DECIMALES;
  unsigned long long puissance        = 0.0 ;
  int pld                             = PL_INVALID_DESCRIPTOR; // Initialisation du productivity link pld
  int ret                             = PL_FAILURE; // retour des commandes sur les compteurs
  
  /* TEMPS D'EXECUTION DU PROGRAMME */
  float nbrAnalysesParSecondes        = 0 ; 
  int tempsDanalyse                   = 0;  
  int t0                              = time(NULL); // Timestamp du début de programme
  
  /* EXECUTION DE PROGRAMMES EXTERNES */
  char commande[TAILLE_COMMANDE]; // pour les commandes à lancer via system ou via popen
  int architecture                    = 0; // pl_gui_monitor est différent suivant que l'on ait une architecture 64 bits ou 32 bits
  
  /* MENU */
  int choixMenu                       = 0;
 
  effacerEcran();
  
  // MENU CONFIGURATIONS
  
  printf("Que souhaitez-vous faire ?\n");
  printf("1 : Charger une configuration existante\n");
  printf("2 : Créer une nouvelle configuration\n");
  printf("3 : Supprimer une configuration\n");
  printf("4 : Lancer le programme sans toucher aux configurations\n");
  
  printf("Votre choix : ");
  scanf("%d",&choixMenu);
  
  effacerEcran();
  if(choixMenu==1){ /// CHARGEMENT D'UNE CONFIGURATION EXISTANTE :
    /// 1. On récupère le nombre et les noms des configurations
    nbConfigurations = nb_configurations();
    allocation_noms_configurations(nbConfigurations, &tabConfigurations);
    enregistrer_noms_configurations(nbConfigurations, tabConfigurations);
    
    /// 2. L'utilisateur choisi sa configuration
    configurationChoisie = choix_configuration(choixMenu, nbConfigurations, tabConfigurations);
    
    /// 3. On récupère les données de la configuration
    recuperation_donnees_statiques(choixMenu, configurationChoisie, tabConfigurations, racinePython,&nb_circles);
    allocation_dynamique_adresses_mac(nb_circles,&tabMAC);
    allocation_dynamique_noms_compteurs(nb_circles,&counters_names); 
    recuperation_donnees_dynamiques(configurationChoisie, nb_circles, tabMAC, counters_names);
    afficher_configuration(configurationChoisie, tabConfigurations, racinePython, nb_circles, counters_names, tabMAC);
    
    /// 4. On libère la mémoire prise par tabConfigurations
  }
  
  if (choixMenu == 2){ /// CREATION D'UNE NOUVELLE CONFIGURATION :
    allocation_noms_configurations(1, &tabConfigurations);
    ecrire_donnees_statiques(choixMenu, 1, tabConfigurations, racinePython, &nb_circles);      
    
    allocation_dynamique_adresses_mac(nb_circles,&tabMAC);
    allocation_dynamique_noms_compteurs(nb_circles,&counters_names); 
    ecrire_donnees_dynamiques(choixMenu, nb_circles, tabMAC, counters_names);
  }
  
  if (choixMenu == 3){ /// SUPPRIMER UNE CONFIGURATION :
    /// 1. On récupère le nombre et les noms des configurations
    nbConfigurations = nb_configurations();
    allocation_noms_configurations(nbConfigurations, &tabConfigurations);
    enregistrer_noms_configurations(nbConfigurations, tabConfigurations);
    
    /// 2. On demande à l'utilisateur de choisir la configuration à supprimer
    configurationChoisie = choix_configuration(choixMenu, nbConfigurations, tabConfigurations);
    
    /// 3. On récupère les données de la configuration
    system("touch configurations.tmp");
    i=1;
    while(i <= nbConfigurations){
      if(i != configurationChoisie){
	
	// Récupération des données
	recuperation_donnees_statiques(choixMenu, i, tabConfigurations, racinePython,&nb_circles);
	allocation_dynamique_adresses_mac(nb_circles,&tabMAC);
	allocation_dynamique_noms_compteurs(nb_circles,&counters_names); 
	recuperation_donnees_dynamiques(i, nb_circles, tabMAC, counters_names);
	afficher_configuration(i, tabConfigurations, racinePython, nb_circles, counters_names, tabMAC);
	
	// Permutation fichiers
	system("mv configurations.txt configurations.txt.tmp");
	system("mv configurations.tmp configurations.txt");
	
	// Ecriture des données
	ecrire_donnees_statiques(choixMenu, i, tabConfigurations, racinePython, &nb_circles);      
	ecrire_donnees_dynamiques(choixMenu, nb_circles, tabMAC, counters_names);
	
	system("mv configurations.txt configurations.tmp");
	system("mv configurations.txt.tmp configurations.txt");
	
	free(tabMAC);
	tabMAC=NULL;
	for (j=0;j<nb_circles;j++){
	  free(counters_names[j]);
	  counters_names[j]=NULL;
	}
	free(counters_names);
	counters_names=NULL;
      }
      i++;
    }
    system("rm configurations.txt");
    system("mv configurations.tmp configurations.txt");
  }
  
  while (strcmp(racinePython, "") == 0)
    initialiser_chemin_python(racinePython);
  
  if(choixMenu == 4)
    initialiser_plugwise(racinePython,&nb_circles,&tabMAC);
  
  // Choix du "temps" d'analyse de la puissance : 
  while (nbrAnalysesParSecondes <= 0){
    printf("Combien d'analyses par secondes voulez-vous faire ?\n");
    // changer en nb_analyse par minutes nan ?
    scanf("%f",&nbrAnalysesParSecondes);
  }
  
  while (tempsDanalyse <= 0){
    printf("Pendant combien de temps (secondes) voulez-vous lancer l'analyse ?\n");
    scanf("%d",&tempsDanalyse);
  }
  
  /// On créé un productivity link plugwise et l'on génère son uuid
  
  // system("rm -r /opt/productivity_link/plugwise_* 2> /dev/null"); 
  // On supprime les anciens productivity link plugwise ou pas ?
  
  pld = pl_open("plugwise",2*nb_circles,(const char **) counters_names,&uuid);
  if (pld == PL_INVALID_DESCRIPTOR){
    perror("Problème lors de l'ouverture du compteur !\n");
    return EXIT_FAILURE;
  }
  uuid_unparse(uuid,strUUID); // on récupère l'uuid que le SDK a généré dans une chaine de caractères 
  
  // On indique le nombre de décimales dans les compteurs
  /** Gestion des nombres décimaux :
   * L'interface graphique pl gui monitor du SDK ne peut
   * que afficher des unisgned long long (des grands entiers).
   * Pour afficher des nombres décimaux il faut donc utiliser une technique 
   * qui consiste à créer des compteurs compteur.decimals qui prennent comme valeur le nombre
   * de décimales que l'on souhaite afficher.
   *
   * Lors de la collecte des informations, on enregistre la valeur de puissance
   * dans une variable "double" ou "float" puis on la multiplie par 10^(nombre de décimales souhaitées).
   * Pour finir on la convertie en "unsigned long long" (lisible par PL GUI MONITOR).
   * Il ne faudra par contre pas oublier d'ajouter l'option "--process" lors de l'ouverture 
   * de l'interface graphique pour que le compteur compteur.decimals soit lu en tant qu'informateur sur le nombre
   * de décimales du compteur "compteur" et non en tant que compteur normal.
   */
  
for (i = 0; i < nb_circles; i++){
    ret = pl_write(pld,&decimales,2*i+1);
    if (ret == PL_FAILURE){
      perror("Erreur lors de l'écriture des \"compteurs\" statiques des décimales !\n");
      return EXIT_FAILURE;
    }
    ret = PL_FAILURE;
  }

  // MENU 

  printf("Choisissez :\n");
  printf("1 pour pl_gui_monitor\n");
  printf("2 pour pl_csv_logger\n");
  printf("3 pour les deux\n");
  scanf("%d",&choixMenu);
  switch (choixMenu){
  case 1 :
    lancement_interface_graphique_sdk(racineSDK,strUUID,&architecture);
    break; 
  case 2:
    lancement_pl_csv_logger_sdk(racineSDK,strUUID);
    break;
  case 3 : 
    lancement_pl_csv_logger_sdk(racineSDK,strUUID);
    lancement_interface_graphique_sdk(racineSDK,strUUID,&architecture);
  }
  
  // Affichage d'un message d'information
  afficherDebutProgramme();
  
  while (time(NULL) <= (t0 + tempsDanalyse)){
    // On actualise le(s) compteur(s) 2i
    for (i = 0; i < nb_circles; i++)
      {
	commande_python(i,racinePython,tabMAC,commande);
        
	puissance = (unsigned long long) (mesure_watt(commande) * ECHELLE);
	ret = pl_write(pld,&puissance,2*i);
	if (ret == PL_FAILURE)
	  {
	    perror("Erreur lors de l'écriture des compteurs !\n");
	    return EXIT_FAILURE;
	  }
	ret = PL_FAILURE;
	printf(".");
	fflush(stdout);
      }
    sleep(1);
  }
  
  printf("Analyse finie !\n");
  
  /// Fermeture du compteur et libération de la mémoire avant l'arrêt du programme
 
  desallocation(nb_circles, &tabConfigurations, &tabMAC, &counters_names);
  pl_close(pld);
  return EXIT_SUCCESS;
}
