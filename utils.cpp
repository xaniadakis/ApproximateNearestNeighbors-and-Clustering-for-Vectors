//File for program utilities
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>

#include "utils.hpp"

using namespace std;

int modulo(int a, int b) 
{
    //Real modulo operator
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

int normal_distribution_rng()
{
    //Random number generator using normal distribution
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<float> d(0,1);
    return round(d(gen));
}

int uniform_distribution_rng(int lowerRange,int higherRange)
{
    const int range_from  = 0;
    const int range_to    = 10;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);

    return round(distr(generator));
}  



void read_file(string filename)
{
    vector<vector<int>> data;

    ifstream  file(filename);

    string  line;
    // Read one line at a time into the variable line:
    while(getline(file, line))
    {
        vector<int>   lineData;
        stringstream  lineStream(line);

        int value;
        // Read an integer at a time from the line
        lineStream >> value;//Vector Id
        while(lineStream >> value)
        {
            // Add the integers from a line to a 1D array (vector)
            lineData.push_back(value);
        }
        // When all the integers have been read, add the 1D array
        // into a 2D array (as one line in the 2D array)
        data.push_back(lineData);
    }
}