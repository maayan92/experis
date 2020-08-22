#ifndef DATA_AGGREGATOR_H
#define DATA_AGGREGATOR_H

#include "cdrRecord.hpp"
#include "typedefIdentifiers.hpp"
#include "uncopyable.hpp"

namespace data {

template<typename dataType, typename keyType>
class IDataAggregator : private experis::Uncopyable{
public:
    //IDataAggregator() = default;
    ~IDataAggregator();

    virtual void Update(const kokfikoCDR::CdrRecord& a_record) = 0;
    virtual bool Find(const keyType& a_key, dataType& a_operator) const = 0;
};

template<typename dataType, typename keyType>
IDataAggregator<dataType, keyType>::~IDataAggregator() 
{}

} // data

#endif