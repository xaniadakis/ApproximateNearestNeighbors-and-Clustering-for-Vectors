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

INPUT_FILE ?= ./examples/Datasets/input_small_id
QUERY_FILE ?= ./examples/Datasets/query_small_id
OUTPUT_FILE ?= results

CFLAGS = -g -I$(INCLUDE) -I$(INCLUDE_COMMON)
DEBUGFLAGS = -g -Wextra -Wall -I$(INCLUDE) -I$(INCLUDE_COMMON)

all: $(BIN_TARGET) run 

lsh: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS)
	$(BIN_TARGET) -i $(INPUT_FILE) -q $(QUERY_FILE) -o $(OUTPUT_FILE)

cube: clean 
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS)
	$(BIN_TARGET) -i $(INPUT_FILE) -q $(QUERY_FILE) -o $(OUTPUT_FILE) -k 14 -M 10 -probes 2  -N 1 -R 10000
# valgrind --leak-check=full \
# 		--show-leak-kinds=all \
# 		--track-origins=yes \
# 		--verbose \
# 		$(BIN_TARGET) -i $(INPUT_FILE) -q $(QUERY_FILE) -o $(OUTPUT_FILE) -k 14 -M 10 -probes 2  -N 1 -R 10000

cluster: clean
	g++ $(MODULES)/main_$(PROGRAM).cpp $(MODULES)/$(PROGRAM).cpp ./src/lsh/lsh.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o $(BIN_TARGET) $(CFLAGS) -I./include/lsh -I./include/cube

clean:
	rm -fr $(BIN_TARGET)
	mkdir ./bin

run: 
	$(BIN_TARGET) -i $(INPUT_FILE) -q $(QUERY_FILE) -o $(OUTPUT_FILE)
#$(ARGS)