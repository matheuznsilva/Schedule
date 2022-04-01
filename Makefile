main:	main.o	login.o	funcoes.o	ListaDinEncadDupla.o
	gcc main.o login.o funcoes.o	ListaDinEncadDupla.o -o main

main.o:	main.c
	gcc -c main.c

login.o:	login.c	login.h
	gcc -c login.c

funcoes.o:	funcoes.c	funcoes.h
	gcc -c funcoes.c

ListaDinEncadDupla.o:	ListaDinEncadDupla.c	ListaDinEncadDupla.h
	gcc -c ListaDinEncadDupla.c

clean:
	rm *.o

run:
	./main