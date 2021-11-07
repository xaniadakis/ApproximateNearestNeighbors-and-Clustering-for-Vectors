#Makefile
#make (lsh/cube/cluster) (run RUN_TARGET=lsh/cube/cluster ARGS="{arguments}") (clean)
all : lsh cube cluster

lsh: PROGRAM=lsh
cube: PROGRAM = cube
cluster: PROGRAM = cluster

MODULES = ./src/$(PROGRAM)
COMMON = ./src/common
BIN_TARGET = ./bin/$(PROGRAM)
INCLUDE = ./include/$(PROGRAM)
INCLUDE_COMMON = ./include/common

clean : BIN_TARGET = ./bin/lsh ./bin/cube ./bin/cluster

CFLAGS = -g -I$(INCLUDE) -I$(INCLUDE_COMMON)
DEBUGFLAGS = -g -Wextra -Wall -I$(INCLUDE) -I$(INCLUDE_COMMON)

lsh: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS)

cube: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS)

cluster: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(MODULES)/$(PROGRAM)_ANN.cpp ./src/lsh/lsh.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS) -I./include/lsh -I./include/cube

clean:
	rm -f $(BIN_TARGET)


--check_run:
ifndef RUN_TARGET
	$(error RUN_TARGET is undefined)
endif
run: --check_run
	./bin/$(RUN_TARGET) $(ARGS)