#include "operatorBilling.hpp"

namespace data {

OperatorBilling::OperatorBilling(size_t a_numOfThreads)
: m_operatorData(a_numOfThreads)
{
}

void OperatorBilling::Update(const kokfikoCDR::CdrRecord& a_record)
{
    Operator mobileOp(a_record);
    std::string mccmnc(a_record.m_imsi.m_mcc);
    mccmnc += a_record.m_imsi.m_mnc;
    m_operatorData.Upsert(mccmnc, mobileOp, experis::Combine<Operator>());
}

bool OperatorBilling::Query(const experis::MCC_MNC& a_mccmnc, Operator& a_operator) const
{
    return m_operatorData.Find(a_mccmnc, a_operator);
}

} // data