#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <map>
#include "utils.hpp"
#include "hash_functions.hpp"

using namespace std;

#include <iostream>

struct hashtable_item
{
	vector<float> p;
	unsigned int ID;
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

	unordered_map<unsigned int, hashtable_item> hypercube;
	int k;//Number of hash functions

	vector<float> *v;//Random vector used by hash function
	float *t;//Random number used by hash function
	unsigned int w;//Window used by hash function
	map<int, int> *f_table;

	unsigned int f(int i);
	
public:

	cube(string input_file,int k,float (* metric)(vector<float>,vector<float>));//Constructor
	~cube();//Destructor
	void query(string query_file,string output_file,int N,int R);
};
