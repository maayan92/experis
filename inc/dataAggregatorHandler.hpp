#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "uncopyable.hpp"
#include "customerBilling.hpp"
#include "operatorBilling.hpp"

namespace data {

class DataAggregatorHandler : private experis::Uncopyable{
public:
    DataAggregatorHandler(CustomerBilling& a_customerBilling, OperatorBilling& a_operatorBilling);
    //~DataAggregatorHandler() = default;

    void InsertNewRecord(const kokfikoCDR::CdrRecord& a_record);

private:
    CustomerBilling& m_customerBilling;
    OperatorBilling& m_operatorBilling;
};

} // data

#endif