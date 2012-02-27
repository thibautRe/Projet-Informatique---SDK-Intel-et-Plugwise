IECSDK_ROOT=/home/telecom_sudparis/projet_informatique/iecsdk

CFLAGS=-I$(IECSDK_ROOT)/src/core_api -Wall
LDFLAGS=-L$(IECSDK_ROOT)/build/linux -lproductivity_link

all : main

main : main.o
	gcc $(CFLAGS) $(LDFLAGS) main.o -o main
main.o : main.c
	gcc $(CFLAGS) -c main.c
