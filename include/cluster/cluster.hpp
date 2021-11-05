#pragma once
using namespace std;
#include <vector>
#include <list>

#include "lsh.hpp"
#include "cube.hpp"

class cluster
{
private:
    class centroid_item
    {
        vector<float> p;
		int index;
    };

    class centroid
    {
        vector<float> coordinates;
        list<vector<centroid_item>> vectors;
    };


    vector<vector<float>> vectors;
    vector<string> ids;
    vector<centroid> centroids;
    bool complete;
    int K;
    
public:
    cluster(int K,vector<vector<float>> vectors,vector<string> ids);
    ~cluster();

    void output(string output_file,bool complete=false);
};

class cluster_lsh : public cluster,public LSH
{
private:
    LSH *lsh;
public:
    cluster_lsh(vector<vector<float>> vectors,vector<string> ids,int K,int k,int L);
    ~cluster_lsh();
};

class cluster_cube : public cluster,public Cube
{
private:
    Cube *cube;
public:
    cluster_cube(vector<vector<float>> vectors,vector<string> ids,int K,int k,int probes,int M);
    ~cluster_cube();
};