#makefile
COMMON 			?= ./src/common
INCLUDE_COMMON 	?= ./include/common

INPUT_FILE 		?= ./examples/Datasets/input_small_id
QUERY_FILE 		?= ./examples/Datasets/query_small_id
OUTPUT_FILE 	?= results
CONGIF_FILE		?= ./examples/cluster_example.conf

CUBE_ARGS 		?= -i $(INPUT_FILE) -o cube_$(OUTPUT_FILE) -q $(QUERY_FILE) 
LSH_ARGS 		?= -i $(INPUT_FILE) -o lsh_$(OUTPUT_FILE) -q $(QUERY_FILE) 
CLUSTER_METHOD	?= Classic
CLUSTER_ARGS 	?= -i $(INPUT_FILE) -o cluster_$(OUTPUT_FILE) -c $(CONGIF_FILE) -m $(CLUSTER_METHOD) -complete 

CC				= g++
CFLAGS 			?= -I$(INCLUDE_COMMON) -O2
DEBUGFLAGS 		?= -g -Wextra -Wall -I$(INCLUDE_COMMON)

all: compile_lsh compile_cube compile_cluster

#LSH
clean_lsh:
	rm -f ./bin/lsh

compile_lsh: clean_lsh mkdir
	$(CC) ./src/lsh/main_lsh.cpp ./src/lsh/lsh.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/lsh -I./include/lsh $(CFLAGS)

run_lsh:
	./bin/lsh $(LSH_ARGS)

compile_debug_lsh:
	$(CC) ./src/lsh/main_lsh.cpp ./src/lsh/lsh.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/lsh -I./include/lsh $(DEBUGFLAGS)

gdb_lsh: compile_debug_lsh
	gdb --args ./bin/lsh $(LSH_ARGS)

valgrind_lsh: compile_debug_lsh
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out-lsh.txt \
			./bin/lsh $(LSH_ARGS)

lsh: compile_lsh run_lsh

#CUBE
clean_cube:
	rm -f ./bin/cube

compile_cube: clean_cube mkdir
	$(CC) ./src/cube/main_cube.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/cube -I./include/cube $(CFLAGS)

run_cube: 
	./bin/cube $(CUBE_ARGS)

compile_debug_cube:
	$(CC) ./src/cube/main_cube.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/cube -I./include/cube $(DEBUGFLAGS)

gdb_cube: compile_debug_cube
	gdb --args 	./bin/cube $(CUBE_ARGS)

valgrind_cube: compile_debug_cube
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out-cube.txt \
			./bin/cube $(CUBE_ARGS)

cube: compile_cube run_cube

#CLUSTER
clean_cluster:
	rm -f ./bin/cluster

compile_cluster: clean_cluster mkdir
	$(CC) ./src/cluster/main_cluster.cpp ./src/cluster/cluster.cpp ./src/cluster/cluster_ANN.cpp ./src/lsh/lsh.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/cluster $(CFLAGS) -I./include/cluster -I./include/lsh -I./include/cube

run_cluster: 
	./bin/cluster $(CLUSTER_ARGS)

compile_debug_cluster:
	$(CC) ./src/cluster/main_cluster.cpp ./src/cluster/cluster.cpp ./src/cluster/cluster_ANN.cpp ./src/lsh/lsh.cpp ./src/cube/cube.cpp $(COMMON)/hash_functions.cpp $(COMMON)/utils.cpp $(COMMON)/exhaustive_search.cpp -o ./bin/cluster $(DEBUGFLAGS) -I./include/cluster -I./include/lsh -I./include/cube

gdb_cluster: compile_debug_cluster
	gdb --args ./bin/cluster $(CLUSTER_ARGS)

valgrind_cluster: compile_debug_cluster
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out-cluster.txt \
			./bin/cluster $(CLUSTER_ARGS)

cluster: compile_cluster run_cluster

#DIRS
mkdir:
	mkdir -p ./bin

cleanall: clean_lsh clean_cube clean_cluster
