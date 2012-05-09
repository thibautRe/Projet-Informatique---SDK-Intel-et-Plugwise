all : configurations

configurations : configurations.o configuration_management.o memory_allocation.o
	gcc -Wall -o configurations configurations.o configuration_management.o memory_allocation.o

configurations.o : configurations.c constants.h configuration_management.h memory_allocation.h
	gcc -Wall -c configurations.c

configuration_management.o : configuration_management.c constants.h configuration_management.h memory_allocation.h
	gcc -Wall -c configuration_management.c

memory_allocation.o : memory_allocation.c constants.h memory_allocation.h
	gcc -Wall -c memory_allocation.c