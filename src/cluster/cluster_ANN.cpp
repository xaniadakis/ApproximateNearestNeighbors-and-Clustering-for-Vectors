#include "cluster.hpp"
#include "utils.hpp"

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids),LSH(vectors,ids,k,L,L2,1/8)
{
    LSH lsh(vectors,ids,k,L,L2);
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
}

cluster_lsh::~cluster_lsh()
{

}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids),Cube(vectors,ids,k,M,probes,L2)
{
    Cube cube(vectors,ids,k,M,probes,L2);
    
    vector<string> flagged_ids;
    
    float min_distance;
    float current_distance;
    for(int i=0;i<K;i++)
        for(int j=0;j<K;j++){
            current_distance = eucledian_distance(cluster::centroids[i].coordinates, cluster::centroids[j].coordinates);
            if(current_distance<min_distance)
                min_distance = current_distance;
        }


    int search_radius = min_distance/2;
    for(int i=0;i<K;i++){
        vector<pair<float,unsigned int>> R_Nearest = cube.find_R_nearest(cluster::centroids[i].coordinates, search_radius);
        for(int j=0;j<R_Nearest.size();j++)
        {
            centroid_item ci={p:R_Nearest.first,index:i};
        }
    }
        


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
}

cluster_cube::~cluster_cube()
{

}