#ifndef CUSTOMER_BILLING_H
#define CUSTOMER_BILLING_H

#include "customer.hpp"
#include "iDataAggregator.hpp"
#include "hashMap.hpp"
#include "additionalStructures.hpp"
#include "iDataQuery.hpp"

namespace data{

struct HashFuncCustomer {
    size_t operator()(const experis::MSISDN& a_msisdn) const {
        std::istringstream msisdn(a_msisdn);
        size_t msisdnNum;
        msisdn >> msisdnNum;
        return msisdnNum;
    }
};

class CustomerBilling : public IDataAggregator, public IDataQuery<Customer, experis::MSISDN> { // uncopyable
public:
    CustomerBilling(size_t a_numOfThreads = 2);
    //virtual ~CustomerBilling() = default;

    virtual void Update(const kokfikoCDR::CdrRecord& a_record);
    virtual bool Find(const experis::MSISDN& a_msisdn, Customer& a_customer) const;

private:
    experis::HashMapMT<experis::MSISDN, Customer, HashFuncCustomer, experis::Equal<experis::MSISDN> > m_customersData;
};

} // data

#endif