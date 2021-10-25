#include <iostream>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <vector>

#include "utils.hpp"

using namespace std;

#include <iostream>

class LSH
{
private:
    int (*distance)(int, int);
public:
    LSH(string input_file,string query_file,string output_file,int k,int L,int N,double R,int (* distance)(vector<int>,vector<int>))
    {

    };
};