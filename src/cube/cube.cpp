#include "cube.hpp"
#include <math.h>
#include <numeric>
#include <map>
#include <utils.hpp>
#include <unordered_map>

#define M 4294967291

unsigned int Cube::f(int i, int h_p) {
	int _f = rand() % 2;
	if (notExists(f_table[i], h_p)) {
		f_table[i].insert(pair<int,int>(h_p, _f));
		return _f;
	} 
	else 
		return getValue(f_table[i], h_p);
}

unsigned int Cube::F(vector<float> p){
	string _F;
	for(int i=0; i<k; i++){
		// cout << f(i, hash_L2(i,p,v,t,w)) << endl;
		_F.push_back( f(i, hash_L2(i,p,v,t,w)));
		cout << _F << endl;
	}
	return binaryToDecimal(_F);
}

Cube::Cube(vector<vector<float>> input_vectors,vector<string> input_ids,int k,int metric)
{
	vectors=input_vectors;
	ids=input_ids;
	
	//Initialize values
	Cube::k=k;
	f_table = new map<int, int>[k];
	hypercube = new hash_table<hashtable_item_cube>;
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

	if(metric==L2)
		distance=&eucledian_distance;

	for(int i = 0;i<n;i++)
	{
		hashtable_item_cube p{vectors[i],i};
		hypercube->insert(F(vectors[i]),p);
	}
};

vector<pair<float,unsigned int>> Cube::find_N_nearest(vector<float> p,unsigned int N)
{
	//Returns indexes of N Nearest elements
	multimap<float, int> distances;


	for (auto it = hypercube->begin(F(p)); it != hypercube->end(F(p)); ++it )
	{
		hashtable_item_cube p_b = *it;
		float distance = Cube::distance(p,p_b.p);
		distances.insert({distance,p_b.index});

	}

	vector<pair<float,unsigned int>> N_Nearest;
	unsigned int y=0;
	auto it=distances.begin();
	for(;it != distances.end() && y<N ;++it,y++)
	{
		N_Nearest.push_back({it->first,it->second});
	}
	return N_Nearest;
}

vector<pair<float,unsigned int>> Cube::find_R_nearest(vector<float> p,int R)
{
	//Returns indexes of R nearest element
	multimap<float, int> distances;


	for (auto it = hypercube->begin(F(p)); it != hypercube->end(F(p)); ++it )
	{
		hashtable_item_cube p_b = *it;
		float distance = Cube::distance(p,p_b.p);
		if(distance<=R)
			distances.insert({distance,p_b.index});

	}

	vector<pair<float,unsigned int>> R_Nearest;
	auto it=distances.begin();
	for(;it != distances.end();++it)
	{
		R_Nearest.push_back({it->first,it->second});
	}

	return R_Nearest;
}

Cube::~Cube()//Destructor
{
	return;
};
