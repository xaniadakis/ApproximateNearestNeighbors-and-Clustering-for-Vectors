using namespace std;
#include <vector>

struct vector_item
{
    float true_distance;
	int index;
};

vector<vector_item> exhaustive_search(vector<float> p,vector<float> *vectors,int R,unsigned int n);