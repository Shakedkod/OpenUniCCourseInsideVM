COMP = gcc
FLAGS = -g -ansi -pedantic -Wall
OBJECTS = assembler.o coms.o macro.o file.o command.o workshop_macro.o
TARGET = assembler

$(TARGET): $(OBJECTS)
	$(COMP) -g $(FLAGS) $(OBJECTS) -o $(TARGET)

# MAIN FILES
timediff.o: assembler.c
	$(COMP) -c $(FLAGS) assembler.c -o assembler.o
coms.o: coms.c coms.h
	$(COMP) -c $(FLAGS) coms.c -o coms.o

# WORKSHOPS
workshop_macro.o: macro_workshop.c macro_workshop.h
	$(COMP) -c $(FLAGS) macro_workshop.c -o workshop_macro.o

# TYPES
macro.o: types/macro.c types/macro.h
	$(COMP) -c $(FLAGS) types/macro.c -o macro.o
file.o: types/file.c types/file.h
	$(COMP) -c $(FLAGS) types/file.c -o file.o
command.o: types/command.c types/command.h
	$(COMP) -c $(FLAGS) types/command.c -o command.o