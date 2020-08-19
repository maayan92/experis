#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "mutexBucket.hpp"
#include <tr1/unordered_map>
#include "atomic.hpp"
#include <assert.h>

namespace experis {

template<class Key, class T, class HashFunc, class Equal>
class HashMapMT : private Uncopyable{
    typedef std::tr1::unordered_map<Key, T, HashFunc, Equal> Map;
    typedef typename Map::iterator Iterator;
public:
    explicit HashMapMT(size_t a_conccurency = 2);
    //~HashMapMT() = default;

    template<class Combine>
    void Upsert(const Key& a_key, const T& a_value);
    bool Find(const Key& a_key, T& a_foundValue) const;
    bool Remove(const Key& a_key, T& a_foundValue);
    size_t Size() const;

private:
    Map m_hash;
    MutexBucket m_mutexBucket;
    Atomic<size_t> m_size;
};

} // experis

namespace experis {

template<class Key, class T, class HashFunc, class Equal> 
HashMapMT<Key, T, HashFunc, Equal>::HashMapMT(size_t a_conccurency)
: m_hash()
, m_mutexBucket(a_conccurency)
, m_size()
{
    assert(a_conccurency > 1);
}

template<class Key, class T, class HashFunc, class Equal>
template<class Combine>
void HashMapMT<Key, T, HashFunc, Equal>::Upsert(const Key& a_key, const T& a_value)
{
    size_t hashVal = HashFunc()(a_key);
    m_mutexBucket.LockByPosition(hashVal);
    Iterator itr = m_hash.find(a_key);
    if(itr != m_hash.end()) {
        itr->second = Combine()(itr->second, a_value);
    }
    else {
        m_hash.insert(std::make_pair(a_key, a_value));
        ++m_size;
    }
    m_mutexBucket.UnLockByPosition(hashVal);
}

template<class Key, class T, class HashFunc, class Equal>
bool HashMapMT<Key, T, HashFunc, Equal>::Find(const Key& a_key, T& a_foundValue) const
{
    size_t hashVal = HashFunc()(a_key);
    m_mutexBucket.LockByPosition(hashVal);
    typename Map::const_iterator itr = m_hash.find(a_key);
    if(itr != m_hash.end()) {
        a_foundValue = itr->second;
        m_mutexBucket.UnLockByPosition(hashVal);
        return true;
    }
    m_mutexBucket.UnLockByPosition(hashVal);

    return false;
}

template<class Key, class T, class HashFunc, class Equal>
bool HashMapMT<Key, T, HashFunc, Equal>::Remove(const Key& a_key, T& a_foundValue)
{
    size_t hashVal = HashFunc()(a_key);
    m_mutexBucket.LockByPosition(hashVal);
    Iterator itr = m_hash.find(a_key);
    bool result = false;
    if(itr != m_hash.end()) {
        a_foundValue = itr->second;
        m_hash.erase(itr);
        result = true;
        --m_size;
    }
    m_mutexBucket.UnLockByPosition(hashVal);

    return result;
}

template<class Key, class T, class HashFunc, class Equal>
size_t HashMapMT<Key, T, HashFunc, Equal>::Size() const {
    return (size_t)m_size;
}

} // experis

#endif