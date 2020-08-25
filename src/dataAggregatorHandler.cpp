#include "dataAggregatorHandler.hpp"

namespace data {

DataAggregatorHandler::DataAggregatorHandler(IDataAggregator* a_customerBilling, IDataAggregator* a_operatorBilling)
: m_customerBilling(a_customerBilling)
, m_operatorBilling(a_operatorBilling)
{
}

void DataAggregatorHandler::InsertNewRecord(const kofiko::CdrRecord& a_record)
{
    m_customerBilling->Update(a_record);
    m_operatorBilling->Update(a_record);
}

} // data