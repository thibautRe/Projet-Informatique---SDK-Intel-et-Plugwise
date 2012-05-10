IECSDK_ROOT=/home/nicolas/iecsdk

CC=gcc
CFLAGS=-g -I$(IECSDK_ROOT)/src/core_api -Wall
LDFLAGS=-g -L$(IECSDK_ROOT)/build/linux -lproductivity_link
EXEC=plugSdk

all : $(EXEC)


plugSdk : plugSdk.o fonctions.o gestion_configurations.o allocation_memoire.o affichage.o
	$(CC) -o $@ $^ $(LDFLAGS)

plugSdk.o : plugSdk.c constantes.h fonctions.h gestion_configurations.h allocation_memoire.h affichage.h
	$(CC) -g -c $< -D RACINE_SDK=\"$(IECSDK_ROOT)\" $(CFLAGS)

fonctions.o : fonctions.c constantes.h fonctions.h allocation_memoire.h
	$(CC) -g -c $<

gestion_configurations.o : gestion_configurations.c constantes.h gestion_configurations.h allocation_memoire.h
	$(CC) -g -c $<

allocation_memoire.o : allocation_memoire.c constantes.h allocation_memoire.h
	$(CC) -g -c $<

affichage.o : affichage.c affichage.h
	$(CC) -g -c $<

pol.o : pol.c pol.h
	$(CC) -g -c $<

clean_o :
	rm *.o

clean : clean_o
	rm $(EXEC)



