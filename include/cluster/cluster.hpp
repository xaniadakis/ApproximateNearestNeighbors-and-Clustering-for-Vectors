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
private:
    struct centroid_item
    {
        vector<float> p;
		int index;
    };

    struct centroid
    {
        vector<float> coordinates;
        list<vector<centroid_item>> vectors;
    };


    vector<vector<float>> vectors;
    vector<string> ids;
    vector<centroid> centroids;
    int K;

    int vectorSize;
    
public:
    cluster(int K,vector<vector<float>> vectors,vector<string> ids);
    ~cluster();

    void output(string output_file,bool complete=false);
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