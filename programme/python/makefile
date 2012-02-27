IECSDK_ROOT=/home/telecom_sudparis/projet_informatique/iecsdk

CFLAGS=-I$(IECSDK_ROOT)/src/core_api -Wall
LDFLAGS=-L$(IECSDK_ROOT)/build/linux -lproductivity_link

all : mainPython

mainPython : mainPython.o
	gcc $(CFLAGS) $(LDFLAGS) mainPython.o -o mainPython
mainPython.o : mainPython.c
	gcc $(CFLAGS) -c mainPython.c
