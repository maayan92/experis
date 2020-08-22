#ifndef DATA_AGGREGATOR_H
#define DATA_AGGREGATOR_H

#include "cdrRecord.hpp"
#include "typedefIdentifiers.hpp"
#include "uncopyable.hpp"

namespace data {

template<typename T>
class IDataAggregator : private experis::Uncopyable{
public:
    //IDataAggregator() = default;
    ~IDataAggregator();

    virtual void Update(const kokfikoCDR::CdrRecord& a_record) = 0;
    virtual bool Find(const experis::IMSI& a_imsi, T& a_operator) const = 0;
};

template<typename T>
IDataAggregator<T>::~IDataAggregator() 
{}

} // data

#endif