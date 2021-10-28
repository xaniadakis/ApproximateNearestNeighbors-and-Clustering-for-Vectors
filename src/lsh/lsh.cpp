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