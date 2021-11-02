#pragma once
using namespace std;
#include <vector>
#include <list>

#include "lsh.hpp"
#include "cube.hpp"

class cluster
{
private:
    class centroid
    {
        vector<float> coordinates;
        list<vector<float>> vectors;
    };

    centroid *centroids;
    bool complete;
    int K;
    
public:
    cluster(int K);
    ~cluster();

    void output(string output_file,bool complete=false);
};

class cluster_classic : public cluster
{
public:
    cluster_classic(string input_file,int K);
};

class cluster_lsh : public cluster
{
public:
    cluster_lsh(string input_file,int K,int k,int L);
};

class cluster_cube : public cluster
{
public:
    cluster_cube(string input_file,int K,int k,int probes,int M);
};