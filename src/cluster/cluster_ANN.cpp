#include "cluster.hpp"
#include "utils.hpp"

cluster_ANN::cluster_ANN(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M,int L,string method)
{
    if (method=="LSH")
        cluster_lsh(vectors,ids,K,k,L);
    else if (method=="Hypercube")
        cluster_cube(vectors,ids,K,k,probes,M);

}

cluster_ANN::~cluster_ANN()
{

}

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids),LSH(vectors,ids,k,L,L2,1/8)
{
    
}

cluster_lsh::~cluster_lsh()
{

}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids),Cube(vectors,ids,k,M,probes,L2)
{
    
}

cluster_cube::~cluster_cube()
{

}