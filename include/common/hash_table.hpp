#pragma once
//HashTable of fixed size with overflow buckets
//Created using vectors
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename V>
class hash_table
{
private:
    vector<vector<V>> Buckets;
    unsigned int tablesize;
public:
    hash_table(unsigned int size = 1000);
    void insert(unsigned int key,V value);
    typename vector<V>::iterator begin(unsigned int key);
    typename vector<V>::iterator end(unsigned int key);
};