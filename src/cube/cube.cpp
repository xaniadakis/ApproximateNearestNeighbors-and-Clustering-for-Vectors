#include "cube.hpp"
#include <math.h>
#include <numeric>
#include <map>
#include <utils.hpp>
#include <unordered_map>
#define M 4294967291

unsigned int cube::f(int i, int h_p) {
	int _f = rand() % 2;
	if (notExists(f_table[i], h_p)) {
		f_table[i].insert(pair<int,int>(h_p, _f));
		return _f;
	} 
	else 
		return getValue(f_table[i], h_p);
}

unsigned int cube::F(vector<float> p){
	string _F;
	for(int i=0; i<k; i++)
		_F.push_back( f(i, modulo( hash_L2(i,p,v,t,w) ,M)));
	return binaryToDecimal(_F);
}

// void cube::query(string query_file,string output_file,int N,int R)
// {
// 	vector<float> *vectors_query;
// 	vector<string> ids_query;
// 	read_file(query_file,vectors_query,ids_query);

// 	unsigned int n_query=ids_query.size();

// 	for (int i=0 ; i<n_query ; i++)
// 	{
// 		vector<float> p = vectors_query[i];
// 		for (int y=0 ; y<L ; y++)
// 		{
// 			unsigned int ID = cube::ID(vectors[i],y);
// 			for (auto it = hashtables[y].begin(modulo(ID,tableSize)); it != hashtables[y].end(modulo(ID,tableSize)); ++it )
// 			{
// 				hashtable_item p_b = it->second;
// 				if (p_b.ID == ID)
// 				{
					
// 				}
// 			}
// 		}
// 	}
// };

cube::cube(string input_file,int k,string metric)
{
	//Initialize values
	cube::k=k;
	read_file(input_file,vectors,ids);
	f_table = new map<int, int>[k];
	hypercube = new hash_table<hashtable_item>;
	w=uniform_distribution_rng(0,6);
	vectorSize=vectors[0].size();
	n=ids.size();
	tableSize=n/4;
	v = new vector<float>[k];
	t = new float[k];

	for (int i = 0; i < k; i++)
	{
		v[i].push_back(normal_distribution_rng());
		t[i] = uniform_distribution_rng(0,w-1);
	}

	if(metric=="L2")
		distance=&eucledian_distance;

	for(int i = 0;i<n;i++)
	{
		hashtable_item p{vectors[i],i};
		hypercube->insert(F(vectors[i]),p);
	}
};

cube::~cube()//Destructor
{
	return;
};
