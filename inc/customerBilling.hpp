#ifndef CUSTOMER_BILLING_H
#define CUSTOMER_BILLING_H

#include "customer.hpp"
#include "iDataAggregator.hpp"
#include "hashMap.hpp"
#include "additionalStructures.hpp"

namespace data{

struct HashFuncCustomer {
    size_t operator()(const experis::IMSI& a_imsi) const {
        return a_imsi; ///// TODO
    }
};

class CustomerBilling : public IDataAggregator<Customer> { // uncopyable
public:
    CustomerBilling(size_t a_numOfThreads = 2);
    //virtual ~CustomerBilling() = default;

    virtual void Update(const kokfikoCDR::CdrRecord& a_record);
    virtual bool Find(const experis::IMSI& a_imsi, Customer& a_operator) const;

private:
    experis::HashMapMT<experis::IMSI, Customer, HashFuncCustomer, experis::Equal<experis::IMSI> > m_customersData;
};

} // data

#endif