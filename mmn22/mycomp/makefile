mycomp: mycomp.o complex.o
	gcc -g -ansi -pedantic -Wall mycomp.o complex.o -o mycomp -lm

mycomp.o: mycomp.c
	gcc -c mycomp.c -o mycomp.o
complex.o: complex.c complex.h
	gcc -c complex.c -o complex.o -lm