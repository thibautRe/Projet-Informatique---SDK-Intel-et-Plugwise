/**
 * \file plugSdk.c
 * \brief Ce programme permet d'importer les données des wattmètres Plugwise© dans un productivity link et de lancer des applications du SDK.
 * \author L'équipe TSP SDK / Plugwise
 * \version 1.0
 * \date 21 mars 2012
 * 
 * Dans un premier temps le programme initialise le(s) compteur(s) et importe les adresses MAC.<br>
 * Après avoir demandé pendant combien de temps on voulait effectuer l'analyse énergétique, <br>
 * les données de puissance sont collectées puis écrites dans le(s) compteur(s). <br>
 * Avant que le programme s'arrête, il ferme le productivity link.
 */
#include <uuid/uuid.h>          // pour identifier le compteur "plugwise".
#include <stdlib.h>             // EXIT_SUCCESS
#include <string.h>             // strcmp
#include <unistd.h>             // pour l'attente (sleep).
#include <time.h>               // Timer pour l'arrêt du programme.
#include <unistd.h>             // Pour mettre en veille le programme.

#include "productivity_link.h"  // les fonctions spécifiques aux compteurs.
#include "fonctions.h"
#include "affichage.h"          // Les fonctions d'affichage ASCII

#define NOMBRE_DECIMALES 4
#define ECHELLE 10000.0 // 10^4

/**
 * \fn void main (void)
 * \brief Création du compteur "plugwise" dans /opt/productivity_link
 * \return EXIT_SUCCESS code de statut : ok. 
 * \return EXIT_FAILURE code de statut : erreur.
 */
int main (int argc, char *argv[], char *arge[]){ // char *arge[] permet d'utiliser les redirections avec la fonction popen
  int i; // pour les boucles for ou while
  
  char commande[TAILLE_COMMANDE]; // pour les commandes à lancer via system ou via popen
  
  uuid_t uuid; // L'uuid (universal unique identifier) permettra d'identifier le productivity link "plugwise"
  char strUUID[TAILLE_UUID]; // pour pouvoir utiliser l'uuid on le convertie en chaine de charactères

  unsigned long long decimales = NOMBRE_DECIMALES;
  unsigned long long puissance = 0.0 ;
  int pld = PL_INVALID_DESCRIPTOR; // Initialisation du productivity link pld
  int ret = PL_FAILURE; // retour des commandes sur les compteurs
  
  /** Le nom de chaque compteurs est stocké
   * dans un tableau constant de chaine de caractères
   * const char *counter[].
   * 
   * A FAIRE :
   * BIG PROBLEME : <<<<<<<<<<<<<<<<<<
   *
   * COMMENT ALLOUER DYNAMIQUEMENT un const char* ?
   */
    const char *counters_names[]={
    "puissance1",
    "puissance1.decimals",
    "puissance2",
    "puissance2.decimals",
    "puissance3",
    "puissance3.decimals",
    "puissance4"
    "puissance4.decimals"
  }; 
     
  char racineSDK[TAILLE_RACINE]     = "";
  char racinePython[TAILLE_RACINE]  = "";
  
  /// "Temps" d'exécution du programme (faudrait essayer de mieux gérer le temps d'exécution)
  float nbrAnalysesParSecondes      = 0 ;           /// Initialisée plus bas (nécessaire de descendre en dessous d'un échantillon par sec?)
  int tempsDanalyse                 = 0;            /// Initialisée plus bas
  int t0                            = time(NULL);   /// Timestamp du début de programme
  
  adresseMAC *tabMAC=NULL;
  
  int nb_circle = 0;
  int architecture;
  
#ifdef DEBUG_MODE
    char login;
    afficherDebugMode();
    printf("Entrez votre login\n");
    scanf("%c", &login);
    
    // Propriétés Thibaut
    if (login == 't')
    {
        strcpy(racineSDK, "/home/thibaut/Projet_Info");
        strcpy(racinePython, "/home/thibaut/Projet_Info/programme/python");
        nb_circle                           = 1;
        nbrAnalysesParSecondes              = 1;
        tempsDanalyse                       = 500;
    }
    
    
    
    /* ------------------------------------------ *
     *    AJOUTEZ ICI VOS PROFILS D'IMPORTATION   *
     * ------------------------------------------ */
    
    
#endif
        
        
    effacerEcran();
  
  while (strcmp(racineSDK, "") == 0)
    initialiser_chemin_sdk(racineSDK);
  while (strcmp(racinePython, "") == 0)
      initialiser_chemin_python(racinePython);
  initialiser_plugwise(racinePython,&nb_circle,&tabMAC);
  
  // Choix du "temps" d'analyse de la puissance : 
  while (nbrAnalysesParSecondes <= 0){
    printf("Combien d'analyses par secondes voulez-vous faire ?\n");
    /// NE FAUDRAIT-IL PAS PLUTOT CHOISIR COMBIEN D'ANALYSES PAR MINUTES ???
    /// (on ne sait pas encore comment actualiser les compteurs du SDK au dessous d'un échantillon par secondes)
    scanf("%f",&nbrAnalysesParSecondes);
  }
  
  while (tempsDanalyse <= 0)
  {
    printf("Pendant combien de temps (secondes) voulez-vous lancer l'analyse ?\n");
    scanf("%d",&tempsDanalyse);
  }
  
  /// On créé un productivity link plugwise et l'on génère son uuid

  // system("rm -r /opt/productivity_link/plugwise_* 2> /dev/null"); 
  // On supprime les anciens productivity link plugwise ou pas ?

  pld = pl_open("plugwise",2*nb_circle,counters_names,&uuid);
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
  
for (i = 0; i < nb_circle; i++){
    ret = pl_write(pld,&decimales,2*i+1);
    if (ret == PL_FAILURE){
      perror("Erreur lors de l'écriture des \"compteurs\" statiques des décimales !\n");
      return EXIT_FAILURE;
    }
    ret = PL_FAILURE;
  }

  // MENU 
  int choixMenu;
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
    // Youpilou !
    lancement_pl_csv_logger_sdk(racineSDK,strUUID);
    break;
  case 3 : 
    lancement_pl_csv_logger_sdk(racineSDK,strUUID);
    lancement_interface_graphique_sdk(racineSDK,strUUID,&architecture);
  }
  
   // Affichage d'un message d'information
   afficherDebutProgramme();
   
   while (time(NULL) <= (t0 + tempsDanalyse))
     {
       // On actualise le(s) compteur(s) 2i
       for (i = 0; i < nb_circle; i++)
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
   
   /// Fermeture du compteur avant l'arrêt du programme
   pl_close(pld);
   return EXIT_SUCCESS;
}
