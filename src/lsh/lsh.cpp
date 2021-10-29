#include "lsh.hpp"
#include <math.h>
#include <numeric>
#include <map>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

unsigned int LSH::g(vector<float> p,unsigned int j){
	return modulo(ID(p,j),tableSize);
}

unsigned long long int LSH::ID(vector<float> p,unsigned int j) {
	unsigned long long int *h = new unsigned long long int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash_L2(i,p,v[j],t[j],w),M);
	unsigned long long int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(_g,M);
}

void LSH::query(string query_file,string output_file,unsigned int N,int R)
{
	struct stat info;
	if (stat("./output",&info) == -1) {
		mkdir("./output", 0700);
	}
	ofstream outfile ("./output/" + output_file);

	vector<float> *vectors_query;
	vector<string> ids_query;
	read_file(query_file,vectors_query,ids_query);
	unsigned int n_query=ids_query.size();
	map<float, hashtable_item> distances;

	for (unsigned int i=0 ; i<n_query ; i++)
	{
		vector<float> p = vectors_query[i];
		for (int y=0 ; y<L ; y++)
		{
			unsigned long long int ID = LSH::ID(vectors[i],y);
			for (auto it = hashtables[y].begin(modulo(ID,tableSize)); it != hashtables[y].end(modulo(ID,tableSize)); ++it )
			{
				hashtable_item p_b = it->second;
				if (p_b.ID == ID)
				{
					float distance = LSH::distance(p,p_b.p);
					if(distance<=R)
					{
						distances.insert({distance,p_b});
					}
				}
			}
		}
		vector<vector_item> nBest_true = exhaustive_search(p,vectors,N,R,n);

		//Print N closest neighbors
		unsigned int y=0;
   		auto it=distances.begin();
		for(;it != distances.end() && y<nBest_true.size() ;++it,y++)
		{
			hashtable_item closest = it->second;
			cout << it->first << nBest_true[y].true_distance << endl;
		}
	}
	outfile.close();
};

LSH::LSH(string input_file,int k,int L,float (* metric)(vector<float>,vector<float>))//Constructor
{
	//Initialize values
	LSH::L=L;
	hashtables = new unordered_map<unsigned int, hashtable_item>[L];
	LSH::k=k;
	read_file(input_file,vectors,ids);
	w=uniform_distribution_rng(0,6);//Should be average of vector distances times 3
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

LSH::~LSH()//Destructor
{
	return;
};