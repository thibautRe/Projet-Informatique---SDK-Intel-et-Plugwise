/**
 * \file hello_world.c
 * \brief Le hello world pour faire fonctionner des compteurs.
 * \author L'équipe TSP Intel Energy Checker
 * \version 1
 * \date 27 février 2012
 * 
 * Un fichier nom_compteur_<uuid> sera créé dans le répertoire /opt/productivity_link.
 * Les fichiers "grandeur_a_analyser" et pl_config.ini seront créés et dans l'interface graphique
 * pl_gui_moniteur, le compteur nom_compteur affichera "nombre" "grandeur_a_analyser".
 *
 * Dans le cas présent, "nombre" est initialisé à 0 et est incrémenté chaque seconde jusqu'à 21.
 * Ensuite il est décrémenté jusqu'à la valeur 5.
 */

#include <uuid/uuid.h> // pour identifier le compteur "nom_compteur".
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // pour l'attente (sleep).
#include "productivity_link.h" // les fonctions spécifiques aux compteurs.

/**
 * \fn void main (void)
 * \brief Création du compteur "nom_compteur" dans /opt/productivity_link
 * \return EXIT_SUCCESS code de statut : ok. 
 * 
 */
int main (void) {
  /** Le type uuid permet de donner un identificateur au compteur */  
  uuid_t uuid; 
  
  unsigned long long nombre=0 ;
  int pld = PL_INVALID_DESCRIPTOR;
  
  /** Le nom du compteur est stocké
   * dans une constante de pointeur de chaine de caractères
   * const char *counter[].
   */
  const char *counter[] = {"grandeur_a_analyser"};
  
  /// Ouverture et test du compteur.
  if ((pld = pl_open("nom_compteur",1,counter,&uuid)) != PL_INVALID_DESCRIPTOR){
    
    /// Incrémentation de "nombre" jusqu'à 21.
    while (nombre<=21){
      pl_write(pld,&nombre,0);
      nombre++;
      sleep(1);
    }

    /// Décrémentation de "nombre" jusqu'à 5.
    while (nombre>5){
      nombre--;
      pl_write(pld,&nombre,0);
      sleep(1);
    }
    
    /// Fermeture du compteur
    pl_close(pld);
  }
  
  return EXIT_SUCCESS;
}
