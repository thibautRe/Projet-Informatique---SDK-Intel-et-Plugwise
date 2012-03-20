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



/**
 * \fn void main (void)
 * \brief Création du compteur "plugwise" dans /opt/productivity_link
 * \return EXIT_SUCCESS code de statut : ok. 
 * \return EXIT_FAILURE code de statut : erreur.
 */
int main (int argc, char *argv[], char *arge[]){ // char *arge[] permet d'utiliser les redirections avec la fonction popen
  int i; // pour les boucles for ou while
  
  char commande[TAILLE_COMMANDE]; // pour les commandes à lancer via system ou via popen
  
  uuid_t uuid; // Le type uuid permet d'identifier le productivity link "plugwise"
  unsigned long long puissance = 0 ;
  int pld = PL_INVALID_DESCRIPTOR; // Initialisation du productivity link pld
  
  /** Le nom de chaque compteurs est stocké
   * dans un tableau constant de chaine de caractères
   * const char *counter[].
   * 
   * A FAIRE :
   * BIG PROBLEME : <<<<<<<<<<<<<<<<<<
   *
   * COMMENT ALLOUER DYNAMIQUEMENT un const char* ?
   */
  const char *counters_names[]={"puissance1","puissance2"}; 
    
  
  char racineSDK[TAILLE_RACINE]     = "";
  char racinePython[TAILLE_RACINE]  = "";
  
  /// "Temps" d'exécution du programme 
  float nbrAnalysesParSecondes; /// Initialisée plus bas
  int tempsDanalyse;            /// Initialisée plus bas
  int t0 = time(NULL);              /// Timestamp du début de programme
  
  adresseMAC *tabMAC=NULL;
  
  int nb_circle;
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
        
        
    
  
  while (strcmp(racineSDK, "") == 0)
    initialiser_chemin_sdk(racineSDK);
  while (strcmp(racinePython, "") == 0)
      initialiser_chemin_python(racinePython);
  initialiser_plugwise(racinePython,&nb_circle,&tabMAC);
  
  /// Choix du "temps" d'analyse de la puissance : 
  while (nbrAnalysesParSecondes <= 0)
  {
    printf("Combien d'analyses par secondes voulez-vous faire ?\n"); // attention on ne peut pas passer en dessous d'une analyse par secondes
    scanf("%f",&nbrAnalysesParSecondes);
  }
  
  while (tempsDanalyse <= 0)
  {
    printf("Pendant combien de temps (secondes) voulez-vous lancer l'analyse ?\n");
    scanf("%d",&tempsDanalyse);
  }
  
  /// On supprime l'ancien productivity link "plugwise", puis on ouvre le nouveau
  system("rm -r /opt/productivity_link/plugwise_* 2> /dev/null");
  pld = pl_open("plugwise",nb_circle,counters_names,&uuid);
  if (pld == PL_INVALID_DESCRIPTOR){
    perror("Problème lors de l'ouverture du compteur !\n");
    return EXIT_FAILURE;
  }

  // A FAIRE : CREER UN MENU DEMANDANT A L'UTILISATEUR DE CHOISIR ENTRE :
  //                 - lancer l'interface graphique ;
  //                 - créer un fichier .csv à lancer dans un tableur à l'aide de iecsdk/build/linux/pl_csv_logger
  //                   (il s'utilise comme ça : /../iesdk/../pl_csv_logger >> /blabla/fichierCSV.csv
  //                 - les deux.
  
   // TODO Décommenter cette ligne pour ceux dont l'interface graphique marche
   //lancement_interface_graphique_sdk(commande,racineSDK,&architecture); 
   
   // Affichage d'un message d'information
   afficherDebutProgramme();
   
   while (time(NULL) <= (t0 + tempsDanalyse))
     {
       // On actualise le(s) compteur(s) i
       for (i = 0; i < nb_circle; i++)
       {
            commande_python(i,racinePython,tabMAC,commande);
            
            puissance = mesure_watt(i,commande);
            pl_write(pld,&puissance,i);
            printf(".\n");
       }
       sleep(1/nbrAnalysesParSecondes);
     }
     
   printf("Analyse finie !\n");
   
   /// Fermeture du compteur avant l'arrêt du programme
   pl_close(pld);
   return EXIT_SUCCESS;
}
