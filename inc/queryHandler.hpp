#ifndef QUERY_HANDLER_H
#define QUERY_HANDLER_H

#include "iDataQuery.hpp"
#include "customerBilling.hpp"
#include "operatorBilling.hpp"

namespace data {

class QueryHandler : private experis::Uncopyable{
public:
    QueryHandler(IDataQuery<Customer, experis::MSISDN>* a_customerBilling, IDataQuery<Operator, experis::MCC_MNC>* a_operatorBilling);
    //~QueryHandler() = default;

    bool GetCustomerQuery(const experis::MSISDN a_msisdn, Customer& a_customer);
    bool GetOperatorQuery(const experis::MCC_MNC a_mccmnc, Operator& a_operator);

private:
    IDataQuery<Customer, experis::MSISDN>* m_customerBilling;
    IDataQuery<Operator, experis::MCC_MNC>* m_operatorBilling;
};

} // data

#endif