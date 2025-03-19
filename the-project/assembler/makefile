COMP = gcc
FLAGS = -g -ansi -pedantic -Wall
OBJECTS = object/assembler.o object/coms.o object/address.o object/command.o object/data.o object/directive.o object/entry.o object/external.o object/file.o object/macro.o object/symbol.o object/preprocessor.o object/pass_one.o object/pass_two.o
TARGET = assembler

$(TARGET): $(OBJECTS)
	$(COMP) -g $(FLAGS) $(OBJECTS) -o $(TARGET)

# MAIN FILES
object/assembler.o: assembler.c
	$(COMP) -c $(FLAGS) assembler.c -o object/assembler.o
object/coms.o: coms.c coms.h
	$(COMP) -c $(FLAGS) coms.c -o object/coms.o

# ASSEMBLER STAGES
object/preprocessor.o: preprocessor.c preprocessor.h
	$(COMP) -c $(FLAGS) preprocessor.c -o object/preprocessor.o
object/pass_one.o: pass_one.c pass_one.h
	$(COMP) -c $(FLAGS) pass_one.c -o object/pass_one.o
object/pass_two.o: pass_two.c pass_two.h
	$(COMP) -c $(FLAGS) pass_two.c -o object/pass_two.o

# TYPES
object/address.o: types/address.c types/address.h
	$(COMP) -c $(FLAGS) types/address.c -o object/address.o
object/command.o: types/command.c types/command.h
	$(COMP) -c $(FLAGS) types/command.c -o object/command.o
object/data.o: types/data.c types/data.h
	$(COMP) -c $(FLAGS) types/data.c -o object/data.o
object/directive.o: types/directive.c types/directive.h
	$(COMP) -c $(FLAGS) types/directive.c -o object/directive.o
object/entry.o: types/entry.c types/entry.h
	$(COMP) -c $(FLAGS) types/entry.c -o object/entry.o
object/external.o: types/external.c types/external.h
	$(COMP) -c $(FLAGS) types/external.c -o object/external.o
object/file.o: types/file.c types/file.h
	$(COMP) -c $(FLAGS) types/file.c -o object/file.o
object/macro.o: types/macro.c types/macro.h
	$(COMP) -c $(FLAGS) types/macro.c -o object/macro.o
object/symbol.o: types/symbol.c types/symbol.h
	$(COMP) -c $(FLAGS) types/symbol.c -o object/symbol.o
