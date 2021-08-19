main:	main.o	ListaDinEncadDupla.o	funcoes.o	quickSort.o
	gcc main.o ListaDinEncadDupla.o	funcoes.o quickSort.o -o main

main.o:	main.c
	gcc -c main.c

quickSort.o:	quickSort.c	quickSort.h
	gcc -c quickSort.c

ListaDinEncadDupla.o:	ListaDinEncadDupla.c	ListaDinEncadDupla.h
	gcc -c ListaDinEncadDupla.c

funcoes.o:	funcoes.c	funcoes.h
	gcc -c funcoes.c
	
clean:
	rm *.o