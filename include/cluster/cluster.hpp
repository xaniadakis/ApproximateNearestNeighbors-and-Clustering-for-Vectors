#pragma once
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
    };

    struct centroid
    {
        vector<float> coordinates;
        list<centroid_item> vectors;
    };

    vector<centroid> get_clusters();
    pair<vector<float>,float> get_silhouettes_average();
protected:
    vector<vector<float>> vectors;
    vector<string> ids;
    vector<centroid> centroids;
    int K;

    int vectorSize;
    int n;
    
    cluster(int K,vector<vector<float>> vectors,vector<string> ids);
    ~cluster();

    void new_centroids();
    bool convergence(vector<centroid> centroids_old);
};

class cluster_lloyds : public cluster
{
public:
    cluster_lloyds(int K,vector<vector<float>> vectors,vector<string> ids);
};

class cluster_ANN
{
public:
    cluster_ANN(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M,int L,string method);
    ~cluster_ANN();
};

class cluster_lsh : public cluster,public LSH //Using LSH reverse assignment (range search)
{
public:
    cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L);
    ~cluster_lsh();
};

class cluster_cube : public cluster,public Cube //Using Hypercube reverse assignment (range search)
{
public:
    cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M);
    ~cluster_cube();
};