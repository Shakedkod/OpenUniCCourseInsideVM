timediff: timediff.o coms.o user_input.o time.o
	gcc -g -ansi -pedantic -Wall timediff.o coms.o user_input.o time.o -o timediff

timediff.o: timediff.c
	gcc -c timediff.c -o timediff.o
user_input.o: user_input.c user_input.h
	gcc -c user_input.c -o user_input.o
time.o: time.c time.h
	gcc -c time.c -o time.o
coms.o: coms.c coms.h
	gcc -c coms.c -o coms.o