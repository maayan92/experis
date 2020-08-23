#ifndef CUSTOMER_BILLING_H
#define CUSTOMER_BILLING_H

#include "customer.hpp"
#include "iDataAggregator.hpp"
#include "hashMap.hpp"
#include "additionalStructures.hpp"
#include "iDataQuery.hpp"

namespace data{

struct HashFuncCustomer {
    size_t operator()(const kokfikoCDR::Imsi& a_imsi) const {
        std::istringstream mnc(a_imsi.m_mnc);
        size_t mncNum;
        mnc >> mncNum;
        return mncNum;
    }
};

class CustomerBilling : public IDataAggregator, public IDataQuery<Customer, kokfikoCDR::Imsi> { // uncopyable
public:
    CustomerBilling(size_t a_numOfThreads = 2);
    //virtual ~CustomerBilling() = default;

    virtual void Update(const kokfikoCDR::CdrRecord& a_record);
    virtual bool Find(const kokfikoCDR::Imsi& a_imsi, Customer& a_customer) const;

private:
    experis::HashMapMT<kokfikoCDR::Imsi, Customer, HashFuncCustomer, experis::Equal<kokfikoCDR::Imsi> > m_customersData;
};

} // data

#endif