#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#include "utils.hpp"
#include "hash_functions.hpp"

using namespace std;

#include <iostream>

struct hashtable_item
{
	vector<float> p;
	unsigned int ID;
};

class LSH
{
private:
	int n;//Number of vectors
	int tableSize;
	int vectorSize;

	vector<float> *vectors;
	vector<string> ids;

	float (*distance)(vector<float>, vector<float>);//Distance function

	unordered_map<int, hashtable_item> *hashtables;
	int num_hashtables;
	int k;

	vector<int> r;
	vector<float> **v;
	float **t;
	int w=uniform_distribution_rng(0,6);
	unsigned int M = UINT32_MAX - 4;

	unsigned int g(vector<float> p,unsigned int j);
	unsigned int ID(vector<float> p,unsigned int j);
	
public:
	LSH(string input_file,int k,int L,float (* metric)(vector<float>,vector<float>))//Constructor
	{
		num_hashtables=L;
		hashtables = new unordered_map<int, hashtable_item>[L];
		k=k;
		read_file(input_file,vectors,ids);
		vectorSize=vectors[0].size();
		n=ids.size();
		tableSize=n/4;
		v = new vector<float>*[L];
		t = new float*[L];
		for (int i = 0; i < L; i++)
		{
			v[i] = new vector<float>[k];
			t[i] = new float[k];
		}
		for (int i = 0; i < num_hashtables; i++)
		{
			r.push_back(uniform_distribution_rng(0,INT32_MAX));
			for (int x = 0; x < k; x++)
			{
				t[i][x]=uniform_distribution_rng(0,w-1);
				for (int y = 0; y < vectorSize; y++)
				{
					v[i][x].push_back(normal_distribution_rng());
				}
			}
		}
		distance=metric;

		//Add vectors to L hashtables
	};
	~LSH()//Destructor
	{
	};
	void query(string query_file,string output_file,int N,int R);
};