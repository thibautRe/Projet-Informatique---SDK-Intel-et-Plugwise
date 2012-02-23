IECSDK_ROOT=/home/telecom_sudparis/projet_informatique/iecsdk

CFLAGS=-I$(IECSDK_ROOT)/src/core_api -Wall
LDFLAGS=-L$(IECSDK_ROOT)/build/linux -lproductivity_link

all : hello_world

hello_world : hello_world.o
	gcc $(CFLAGS) $(LDFLAGS) hello_world.o -o hello_world
hello_world.o : hello_world.c
	gcc $(CFLAGS) -c hello_world.c
