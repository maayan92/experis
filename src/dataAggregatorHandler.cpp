#include "dataAggregatorHandler.hpp"

namespace data {

DataAggregatorHandler::DataAggregatorHandler(CustomerBilling& a_customerBilling, OperatorBilling& a_operatorBilling)
: m_customerBilling(a_customerBilling)
, m_operatorBilling(a_operatorBilling)
{
}

void DataAggregatorHandler::InsertNewRecord(const kokfikoCDR::CdrRecord& a_record)
{
    m_customerBilling.Update(a_record);
    m_operatorBilling.Update(a_record);
}

} // data