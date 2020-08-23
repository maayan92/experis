#ifndef INTERFACE_DATA_QUERY_H
#define INTERFACE_DATA_QUERY_H

#include "cdrRecord.hpp"
#include "uncopyable.hpp"

namespace data {

template<typename Data, typename Key>
// Data: data aggregation type.
// Key: primary key for data aggregator.
class IDataQuery : private experis::Uncopyable {
public:
    virtual ~IDataQuery();

    virtual bool Query(const Key& a_key, Data& a_data) const = 0; /// change name to query

protected:
    IDataQuery();
};

#include "iDataQuery.hxx"

} // data

#endif