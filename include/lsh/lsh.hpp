#pragma once

#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#include "hash_functions.hpp"
#include "exhaustive_search.hpp"
#include "utils.hpp"
#include "hash_table.hpp"

using namespace std;

#include <iostream>

struct hashtable_item
{
	vector<float> p;
	unsigned long long int ID;
	int index;
};

template class hash_table<hashtable_item>;

class LSH
{

private:

	int n;//Number of vectors
	int tableSize;
	int vectorSize;

	vector<float> *vectors;//Vectors from dataset
	vector<string> ids;//Ids of vectors from dataset

	float (*distance)(vector<float>, vector<float>);//Distance function

	hash_table<hashtable_item> *hashtables;//Hashtables
	int L;//Number of hashtables
	int k;//Number of hash functions

	vector<int> r;//r vector used by g
	vector<float> **v;//Random vector used by hash function
	float **t;//Random number used by hash function
	unsigned int w;//Window used by hash function
	unsigned int M = UINT32_MAX - 4;//M used by g

	unsigned int g(vector<float> p,unsigned int j);
	unsigned long long int ID(vector<float> p,unsigned int j);
	
public:

	LSH(string input_file,int k,int L,float (* metric)(vector<float>,vector<float>));//Constructor
	~LSH();//Destructor
	void query(string query_file,string output_file,unsigned int N,int R);
};