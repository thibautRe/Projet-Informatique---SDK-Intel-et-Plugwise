IECSDK_ROOT=/home/telecom_sudparis/projet_informatique/iecsdk

CFLAGS=-I$(IECSDK_ROOT)/src/core_api -Wall
LDFLAGS=-L$(IECSDK_ROOT)/build/linux -lproductivity_link

all : plugSdk

plugSdk : plugSdk.o fonctions.o
	gcc $(CFLAGS) plugSdk.o fonctions.o -o plugSdk $(LDFLAGS)
plugSdk.o : plugSdk.c fonctions.h
	gcc $(CFLAGS) -c plugSdk.c
fonctions.o : fonctions.c fonctions.h
	gcc -Wall -c fonctions.c
