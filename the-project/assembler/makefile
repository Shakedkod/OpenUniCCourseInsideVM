COMP = gcc
FLAGS = -g -ansi -pedantic -Wall
OBJECTS = assembler.o coms.o macro.o file.o command.o preprocessor.o
TARGET = assembler

$(TARGET): $(OBJECTS)
	$(COMP) -g $(FLAGS) $(OBJECTS) -o $(TARGET)

# MAIN FILES
assembler.o: assembler.c
	$(COMP) -c $(FLAGS) assembler.c -o assembler.o
coms.o: coms.c coms.h
	$(COMP) -c $(FLAGS) coms.c -o coms.o

# WORKSHOPS
preprocessor.o: preprocessor.c preprocessor.h
	$(COMP) -c $(FLAGS) preprocessor.c -o preprocessor.o

# TYPES
macro.o: types/macro.c types/macro.h
	$(COMP) -c $(FLAGS) types/macro.c -o macro.o
file.o: types/file.c types/file.h
	$(COMP) -c $(FLAGS) types/file.c -o file.o
command.o: types/command.c types/command.h
	$(COMP) -c $(FLAGS) types/command.c -o command.o