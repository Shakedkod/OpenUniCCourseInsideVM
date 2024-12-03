linked_list: linked_list.o list.o
	gcc -g -ansi -pedantic -Wall linked_list.o list.o -o linked_list

linked_list.o: linked_list.c
	gcc -c linked_list.c -o linked_list.o

list.o: list.c list.h
	gcc -c list.c -o list.o