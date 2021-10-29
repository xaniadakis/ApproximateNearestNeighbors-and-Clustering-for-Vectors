#include "cube.hpp"
#include <math.h>
#include <numeric>
#include <map>
#include <utils.hpp>

unsigned int cube::g(vector<float> p,unsigned int j){
	return modulo(ID(p,j),tableSize);
}

unsigned int cube::ID(vector<float> p,unsigned int j) {
	int *h = new int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash_L2(i,p,v[j],t[j],w),M);
	long long int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(_g,M);
}

unsigned int cube::f(int i, int h_p) {
	int _f = rand() % 2;
	if (notExists(f_table[i], h_p) {
		f_table[i].insert(pair<int,int>(h_p, _f));
		return _f;
	} 
	else 
		return getValue(f_table[i], h_p);
}

void cube::query(string query_file,string output_file,int N,int R)
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
			unsigned int ID = cube::ID(vectors[i],y);
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

cube::cube(string input_file,int k,float (* metric)(vector<float>,vector<float>))
{
	//Initialize values
	cube::k=k;
	read_file(input_file,vectors,ids);
	f_table = new map<int, int>[k];
	w=uniform_distribution_rng(0,6);
	vectorSize=vectors[0].size();
	n=ids.size();
	tableSize=n/4;
	v = new vector<float>[k];
	t = new float*[k];

	for (int i = 0; i < k; i++)
	{
		v[i].push_back(normal_distribution_rng());
		t[i] = uniform_distribution_rng(0,w-1);
	}

	distance=metric;

};

cube::~cube()//Destructor
{
	return;
};
