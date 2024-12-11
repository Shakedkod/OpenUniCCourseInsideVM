adjacency: adjacency.o adjmat.o
	gcc -g -ansi -pedantic -Wall adjacency.o adjmat.o -o adjacency

adjmat.o: adjmat.c constants.h
	gcc -c adjmat.c -o adjmat.o
adjacency.o: adjacency.c constants.h adjmat.h
	gcc -c adjacency.c -o adjacency.o