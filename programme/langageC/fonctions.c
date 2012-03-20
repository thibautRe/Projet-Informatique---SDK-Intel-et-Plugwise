#include "fonctions.h"

void initialiser_chemin_sdk(char racineSDK[]){
  printf("Quel est le chemin menant au répertoire iecsdk ?\n");
  scanf("%s",racineSDK);
}

void initialiser_chemin_python(char racinePython[]){
  printf("Dans quel répertoire est situé votre fichier pol.py ?\n");
  scanf("%s",racinePython);
}
  
void initialiser_plugwise(char racinePython[],int *nb_circle, adresseMAC *tabMAC[]){
  int i;
  
  while (*nb_circle <= 0)
  {
    printf("De combien de circles souhaitez-vous mesurez la consommation ?\n");
    scanf("%d",nb_circle);
  }
  
   //allocation_adresse_MAC(*nb_circle,&tabMAC);
	if((*tabMAC = malloc((*nb_circle)*sizeof(adresseMAC[TAILLE_ADRESSE_MAC])))==NULL){
    perror("Problème d'allocation mémoire des adresses MAC !\n");
    return exit(EXIT_FAILURE);
}

// adresse(s) MAC des circle
	printf("*** Adresse(s) MAC ***\n");
  	for (i=0 ; i < *nb_circle ; i++){
        #ifdef DEBUG_MODE
            tabMAC[0] = ADRESSE_MAC_CIRCLE1;
            if (nb_circle == 2)
                tabMAC[1] = ADRESSE_MAC_CIRCLE2;
        #else
            printf("Adresse MAC du Circle %d : ",i+1);
            scanf("%s",(*tabMAC)[i]);
        #endif
}
//noms_compteurs_sdk(*nb_circle);
}

void lancement_interface_graphique_sdk(char commande[], char racineSDK[], int *architecture){
  printf("Quel est votre architecture système, 64 ou 32 bits ?\n");
  scanf("%d",architecture);
  if (*architecture==32) // structure 32 bits <=> i386
    *architecture=86;
  
  printf("\n");
  printf("*** Lancement de l'interface graphique du SDK***\n");
  sprintf(commande,"%s/iecsdk/bin/companion_applications/pl_gui_monitor/linux/X%d/pl_gui_monitor --geometry \"gauges=2x2\" /opt/productivity_link/plugwise_*/pl_config.ini &",racineSDK,*architecture);
  system(commande); 
}

unsigned long long mesure_watt(int i, char commande[]){
  FILE *pp;
  char tampon[TAILLE_TAMPON];
  long long output;
  
  // Exécution et écriture de la commande dans le "pipe"
  pp = popen (commande, "r");
  if (pp == NULL){
    perror ("popen error !");
    exit(EXIT_FAILURE);
  }
  
  // Ecriture du résultat de la commande dans le tampon via le "pipe"
  fgets (tampon, sizeof (tampon), pp);
  
  pclose(pp);
  tampon[strlen (tampon) - 1] = '\0';
  output = atoll(tampon);
   
  return (unsigned long long) output;
}

void commande_python(int i, char racinePython[], adresseMAC tabMAC[],char commande[]){
  sprintf(commande,"sudo python %s/pol.py -w %s",racinePython,tabMAC[i]);
} 
