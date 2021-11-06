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

    vector<float> D(n);
    fill(D.begin(), D.end(), HUGE_VAL);
    
    centroid c1;
    int index=uniform_distribution_rng(0,n);
    c1.coordinates=vectors[index];
    non_centroids.erase(remove(non_centroids.begin(), non_centroids.end(), index), non_centroids.end());
    centroids.push_back(c1);
    for(int t=1;t<K;t++)
    {
        centroid c;
        for (int i : non_centroids)
        {
            for (auto it = centroids.begin(); it != centroids.end(); ++it)
            {
                float distance=eucledian_distance(vectors[i],centroids.back().coordinates);
                if(distance<D[i]) D[i]=distance;
            }
        }
        float max_value=*max_element( D.begin(), D.end() );
        
        list<pair<float,int>> P;
        float range;
        for (int r : non_centroids)
        {
            float P_r = 0;
            for(int i:non_centroids)
            {
                if(i>r) break;
                P_r+=pow(D[r]/max_value,2);
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

bool cluster::new_centroids()
{
    vector<vector<float>> new_centroids;
    int converge_count=0;
    for (auto it = centroids.begin(); it != centroids.end(); ++it)
    {
        vector<float> new_centroid(vectorSize);
        iota(new_centroid.begin(), new_centroid.end(), 0);
        for(auto it2 = it->vectors.begin() ; it2 != it->vectors.end(); ++it2)
        {
            for (int i = 0; i < vectorSize; i++)
            {
                new_centroid[i]+=it2->p[i];
            }
        }
        for (int y = 0; y < vectorSize; y++)
        {
            new_centroid[y] /= it->vectors.size();
        }
        new_centroids.push_back(new_centroid);


    }
    if(converge_count==n)
    {
        return false;
    }
    for (int i=0;i<new_centroids.size();i++)
    {
        centroids[i].coordinates=new_centroids[i];
        centroids[i].vectors.clear();
    }
    return true;
};

vector<cluster::centroid> cluster::get_clusters()
{
    return centroids;
}

pair<vector<float>,float> cluster::get_silhouettes_average()
{
    for (auto it = centroids.begin(); it != centroids.end(); ++it)
    {

    }
}

cluster::~cluster()
{
}


//Cluster Lloyd's
cluster_lloyds::cluster_lloyds(int K,vector<vector<float>> vectors,vector<string> ids) : cluster(K,vectors,ids)
{
    // do
    // {
        for(int i=0;i<vectors.size();i++)
        {
            centroid_item ci={p:vectors[i],index:i};
            int minimum=numeric_limits<int>::max(),minimum_index;
            for (auto it = centroids.begin(); it != centroids.end(); ++it)
            {
                float distance=eucledian_distance(vectors[i],it->coordinates);
                if(distance<minimum)
                {
                    minimum=distance;
                    minimum_index= it - centroids.begin();
                }
            }
            centroids[minimum_index].vectors.push_back(ci);
        }
    // }while(new_centroids()==true);
}

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids),LSH(vectors,ids,k,L,L2,1/8)
{
    
}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids),Cube(vectors,ids,k,M,probes,L2)
{
    
}