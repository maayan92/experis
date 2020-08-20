#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "mutexBucket.hpp"
#include "atomic.hpp"
#include "locker.hpp"
#include <tr1/unordered_map>
#include <assert.h>

namespace experis {

template<class Key, class Value, class HashFunc, class Equal>
class HashMapMT : private Uncopyable{
    typedef std::tr1::unordered_map<Key, Value, HashFunc, Equal> Map;
public:
    explicit HashMapMT(size_t a_conccurency = 2);
    //~HashMapMT() = default;

    template<class Combine>
    void Upsert(const Key& a_key, const Value& a_value, const Combine& a_combineFunc);
    bool Find(const Key& a_key, Value& a_foundValue) const;
    bool Remove(const Key& a_key, Value& a_foundValue);
    size_t Size() const;

private:
    Map m_hash;
    MutexBucket m_mutexBucket;
    Atomic<size_t> m_size;
};

} // experis

namespace experis {

template<class Key, class Value, class HashFunc, class Equal> 
HashMapMT<Key, Value, HashFunc, Equal>::HashMapMT(size_t a_conccurency)
: m_hash()
, m_mutexBucket(a_conccurency)
, m_size()
{
    assert(a_conccurency > 1);
}

template<class Key, class Value, class HashFunc, class Equal>
template<class Combine>
void HashMapMT<Key, Value, HashFunc, Equal>::Upsert(const Key& a_key, const Value& a_value, const Combine& a_combineFunc)
{
    multiThreading::Locker locker(m_mutexBucket.GetMutexByHashPosition(HashFunc()(a_key)));
    typename Map::iterator itr = m_hash.find(a_key);
    
    if(itr != m_hash.end()) {
        itr->second = a_combineFunc(itr->second, a_value);
    }
    else {
        m_hash.insert(std::make_pair(a_key, a_value));
        ++m_size;
    }
}

template<class Key, class Value, class HashFunc, class Equal>
bool HashMapMT<Key, Value, HashFunc, Equal>::Find(const Key& a_key, Value& a_foundValue) const
{
    Mutex* mutex = (const_cast<MutexBucket*>(&m_mutexBucket))->GetMutexByHashPosition(HashFunc()(a_key));
    multiThreading::Locker locker(mutex);
    typename Map::const_iterator itr = m_hash.find(a_key);
    
    if(itr != m_hash.end()) {
        a_foundValue = itr->second;
        return true;
    }
    
    return false;
}

template<class Key, class Value, class HashFunc, class Equal>
bool HashMapMT<Key, Value, HashFunc, Equal>::Remove(const Key& a_key, Value& a_foundValue)
{
    multiThreading::Locker locker(m_mutexBucket.GetMutexByHashPosition(HashFunc()(a_key)));
    typename Map::iterator itr = m_hash.find(a_key);
    
    if(itr != m_hash.end()) {
        a_foundValue = itr->second;
        m_hash.erase(itr);
        --m_size;
        return true;
    }

    return false;
}

template<class Key, class Value, class HashFunc, class Equal>
size_t HashMapMT<Key, Value, HashFunc, Equal>::Size() const {
    return (size_t)m_size;
}

} // experis

#endif