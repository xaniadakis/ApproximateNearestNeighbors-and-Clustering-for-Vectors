#Makefile
all : lsh cube cluster

lsh: PROGRAM = lsh
cube: PROGRAM = cube
cluster: PROGRAM = cluster

MODULES = ./src/$(PROGRAM)
COMMON = ./src/common
BIN_TARGET = ./bin/$(PROGRAM)
INCLUDE = ./include/$(PROGRAM)
INCLUDE_COMMON = ./include/common

CFLAGS = -g -I$(INCLUDE) -I$(INCLUDE_COMMON)
DEBUGFLAGS = -g -Wextra -Wall -I$(INCLUDE) -I$(INCLUDE_COMMON)

all: $(BIN_TARGET) run 

lsh: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp $(COMMON)/hash_table.cpp -o $(BIN_TARGET) $(CFLAGS)

cube: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp -o $(BIN_TARGET) $(CFLAGS)

cluster: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp -o $(BIN_TARGET) $(CFLAGS)

clean:
	rm -fr $(BIN_TARGET)

run: 
	$(BIN_TARGET) $(ARGS)