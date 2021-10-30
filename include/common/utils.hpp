#pragma once

using namespace std;
#include <string>
#include <map>

#include "lsh.hpp"
#include "exhaustive_search.hpp"


float eucledian_distance(vector<float>,vector<float>);
void read_file(string filename,vector<float> *&vectors,vector<string> &ids);
float normal_distribution_rng();
int uniform_distribution_rng(int lowerRange,int higherRange);
unsigned long long int modulo(long long int a,long long int b);
float inner_product(vector <float> v1,vector <float> v2);
void write_file(ofstream &outfile,string query_id,vector<string> ids,multimap<float, int> distances,vector<vector_item> distances_true,double time,double time_true,string algorithm /*LSH or Hypercube*/);