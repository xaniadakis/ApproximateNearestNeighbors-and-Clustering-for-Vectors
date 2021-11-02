#include "cluster.hpp"

//Cluster parent class
cluster::cluster(int K)
{

}

cluster::~cluster()
{

}

//Cluster classic (lloyd's)
cluster_classic::cluster_classic(string input_file,int K) : cluster(K)
{

}

//Cluster LSH
cluster_lsh::cluster_lsh(string input_file,int K,int k,int L) : cluster(K)
{

}

//Cluster hypercube
cluster_cube::cluster_cube(string input_file,int K,int k,int probes,int M) : cluster(K)
{
    
}