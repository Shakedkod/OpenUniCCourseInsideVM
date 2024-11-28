output: main_program.o part1.o part2.o
	gcc -ansi -pedantic -Wall main_program.o part1.o part2.o -o output

main_program.o: main_program.c
	gcc -c -ansi -pedantic -Wall main_program.c -o main_program.o

part1.o: part1.h part1.c
	gcc -c -ansi -pedantic -Wall part1.c -o part1.o

part2.o: part2.h part2.c
	gcc -c -ansi -pedantic -Wall part2.c -o part2.o