#pragma once
using namespace std;
#include <vector>
#include <list>

#include "lsh.hpp"
#include "cube.hpp"
#include "lloyds.hpp"

class cluster
{
private:
    class centroid
    {
        vector<float> coordinates;
        list<vector<float>> vectors;
    };

    centroid *centroids;
    
public:
    cluster();
    ~cluster();
};