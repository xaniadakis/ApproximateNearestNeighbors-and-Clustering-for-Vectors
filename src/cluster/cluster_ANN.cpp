#include "cluster.hpp"
#include "utils.hpp"
#include <algorithm>

//Cluster LSH
cluster_lsh::cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L) : cluster(K,vectors,ids), LSH(vectors,k,L,L2,0.125)
{
    //First assignment
    new_assignment();

    //Assignment/Update
    while(true)
    {
        vector<centroid> centroids_old=centroids;
        new_centroids();
        new_assignment();

        if(convergence(centroids_old)==true)
            break;
    }
}

void cluster_lsh::new_assignment()
{
    vector<tuple<int,int,float>> flagged_indexes;

    float min_distance;
    float current_distance;
    for(int i=0;i<K;i++)
        for(int j=0;j<K;j++){
            current_distance = eucledian_distance(cluster::centroids[i].coordinates, cluster::centroids[j].coordinates);
            if(current_distance<min_distance)
                min_distance = current_distance;
        }

    int search_radius = min_distance/2;
    while(true){
        if(flagged_indexes.size()>=(cluster::ids.size()*(8/10)))
            break;
        vector<tuple<int,int,float>> new_indexes;
        int found = 0;
        for(int i=0;i<K;i++){
            vector<pair<float,unsigned int>> R_Nearest = LSH::find_R_nearest(cluster::centroids[i].coordinates, search_radius);
            
            for(int j=0;j<R_Nearest.size();j++)
            {
                int Index = get<unsigned int>(R_Nearest[j]);
                found = 0;
                for(int l=0;l<flagged_indexes.size();l++)
                {
                    if(get<0>(flagged_indexes[l])==Index)
                        found = 1;
                }
                if(found==1){
                // if (find(flagged_indexes.begin(), flagged_indexes.end(),Index)==flagged_indexes.end()){             
                    centroid_item ci={p:cluster::vectors[Index],index:Index};
                    centroids[i].vectors.push_back(ci);
                    new_indexes.push_back({Index,i,get<float>(R_Nearest[j])});
                }
            }
        }
        for(int i=0;i<new_indexes.size();i++)
        {
            int indexi = get<0>(new_indexes[i]);
            int centroidi = get<1>(new_indexes[i]);
            float distancei = get<float>(new_indexes[i]);
            for(int j=0;j<new_indexes.size();j++)
            {
                int indexj = get<0>(new_indexes[j]);
                int centroidj = get<1>(new_indexes[j]);
                float distancej = get<float>(new_indexes[j]);
                if(indexi==indexj)
                    if(distancei<=distancej)
                    {
                        for(int k=0;k<centroids[centroidj].vectors.size();k++)
                        {
                            if(centroids[centroidj].vectors[k].index==indexj){
                                centroids[centroidj].vectors.erase(centroids[centroidj].vectors.begin()+k-1);
                                new_indexes.erase(new_indexes.begin()+j-1);
                            }
                        }
                    }
                    else               
                    {
                        for(int k=0;k<centroids[centroidi].vectors.size();k++)
                        {
                            if(centroids[centroidi].vectors[k].index==indexi){
                                centroids[centroidi].vectors.erase(centroids[centroidi].vectors.begin()+k-1);
                                new_indexes.erase(new_indexes.begin()+i-1);
                            }
                        }
                    }
            }
        }
        for(int i=0;i<new_indexes.size();i++)
            flagged_indexes.push_back(new_indexes[i]);
    }
}

cluster_lsh::~cluster_lsh()
{

}

//Cluster hypercube
cluster_cube::cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M) : cluster(K,vectors,ids), Cube(vectors,k,M,probes,L2)
{
    //First assignment
    new_assignment();
    
    //Assignment/Update
    while(true)
    {
        vector<centroid> centroids_old=centroids;
        new_centroids();
        new_assignment();

        if(convergence(centroids_old)==true)
            break;
    }
}

void cluster_cube::new_assignment()
{
    vector<tuple<int,int,float>> flagged_indexes;
    
    float min_distance=numeric_limits<float>::max();
    float current_distance;
    for(int i=0;i<K;i++)
        for(int j=i+1;j<K;j++){
            current_distance = eucledian_distance(cluster::centroids[i].coordinates, cluster::centroids[j].coordinates);
            if(current_distance<min_distance)
                min_distance = current_distance;
        }
    
    int search_radius = min_distance/2;
    while(true){
        if(flagged_indexes.size()>=(cluster::ids.size()*(8/10)))
            break;
        vector<tuple<int,int,float>> new_indexes;
        int found = 0;
        for(int i=0;i<K;i++){
            vector<pair<float,unsigned int>> R_Nearest = Cube::find_R_nearest(cluster::centroids[i].coordinates, search_radius);
            
            for(int j=0;j<R_Nearest.size();j++)
            {
                int Index = get<unsigned int>(R_Nearest[j]);
                found = 0;
                for(int l=0;l<flagged_indexes.size();l++)
                {
                    if(get<0>(flagged_indexes[l])==Index)
                        found = 1;
                }
                if(found==1){
                // if (find(flagged_indexes.begin(), flagged_indexes.end(),Index)==flagged_indexes.end()){             
                    centroid_item ci={p:cluster::vectors[Index],index:Index};
                    centroids[i].vectors.push_back(ci);
                    new_indexes.push_back({Index,i,get<float>(R_Nearest[j])});
                }
            }
        }
        for(int i=0;i<new_indexes.size();i++)
        {
            int indexi = get<0>(new_indexes[i]);
            int centroidi = get<1>(new_indexes[i]);
            float distancei = get<float>(new_indexes[i]);
            for(int j=0;j<new_indexes.size();j++)
            {
                int indexj = get<0>(new_indexes[j]);
                int centroidj = get<1>(new_indexes[j]);
                float distancej = get<float>(new_indexes[j]);
                if(indexi==indexj)
                    if(distancei<=distancej)
                    {
                        for(int k=0;k<centroids[centroidj].vectors.size();k++)
                        {
                            if(centroids[centroidj].vectors[k].index==indexj){
                                centroids[centroidj].vectors.erase(centroids[centroidj].vectors.begin()+k-1);
                                new_indexes.erase(new_indexes.begin()+j-1);
                            }
                        }
                    }
                    else               
                    {
                        for(int k=0;k<centroids[centroidi].vectors.size();k++)
                        {
                            if(centroids[centroidi].vectors[k].index==indexi){
                                centroids[centroidi].vectors.erase(centroids[centroidi].vectors.begin()+k-1);
                                new_indexes.erase(new_indexes.begin()+i-1);
                            }
                        }
                    }
            }
        }
        for(int i=0;i<new_indexes.size();i++)
            flagged_indexes.push_back(new_indexes[i]);
    }
}

cluster_cube::~cluster_cube()
{

}