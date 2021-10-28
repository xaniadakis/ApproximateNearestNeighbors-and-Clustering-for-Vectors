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
	int index;
};

class LSH
{
private:
	int n;//Number of vectors
	int tableSize;
	int vectorSize;

	vector<float> *vectors;//Vectors from dataset
	vector<string> ids;//Ids of vectors from dataset

	float (*distance)(vector<float>, vector<float>);//Distance function

	unordered_map<unsigned int, hashtable_item> *hashtables;//Hashtables
	int L;//Number of hashtables
	int k;//Number of hash functions

	vector<int> r;//r vector used by g
	vector<float> **v;//Random vector used by hash function
	float **t;//Random number used by hash function
	unsigned int w;//Window used by hash function
	unsigned int M = UINT32_MAX - 4;//M used by g

	unsigned int g(vector<float> p,unsigned int j);
	unsigned int ID(vector<float> p,unsigned int j);
	
public:
	LSH(string input_file,int k,int L,float (* metric)(vector<float>,vector<float>))//Constructor
	{
		//Initialize values
		LSH::L=L;
		hashtables = new unordered_map<unsigned int, hashtable_item>[L];
		LSH::k=k;
		read_file(input_file,vectors,ids);
		w=uniform_distribution_rng(0,6);
		vectorSize=vectors[0].size();
		n=ids.size();
		tableSize=n/4;
		v = new vector<float>*[L];
		t = new float*[L];

		for (int x = 0; x < k; x++)
		{
			r.push_back(uniform_distribution_rng(0,INT32_MAX));
		}
		for (int i = 0; i < L; i++)
		{
			v[i] = new vector<float>[k];
			t[i] = new float[k];
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
		for(int i = 0;i<n;i++)
		{
			for(int y=0;y<L;y++)
			{
				hashtable_item p{vectors[i],ID(vectors[i],y),i};
				hashtables[y].insert({modulo(p.ID,tableSize),p});
			}
		}
	};
	~LSH()//Destructor
	{
	};

	void query(string query_file,string output_file,int N,int R);
};