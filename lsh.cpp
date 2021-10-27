#include "lsh.hpp"
#include <math.h>
#include <numeric>

unsigned int LSH::g(vector<float> p,unsigned int j){
	int *h = new int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash_L2(i,p,v[j],t[j],w),M);
	int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(modulo(_g,M),tableSize);
}

unsigned int LSH::ID(vector<float> p,unsigned int j) {
	int *h = new int[k];
	for(int i=0; i<k; i++)
		h[i] = modulo(hash_L2(i,p,v[j],t[j],w),M);
	int _g = 0;
	for(int i=0; i<k; i++)
		_g += modulo((r[i]*h[i]),M);
	return modulo(_g,M);
}