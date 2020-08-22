#ifndef OPERATOR_BILLING_H
#define OPERATOR_BILLING_H

#include "iDataAggregator.hpp"
#include "hashMap.hpp"
#include "operator.hpp"
#include "additionalStructures.hpp"

namespace data {

struct HashFuncOperator {
    size_t operator()(const experis::MNC& a_mnc) const {
        std::istringstream mnc(a_mnc);
        size_t mncNum;
        mnc >> mncNum;
        return mncNum;
    }
};

class OperatorBilling : public IDataAggregator<Operator, experis::MNC>{ // uncopyable
public:
    OperatorBilling(size_t a_numOfThreads = 2);
    //virtual ~OperatorBilling() = default;

    virtual void Update(const kokfikoCDR::CdrRecord& a_record);
    virtual bool Find(const experis::MNC& a_mnc, Operator& a_operator) const;

private:
    experis::HashMapMT<experis::MNC, Operator, HashFuncOperator, experis::Equal<experis::MNC> > m_operatorData;
};

} // data

#endif