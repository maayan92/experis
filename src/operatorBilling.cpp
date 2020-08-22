#include "operatorBilling.hpp"

namespace data {

OperatorBilling::OperatorBilling(size_t a_numOfThreads)
: m_operatorData(a_numOfThreads)
{
}

void OperatorBilling::Update(const kokfikoCDR::CdrRecord& a_record)
{
    Operator mobileOp(a_record);
    m_operatorData.Upsert(a_record.m_imsi, mobileOp, experis::Combine<Operator>()); /// change imsi to mcn
}

bool OperatorBilling::Find(const experis::IMSI& a_imsi, Operator& a_operator) const /// change imsi to mcn
{
    return m_operatorData.Find(a_imsi, a_operator);
}

} // data