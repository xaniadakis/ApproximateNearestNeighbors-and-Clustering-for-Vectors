#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <map>

#include "exhaustive_search.hpp"
#include "utils.hpp"
#include "hash_functions.hpp"
#include "hash_table.hpp"

using namespace std;

#define L2 2

class Cube
{

private:

	struct hashtable_item_cube
	{
		vector<float> p;
		int index;
	};

	int n;//Number of vectors
	int tableSize;
	int vectorSize;

	vector<vector<float>> vectors;//Vectors from dataset
	vector<string> ids;//Ids of vectors from dataset

	float (*distance)(vector<float>, vector<float>);//Distance function
	hash_table<hashtable_item_cube> *hypercube;
	// unordered_map<unsigned int, hashtable_item> *hypercube;
	int k;//Number of hash functions

	vector<float> *v;//Random vector used by hash function
	float *t;//Random number used by hash function
	unsigned int w;//Window used by hash function
	map<int, int> *f_table;

	unsigned int f(int i, int h_p);
	unsigned int F(vector<float> p);

public:

	Cube(vector<vector<float>> input_vectors,vector<string> input_ids,int k,int metric);
	~Cube();//Destructor
	vector<pair<float,unsigned int>> find_N_nearest(vector<float> p,unsigned int N);
	vector<pair<float,unsigned int>> find_R_nearest(vector<float> p,int R);
};
