#include "customerBilling.hpp"

namespace data {

CustomerBilling::CustomerBilling(size_t a_numOfThreads)
: m_customersData(a_numOfThreads)
{
}

void CustomerBilling::Update(const kokfikoCDR::CdrRecord& a_record)
{
    Customer customer(a_record);
    m_customersData.Upsert(a_record.m_imsi, customer, experis::Combine<Customer>());
}

bool CustomerBilling::Find(const experis::IMSI& a_imsi, Customer& a_operator) const
{
    return m_customersData.Find(a_imsi, a_operator);
}

} // data