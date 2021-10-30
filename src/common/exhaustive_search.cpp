#include <iostream>
#include "exhaustive_search.hpp"
#include "utils.hpp"
#include <map>

vector<vector_item> exhaustive_search(vector<float> p,vector<float> *vectors,unsigned int N,int R,unsigned int n,float (* distance)(vector<float>,vector<float>))
{    
    //Find N nearest neighbors of vector p size n from array vector in range R
    map<float,vector_item> distances;
    for(unsigned int i=0;i<n;i++)
    {
        vector_item vector = {distance(p,vectors[i]),i};
        if(vector.true_distance <= R)
            distances.insert({vector.true_distance,vector});
    }
    
    vector<vector_item> nBest;
    unsigned int i=0;
    auto it=distances.begin();
    for(;it != distances.end() && i<N ;++it,i++)
    {
        nBest.push_back(it->second);
    }
    return nBest;
}