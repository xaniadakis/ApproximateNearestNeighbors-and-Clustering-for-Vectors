#include "cluster.hpp"
#include "utils.hpp"

//Cluster parent class
cluster::cluster(int K,vector<vector<float>> vectors,vector<string> ids)
{
    cluster::vectors=vectors;
    cluster::ids=ids;
    cluster::K=K;
    cluster::vectorSize=vectors[0].size();

    int t=0;

    for(int t=1;t<=cluster::K;t++)
    {
        centroid c;
        for (int x = 0; x < vectorSize; x++)
        {
            c.coordinates.push_back(uniform_distribution_rng(0,INT32_MAX));
        }
    }
}

cluster::~cluster()
{

}

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids),LSH(vectors,ids,k,L,L2,1/8)
{
    
}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids),Cube(vectors,ids,k,M,probes,L2)
{
    
}