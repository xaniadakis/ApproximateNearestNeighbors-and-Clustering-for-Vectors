#include <hash_functions.hpp>
#include <math.h>       /* pow */

#define K 6
#define M 4294967291
#define TableSize 1000000 //n/8 or n/16, where n is the number of vectors in dataset

int hash(unsigned int i, unsigned int p) {
	return (int)((p*v[i]+t)/w);
}

unsigned int g(unsigned int p) {
	int *h = new int(K);
	for(int i=0; i<K; i++)
		h[i] = hash(i,p) % M;
	int _g = 0;
	for(int i=0; i<K; i++)
		_g += (r[i]*h[i]) % M;
	return abs(_g % M) % TableSize;
}

unsigned int ID(unsigned int p) {
	int *h = new int(K);
	for(int i=0; i<K; i++)
		h[i] = hash(i,p) % M;
	int _g = 0;
	for(int i=0; i<K; i++)
		_g += (r[i]*h[i]) % M;
	return abs(_g % M);
}

int f(void) {
	return rand() % 2;
}