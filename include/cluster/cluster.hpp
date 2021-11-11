#pragma once
#ifndef cluster_h
#define cluster_h

using namespace std;
#include <vector>
#include <list>

#include "lsh.hpp"
#include "cube.hpp"

//Implementation of centroid-based clustering
//K-Means++ Initialization
//L2 Metric
//Update centroids using 

class cluster //Using lloyd's
{
public:
    struct centroid_item
    {
        vector<float> p;
		int index;

        bool operator < (const centroid_item& str) const
        {
            return (index < str.index);
        }
        bool operator == (const centroid_item& str) const
        {
            return (index == str.index);
        }
    };

    struct centroid
    {
        vector<float> coordinates;
        vector<centroid_item> vectors;
    };
    
    vector<centroid> get_clusters();
    pair<vector<float>,float> get_silhouettes_average();

protected:
    vector<centroid> centroids;
    vector<vector<float>> vectors;
    vector<string> ids;
    int K;

    int vectorSize;
    int n;
    
    cluster(int K,vector<vector<float>> vectors,vector<string> ids);
    ~cluster();

    void new_centroids();
    bool convergence(vector<centroid> centroids_old);
    void bruteforce_assignment(vector<tuple<int,int,float>> flagged_indexes);
    float init_search_radius();
    bool terminationCriterion(vector<tuple<int,int,float>> flagged_indexes, float search_radius, int* updatedCentroid);
};

class cluster_lloyds : public cluster
{
public:
    cluster_lloyds(int K,vector<vector<float>> vectors,vector<string> ids);
};


class cluster_lsh : public cluster,public LSH //Using LSH reverse assignment (range search)
{
public:
    cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L);
    void new_assignment();
    void rangeSearch_Assignment(vector<tuple<int,int,float>> flagged_indexes, float search_radius);
    ~cluster_lsh();
};

class cluster_cube : public cluster,public Cube //Using Hypercube reverse assignment (range search)
{
public:
    cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M);
    void new_assignment();
    void rangeSearch_Assignment(vector<tuple<int,int,float>> flagged_indexes, float search_radius);
    ~cluster_cube();
};

#endif