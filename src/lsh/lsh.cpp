#include "lsh.hpp"
#include <math.h>
#include <numeric>

unsigned int LSH::g(vector<float> p,unsigned int j){
	return modulo(ID(p,j),tableSize);
}

unsigned int LSH::ID(vector<float> p,unsigned int j) {
	int *h = new int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash_L2(i,p,v[j],t[j],w),M);
	long long int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(_g,M);
}

void LSH::query(string query_file,string output_file,int N,int R)
{
	vector<float> *vectors_query;
	vector<string> ids_query;
	read_file(query_file,vectors_query,ids_query);

	unsigned int n_query=ids_query.size();

	for (int i=0 ; i<n_query ; i++)
	{
		vector<float> p = vectors_query[i];
		for (int y=0 ; y<L ; y++)
		{
			unsigned int ID = LSH::ID(vectors[i],y);
			for (auto it = hashtables[y].begin(modulo(ID,tableSize)); it != hashtables[y].end(modulo(ID,tableSize)); ++it )
			{
				hashtable_item p_b = it->second;
				if (p_b.ID == ID)
				{
					
				}
			}
		}
	}
};

void LSH::LSH(string input_file,int k,int L,float (* metric)(vector<float>,vector<float>))
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

void LSH::~LSH()//Destructor
{
	return;
};