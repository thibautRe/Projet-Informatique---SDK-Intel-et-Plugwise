#include "fonctions.h"

void initialiser_chemin_python(char racinePython[]){
  printf("Dans quel répertoire est situé votre fichier pol.py ?\n");
  scanf("%s",racinePython);
}

void initialiser_plugwise(char racinePython[],int *nb_circles, AdresseMAC *tabMAC[], char **counters_names[]){
  int i;
  
  while (*nb_circles <= 0){
    printf("De combien de circles souhaitez-vous mesurez la consommation ?\n");
    scanf("%d",nb_circles);
  }
  
  // Allocation mémoire :
  allocation_dynamique_adresses_mac(*nb_circles,tabMAC);
  allocation_dynamique_noms_compteurs(*nb_circles,counters_names);
  
  // Enregistrement des noms et des adresses MAC des circles
  for (i=0 ; i < *nb_circles ; i++){
    printf(" * Nom du circle %d : ",i+1);
    scanf("%s",(*counters_names)[2*i]);
    sprintf((*counters_names)[2*i+1],"%s.decimals",(*counters_names)[2*i]);
    
    printf(" * Adresse MAC de %s : ",(*counters_names)[2*i]);
    scanf("%s",(*tabMAC)[i]);
  }
}

void lancement_interface_graphique_sdk(char racineSDK[], char strUUID[],int *architecture, int *pid_pl_gui_monitor){
  char processus[TAILLE_PROCESSUS]="pl_gui_monitor";
  char commande[TAILLE_COMMANDE];
  
  printf("Quel est votre architecture système, 64 ou 32 bits ?\n");
  scanf("%d",architecture);
  if (*architecture==32) // structure 32 bits <=> i386
    *architecture=86;
  sprintf(commande,"xterm -ge 50x13 -iconic -bg black -fg white -title \"PL GUI MONITOR\" -name \"PL GUI MONITOR\" -e \"%s/bin/companion_applications/pl_gui_monitor/linux/X%d/pl_gui_monitor --process --geometry \"gauges=2x2\" /opt/productivity_link/plugwise_%s/pl_config.ini\" &",racineSDK,*architecture,strUUID);

  system(commande); 
  *pid_pl_gui_monitor=recuperer_pid(processus);
}

void lancement_pl_csv_logger_sdk(char racineSDK[], char strUUID[], int *pid_pl_csv_logger){
  char processus[TAILLE_PROCESSUS]="pl_csv_logger";
  char commande[TAILLE_COMMANDE];		
  
  sprintf(commande,"xterm -ge 75x11 -iconic -bg yellow -fg blue -fn 7x13bold -title \"PL CSV LOGGER\" -name \"PL CSV LOGGER\" -e \"%s/build/linux/pl_csv_logger /opt/productivity_link/plugwise_%s/pl_config.ini >> ~/Bureau/valeurs_plugwise_%s.csv\" &",racineSDK,strUUID,strUUID);
 
  system(commande);
  *pid_pl_csv_logger=recuperer_pid(processus);
}

double mesure_watt(char commande[]){
  FILE *pp;
  char tampon[TAILLE_TAMPON];
  double output;
  
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
  output = atof(tampon);
  return output;
}

void commande_python(int i, char racinePython[], AdresseMAC tabMAC[],char commande[]){
  sprintf(commande,"sudo python %s/pol.py -w %s 2> /dev/null",racinePython,tabMAC[i]);
} 

int recuperer_pid(char processus[]){
  FILE *pp=NULL;
  char tampon[TAILLE_TAMPON];
  char buffer[TAILLE_TAMPON];
  int pid=0;
  
  sprintf(tampon,"ps -e | grep %s | tail -1 | cut -f2 -d' '",processus);
  

  sleep(1);  // il faut être sur que le processus soit bien lancé
  while(pid == 0){
    // Exécution et écriture de la commande dans le "pipe"
    pp = popen (tampon, "r");
    if (pp == NULL){
      perror ("popen error !");
      exit(EXIT_FAILURE);
    }
    
    // Ecriture du résultat de la commande dans le tampon via le "pipe"
    fgets (buffer,sizeof(buffer), pp);
    buffer[strlen (buffer) - 1] = '\0';
    pclose(pp);
    
    pid = atoi(buffer);
  }
  
  return pid;
} 



