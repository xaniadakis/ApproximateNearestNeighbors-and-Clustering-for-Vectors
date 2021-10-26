using namespace std;

float eucledian_distance(vector<float>,vector<float>);
void read_file(string filename,vector<float> *&vectors,vector<string> &ids);
float normal_distribution_rng();
int uniform_distribution_rng(int lowerRange,int higherRange);
int modulo(int a, int b);