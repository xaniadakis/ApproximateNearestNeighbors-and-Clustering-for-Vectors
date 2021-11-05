#include <map>
#include <set>
#include <numeric>
#include <cmath>
#include <limits>
#include <algorithm>

#include "cluster.hpp"
#include "utils.hpp"

//Cluster parent class
cluster::cluster(int K,vector<vector<float>> vectors,vector<string> ids)
{
    cluster::vectors=vectors;
    cluster::ids=ids;
    cluster::K=K;
    cluster::vectorSize=vectors[0].size();
    cluster::n=ids.size();

    //K-Means++ initialization
    vector<int> non_centroids;
    iota(non_centroids.begin(), non_centroids.end(), 0);

    centroid c1;
    int index=uniform_distribution_rng(0,n);
    c1.coordinates=vectors[index];
    non_centroids.erase(remove(non_centroids.begin(), non_centroids.end(), index), non_centroids.end());
    centroids.push_back(c1);
    for(int t=1;t<K;t++)
    {
        vector<float> D(n);
        float max_value=numeric_limits<float>::min();
        centroid c;
        for (int i : non_centroids)
        {
            D[i]=HUGE_VAL;
            for (auto it = centroids.begin(); it != centroids.end(); ++it)
            {
                float distance=eucledian_distance(vectors[i],it->coordinates);
                if(distance<D[i]) D[i]=distance;
                if(distance>max_value) max_value=distance;
            }
        }
        for (int i : non_centroids)
        {
            D[i] /= max_value;
        }
        
        list<pair<float,int>> P;
        float range;
        for (int r : non_centroids)
        {
            float P_r = 0;
            for(int i:non_centroids)
            {
                if(i>r) break;
                P_r+=pow(D[r],2);
            }
            P.push_back({P_r,r});
            range=P_r;
        }
        float x=uniform_distribution_rng_float(0,range);

        for (auto it = P.begin(); it != P.end(); ++it)
        {
            auto next=it++;
            if(x>it->first && x<=next->first)
            {
                centroid c;
                c.coordinates=vectors[next->second];
                non_centroids.erase(remove(non_centroids.begin(), non_centroids.end(), next->second), non_centroids.end());
                centroids.push_back(c);
            }
        }
    }
}

cluster::~cluster()
{
}


//Cluster Lloyd's
cluster_lloyds::cluster_lloyds(int K,vector<vector<float>> vectors,vector<string> ids) : cluster(K,vectors,ids)
{
    for(int i=0;i<vectors.size();i++)
    {

    }
}

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids),LSH(vectors,ids,k,L,L2,1/8)
{
    
}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids),Cube(vectors,ids,k,M,probes,L2)
{
    
}