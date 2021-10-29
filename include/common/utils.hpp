using namespace std;

float eucledian_distance(vector<float>,vector<float>);
void read_file(string filename,vector<float> *&vectors,vector<string> &ids);
float normal_distribution_rng();
int uniform_distribution_rng(int lowerRange,int higherRange);
unsigned long long int modulo(long long int a,long long int b);
float inner_product(vector <float> v1,vector <float> v2);