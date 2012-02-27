/**
 * \file main.c
 * \brief Ce programme permet d'importer les données des wattmètres dans un compteurs en utilisant pol.py.
 * \author L'équipe TSP Intel Energy Checker
 * \version 0.1
 * \date 27 février 2012
 * 
 * Dans un premier temps, le programme met le stick sous tension puis l'ouvre. <br>
 * On initialise ensuite les compteurs. <br>
 * Après avoir demandé pendant combien de temps on voulait effectuer l'analyse énergétique, <br>
 * les données de puissance sont collectées puis écrites dans les compteurs. <br>
 * Avant que le programme s'arrête, il ferme le compteur, puis éteint le Stick.
 */
#include <uuid/uuid.h> // pour identifier le compteur "plugwise".
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // pour l'attente (sleep).
#include "productivity_link.h" // les fonctions spécifiques aux compteurs.

/**
 * \fn void main (void)
 * \brief Création du compteur "plugwise" dans /opt/productivity_link
 * \return EXIT_SUCCESS code de statut : ok. 
 * \return EXIT_FAILURE code de statut : erreur.
 */
int main (void) {
  /** Le type uuid permet de donner un identificateur au compteur */  
  uuid_t uuid; 
  
  unsigned long long pWatt = 0 ;
  int pld = PL_INVALID_DESCRIPTOR;  
  /** Le nom du compteur est stocké
   * dans une constante de pointeur de chaine de caractères
   * const char *counter[].
   */
  const char *counter[] = {"puissance"};
  
  int time;
  int compteurTime=0;
  
  /// Initialisation du stick	
 system(`python machintruc/pol0.2_sources/pol.py -p <port>);
 system(`python machintruc/pol0.2_sources/pol.py -o <macaddresse>);
  
  /// Choix du temps d'analyse de la puissance : (en supposant que pl_write et lectureStick se font instantannément)
  printf("Pendants combien de temps (seconde) voulez-vous analyser la puissance ?\n");
  scanf("%d",&time);
  
  /// Ouverture et test du compteur.
  if ((pld = pl_open("plugwise",1,counter,&uuid)) != PL_INVALID_DESCRIPTOR){
    
    while(compteurTime!=time){
      /// Lecture des données de puissance collectées par le Stick.
      pWatt = system(`python machintruc/pol0.2_sources/pol.py -w <macaddresse>);
	
      /// pWatt est alors lue par le compteur.
      pl_write(pld,&pWatt,0);
      sleep(1);
      compteurTime++;
    }
    
    /// Fermeture du compteur
    pl_close(pld);

    /// Mise hors tension du Stick 
      system(`python machintruc/pol0.2_sources/pol.py -f <macaddresse>);
  }
  else{
    perror("Problème lors de l'ouverture du compteur !\n");
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
