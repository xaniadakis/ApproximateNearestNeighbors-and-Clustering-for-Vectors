//File for program utilities
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "utils.hpp"

using namespace std;

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