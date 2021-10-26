#include "lsh.hpp"
#include <math.h>
#include <numeric>

int LSH::hash(unsigned int i,vector<float> p,vector<float> *v,float *t) {
	float innerProduct = inner_product(p.begin(), p.end(), v[i].begin(), 0);
	return floor((innerProduct+t[i])/w);
}

unsigned int LSH::g(vector<float> p,unsigned int j){
	int *h = new int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash(i,p,v[j],t[j]),M);
	int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(modulo(_g,M),tableSize);
}

unsigned int LSH::ID(vector<float> p,unsigned int j) {
	int *h = new int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash(i,p,v[j],t[j]),M);
	int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(_g,M);
}