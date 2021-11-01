#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <map>
#include "utils.hpp"
#include "hash_functions.hpp"
#include "hash_table.hpp"

using namespace std;

#include <iostream>

#define L2 2

struct hashtable_item_cube
{
	vector<float> p;
	int index;
};

class cube
{

private:

	int n;//Number of vectors
	int tableSize;
	int vectorSize;

	vector<float> *vectors;//Vectors from dataset
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

	cube(string input_file,int k,string metric);//Constructor
	~cube();//Destructor
	void query(string query_file,string output_file,int N,int R);
};
