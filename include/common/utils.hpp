using namespace std;

float eucledian_distance(vector<float>,vector<float>);
void read_file(string filename,vector<float> *&vectors,vector<string> &ids);
float normal_distribution_rng();
int uniform_distribution_rng(int lowerRange,int higherRange);
unsigned long long int modulo(long long int a,long long int b);
float inner_product(vector <float> v1,vector <float> v2);
int getHammingDistance(string first, string second);
string decimalToBinary(int decimal);
int binaryToDecimal(string binary);
int getValue(map<int,int> m, int key);
int notExists(map<int,int> m, int key);