#include "queryHandler.hpp"

namespace data {

QueryHandler::QueryHandler(IDataQuery<Customer, experis::MSISDN>* a_customerBilling, IDataQuery<Operator, experis::MCC_MNC>* a_operatorBilling)
: m_customerBilling(a_customerBilling)
, m_operatorBilling(a_operatorBilling)
{
}

bool QueryHandler::GetCustomerQuery(const experis::MSISDN a_msisdn, Customer& a_customer)
{
    return m_customerBilling->Query(a_msisdn, a_customer);
}

bool QueryHandler::GetOperatorQuery(const experis::MCC_MNC a_mccmnc, Operator& a_operator)
{
    return m_operatorBilling->Query(a_mccmnc, a_operator);
}

} // data