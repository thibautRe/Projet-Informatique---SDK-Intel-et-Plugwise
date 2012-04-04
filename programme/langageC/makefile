IECSDK_ROOT=/home/thibaut/Projet_Info/iecsdk

CFLAGS=-I$(IECSDK_ROOT)/src/core_api -Wall
LDFLAGS=-L$(IECSDK_ROOT)/build/linux -lproductivity_link

all : plugSdk clean

plugSdk : plugSdk.o fonctions.o affichage.o pol.o
	gcc $(CFLAGS) plugSdk.o fonctions.o affichage.o pol.o -o plugSdk $(LDFLAGS)

plugSdk.o : plugSdk.c fonctions.h
	gcc $(CFLAGS) -c plugSdk.c

fonctions.o : fonctions.c fonctions.h
	gcc -Wall -c fonctions.c

affichage.o : affichage.c affichage.h
	gcc -Wall -c affichage.c

pol.o : pol.c pol.h
	gcc -Wall -c pol.c

clean :
	rm *.o *~
