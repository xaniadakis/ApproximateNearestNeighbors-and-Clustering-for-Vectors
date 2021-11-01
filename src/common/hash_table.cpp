#include "hash_table.hpp"
#include "utils.hpp"

template <typename V>
hash_table<V>::hash_table(unsigned int size)
{
    hash_table::Buckets = vector<vector<V>>(size);
    hash_table::tablesize=size;
};

template <typename V>
void hash_table<V>::insert(unsigned int key,V value)
{
    Buckets[key].push_back(value);
};

template <typename V>
typename vector<V>::iterator hash_table<V>::begin(unsigned int key)
{
    return Buckets[key].begin();
};

template <typename V>
typename vector<V>::iterator hash_table<V>::end(unsigned int key)
{
    return Buckets[key].end();
};