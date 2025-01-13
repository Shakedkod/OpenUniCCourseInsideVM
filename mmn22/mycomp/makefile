mycomp: mycomp.o complex.o coms.o user_interface.o string_manipulation.o
	gcc -g -ansi -pedantic -Wall mycomp.o user_interface.o string_manipulation.o complex.o coms.o -o mycomp -lm

mycomp.o: mycomp.c
	gcc -c mycomp.c -o mycomp.o
user_interface.o: user_interface.c user_interface.h
	gcc -c user_interface.c -o user_interface.o
string_manipulation.o: string_manipulation.c string_manipulation.h
	gcc -c string_manipulation.c -o string_manipulation.o
coms.o: coms.c coms.h
	gcc -c coms.c -o coms.o
complex.o: complex.c complex.h
	gcc -c complex.c -o complex.o -lm