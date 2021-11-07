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
    vector<int> non_centroids(n);
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
            float distance=eucledian_distance(vectors[i],centroids.back().coordinates);
            if(distance<D[i]) 
            {
                D[i]=distance;
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

void cluster::new_centroids()
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
    for (int i=0;i<new_centroids.size();i++)
    {
        centroids[i].coordinates=new_centroids[i];
        centroids[i].vectors.clear();
    }
};

vector<cluster::centroid> cluster::get_clusters()
{
    return centroids;
}

// vector<pair<vector<float>,float>> cluster::get_silhouettes_average()
// {
//     for (auto it = centroids.begin(); it != centroids.end(); ++it)
//     {
        
//     }
// }

bool cluster::convergence(vector<centroid> centroids_old)
{
    for (int i = 0; i < centroids.size(); i++)
    {   
        if(centroids[i].vectors.size() != centroids_old[i].vectors.size())
            return false;
        auto it=centroids[i].vectors.begin();
        auto it_old=centroids_old[i].vectors.begin();
        for(;it!=centroids[i].vectors.end();it++,it_old++)
        {
            if(it->index!=it_old->index)
                return false;
        }
    }
    return true;
}

cluster::~cluster()
{
}


//Cluster Lloyd's
cluster_lloyds::cluster_lloyds(int K,vector<vector<float>> vectors,vector<string> ids) : cluster(K,vectors,ids)
{
    //First assignment
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
    //Assignment/Update
    while(true)
    {
        vector<centroid> centroids_old=centroids;
        new_centroids();

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

        if(convergence(centroids_old)==true)
            break;
    }
}    //First assignment
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