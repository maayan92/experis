#include "customerBilling.hpp"

namespace data {

CustomerBilling::CustomerBilling(size_t a_numOfThreads)
: m_customersData(a_numOfThreads)
{
}

void CustomerBilling::Update(const kokfikoCDR::CdrRecord& a_record)
{
    Customer customer(a_record);
    m_customersData.Upsert(a_record.m_msisdn, customer, experis::Combine<Customer>());
}

bool CustomerBilling::Query(const experis::MSISDN& a_msisdn, Customer& a_customer) const
{
    return m_customersData.Find(a_msisdn, a_customer);
}

} // data