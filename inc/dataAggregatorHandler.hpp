#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "uncopyable.hpp"
#include "customerBilling.hpp"
#include "operatorBilling.hpp"

namespace data {

class DataAggregatorHandler : private experis::Uncopyable{
public:
    DataAggregatorHandler(IDataAggregator* a_customerBilling, IDataAggregator* a_operatorBilling);
    //~DataAggregatorHandler() = default;

    void InsertNewRecord(const kokfikoCDR::CdrRecord& a_record);

private:
    IDataAggregator* m_customerBilling;
    IDataAggregator* m_operatorBilling;
};

} // data

#endif