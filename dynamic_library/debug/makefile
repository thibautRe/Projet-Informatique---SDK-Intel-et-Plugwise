all: pol cleanall

pol: pol.o main.o crc.o
	gcc -Wall -o pol pol.o main.o crc.o
crc.o: crc.c crc.h
	gcc -Wall -o crc.o -c crc.c 
pol.o: pol.c pol.h crc.h
	gcc -Wall -o pol.o -c pol.c
main.o: main.c pol.h crc.h
	gcc -Wall -o main.o -c main.c
clean:
	rm *~ 
cleanall: clean
	rm *.o