/**
 * \file hello_world.c
 * \brief Le hello world pour faire fonctionner des compteurs.
 * \author Intel©
 * \version 0.1
 * \date 2010
 * 
 * Un fichier hello_<uuid> sera créé dans le répertoire /opt/productivity_link.
 * Les fichiers "world" et pl_config.ini sont créés et le compteurs hello affiche 42 "world".
 *
 */

#include <uuid/uuid.h>
#include "productivity_link.h"

/**
 * \fn void main (void)
 * \brief Entrée du programme.
 */
void main (void) {
/** Le type uuid permet de donner une adresse au compteur */  
  uuid_t uuid; 

  unsigned long long the_answer=42 ;
  int pld = PL_INVALID_DESCRIPTOR;

/** Le nom du compteur est stocké
 * dans une constante de pointeur de chaine de caractères
 * const char *counter[]
*/
  const char *counter[] = {"World"};
  if ((pld = pl_open("Hello",1,counter,&uuid)) != PL_INVALID_DESCRIPTOR){
      pl_write(pld,&the_answer,0);
      pl_close(pld);
  }
}
