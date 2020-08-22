#include "operatorBilling.hpp"

namespace data {

OperatorBilling::OperatorBilling(size_t a_numOfThreads)
: m_operatorData(a_numOfThreads)
{
}

void OperatorBilling::Update(const kokfikoCDR::CdrRecord& a_record) /// change imsi to mnc
{
    Operator mobileOp(a_record);
    std::stringstream imsi;
    imsi << a_record.m_imsi;
    std::string mnc(imsi.str(), 3, 2);
    m_operatorData.Upsert(mnc, mobileOp, experis::Combine<Operator>());
}

bool OperatorBilling::Find(const experis::MNC& a_mnc, Operator& a_operator) const
{
    return m_operatorData.Find(a_mnc, a_operator);
}

} // data