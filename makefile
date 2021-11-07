#makefile

COMMON = ./src/common
INCLUDE_COMMON = ./include/common

INPUT_FILE ?= ./examples/Datasets/input_small_id
QUERY_FILE ?= ./examples/Datasets/query_small_id
OUTPUT_FILE ?= results

DEF_ARGS ?= -i $(INPUT_FILE) -o $(OUTPUT_FILE) -q $(QUERY_FILE) 
CLUSTER_ARGS ?= -i $(INPUT_FILE) -o $(OUTPUT_FILE)

CC			= g++
CFLAGS = -g -I$(INCLUDE_COMMON)
DEBUGFLAGS = -g -Wextra -Wall -I$(INCLUDE_COMMON)

all: compile_lsh	\
	compile_cube	\
	compile_cluster

#LSH
compile_lsh: clean
	$(CC) ./src/lsh/main_lsh.cpp ./src/lsh/lsh.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/lsh -I./include/lsh $(CFLAGS)

run_lsh:
	./bin/lsh $(DEF_ARGS)

lsh: compile_lsh run_lsh

#CUBE
compile_cube: clean
	$(CC) ./src/cube/main_cube.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/cube -I./include/cube $(CFLAGS)

run_cube: 
	./bin/cube $(DEF_ARGS)

cube: compile_cube run_cube

#CLUSTER
compile_cluster: clean
	$(CC) ./src/cluster/main_cluster.cpp ./src/cluster/cluster.cpp ./src/lsh/lsh.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/cluster $(CFLAGS) -I./include/lsh -I./include/cube

run_cluster: 
	./bin/cluster $(CLUSTER_ARGS)

cluster: compile_cluster run_cluster


clean:
	rm -f ./bin/cluster
	rm -f ./bin/cube
	rm -f ./bin/lsh
