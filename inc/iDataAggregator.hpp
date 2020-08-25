#ifndef DATA_AGGREGATOR_H
#define DATA_AGGREGATOR_H

#include "cdrRecord.hpp"
#include "uncopyable.hpp"

namespace data {

class IDataAggregator : private experis::Uncopyable {
public:
    virtual ~IDataAggregator();

    virtual void Update(const kofiko::CdrRecord& a_record) = 0;

protected:
    IDataAggregator();
};

} // data

#endif