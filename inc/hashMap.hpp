#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "mutexBucket.hpp"
#include <tr1/unordered_map>

namespace experis {

template<class Key, class T, class HashFunc, class Equal>
class HashMapMT {
    typedef std::tr1::unordered_map<Key, T, HashFunc, Equal> Map;
    typedef typename Map::iterator Iterator;
public:
    HashMapMT(size_t a_numOfThreads);
    //HashMapMT(const HashMapMT& a_hashMapMT) = default;
    //~HashMapMT() = defult;
    //HashMapMT& operator=(const HashMapMT& a_hashMapMT) = default;

    template<class Combine>
    void Upsert(Key a_key, T a_value);
    const T* Find(Key a_key);

private:
    void update(Key a_key, T a_value, T a_currentVal);

private:
    Map m_hash;
    MutexBucket m_mutexBucket;
};

} // experis

namespace experis {

template<class Key, class T, class HashFunc, class Equal> 
HashMapMT<Key, T, HashFunc, Equal>::HashMapMT(size_t a_numOfThreads)
: m_hash()
, m_mutexBucket(a_numOfThreads)
{
    //assert(m_mutexBucket == MutexBucket(a_numOfThreads));
}

template<class Key, class T, class HashFunc, class Equal>
template<class Combine>
void HashMapMT<Key, T, HashFunc, Equal>::Upsert(Key a_key, T a_value)
{
    m_mutexBucket.LockByPosition(HashFunc()(a_key));
    Iterator itr = m_hash.find(a_key);
    if(itr != m_hash.end()) {
        m_hash[a_key] = Combine()(itr->second, a_value);
    }
    else {
        m_hash[a_key] = a_value;
    }
    m_mutexBucket.UnLockByPosition(HashFunc()(a_key));
}

template<class Key, class T, class HashFunc, class Equal>
const T* HashMapMT<Key, T, HashFunc, Equal>::Find(Key a_key)
{
    m_mutexBucket.LockByPosition(HashFunc()(a_key));
    typename Map::const_iterator itr = m_hash.find(a_key);
    if(itr != m_hash.end()) {
        m_mutexBucket.UnLockByPosition(HashFunc()(a_key));
        return &(itr->second);
    }
    m_mutexBucket.UnLockByPosition(HashFunc()(a_key));

    return 0;
}

} // experis

#endif