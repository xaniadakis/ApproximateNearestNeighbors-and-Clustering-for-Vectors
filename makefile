#Makefile

PROGRAM = lsh

MODULES = ./src/$(PROGRAM)
COMMON = ./src/common
BIN_TARGET = ./bin/$(PROGRAM)
INCLUDE = ./include/$(PROGRAM)
INCLUDE_COMMON = ./include/common

CFLAGS = -g -Wextra -Wall -I$(INCLUDE) -I$(INCLUDE_COMMON)

$(BIN_TARGET): clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS) 

clean:
	rm -f $(BIN_TARGET)

run: $(BIN_TARGET)
	$(BIN_TARGET) $(ARGS)