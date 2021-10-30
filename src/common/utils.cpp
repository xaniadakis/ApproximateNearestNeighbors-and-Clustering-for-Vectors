//File for program utilities
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <algorithm>
#include <cmath>
#include <map>
#include <algorithm>

#include "utils.hpp"
using namespace std;

int getHammingDistance(string first, string second)
{
	int len1 = first.size();
	int len2 = second.size();
	int _hammingDistance = 0;
	for(int i=0; i<min(len1, len2); i++){
		if(first[i] != second[i]){
			string j(1,first[i]);
			string k(1,second[i]);
			_hammingDistance += abs(stoi(j)-stoi(k));
		}
	}
	if(len1 != len2)
		_hammingDistance += abs(len1-len2);
	return _hammingDistance;
}

string decimalToBinary(int decimal)
{
    string r;
    while(decimal != 0) 
	{
		r = ( decimal % 2 == 0 ? "0" : "1" ) + r; 
		decimal /= 2;
	}
    return r;
}

int binaryToDecimal(string binary){
	return stoi(binary, 0, 2);
}

int getValue(map<int,int> m, int key){
	return m.find(key)->second;
}

int notExists(map<int,int> m, int key){
	if(m.find(key) == m.end())
		return 1;
	else 
		return 0;
}

float eucledian_distance(vector<float> p1,vector<float> p2)
{
	float distance=0;
	for (unsigned int i=0;i<p1.size();i++)
	{
		distance+=pow((p2[i]-p1[i]),2);
	}
	return sqrt(distance);
}

unsigned long long int modulo(long long int a,long long int b) 
{
	//Real modulo operator
	const long long int result = a % b;
	return result >= 0 ? result : result + b;
}

float normal_distribution_rng()
{
	//Random number generator using normal distribution
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<float> d(0,1);
	return d(gen);
}

int uniform_distribution_rng(int lowerRange,int higherRange)
{
	random_device rand_dev;
	mt19937 generator(rand_dev());
	uniform_int_distribution<int> distr(lowerRange, higherRange);

	return distr(generator);
}  


void read_file(string filename,vector<float> *&vectors,vector<string> &ids)
{
	ifstream  file(filename);
	int filelines=count(istreambuf_iterator<char>(file), 
    istreambuf_iterator<char>(), '\n');

	vectors=new vector<float>[filelines];

	file.clear();
	file.seekg(0,ios::beg);
	string  line;
	int i=0;
	while(getline(file, line))
	{
		stringstream  lineStream(line);

		float value;
		string id;
		lineStream >> id;
		ids.push_back(id);//Vector Id
		while(lineStream >> value)
		{
			vectors[i].push_back(value);
		}
		i++;
	}
}

void write_file(ofstream &outfile,string query_id,vector<string> ids,multimap<float, int> distances,vector<vector_item> distances_true,double time,double time_true,string algorithm)
{
	outfile << "Query: " << query_id << endl;
	unsigned int y=0;
	auto it=distances.begin();
	for(;it != distances.end() && y<distances_true.size() ;++it,y++)
	{
		outfile << "Nearest neighbor-" << y+1 << ": " << ids[it->second] << endl;
		outfile << "distance" << algorithm << ": " << (double) it->first << endl;
		outfile << "distanceTrue: " << (double) distances_true[y].true_distance << endl;
	}

	outfile << "t" << algorithm << ": " << time << endl;
	outfile << "tTrue: " << time_true << endl;

	outfile << "R-near neighbors:" << endl;
	for (it = distances.begin(); it != distances.end(); ++it)
	{
		outfile << ids[it->second] << endl;
	}
}
