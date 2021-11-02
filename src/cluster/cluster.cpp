#include "cluster.hpp"

//Cluster parent class
cluster::cluster(int K,vector<vector<float>> vectors,vector<string> ids)
{

}

cluster::~cluster()
{

}

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids)
{

}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids)
{
    
}