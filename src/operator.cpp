#include "operator.hpp"

namespace data {

Operator::Operator()
: m_incomingVC(0)
, m_outgoingVC(0)
, m_incomingSms(0)
, m_outgoingSms(0)
{
}

Operator::Operator(const kofiko::CdrRecord& a_record)
: m_incomingVC(0)
, m_outgoingVC(0)
, m_incomingSms(0)
, m_outgoingSms(0)
{
    initialization(a_record);
}

Operator& Operator::operator+=(const Operator& a_operator)
{
    m_incomingVC += a_operator.m_incomingVC;
    m_outgoingVC += a_operator.m_outgoingVC;
    m_incomingSms += a_operator.m_incomingSms;
    m_outgoingSms += a_operator.m_outgoingSms;
    return *this;
}

void Operator::initialization(const kofiko::CdrRecord& a_record)
{
    if("MTC" == a_record.m_usageType) {
        m_incomingVC = a_record.m_duration;
    }
    else if("MOC" == a_record.m_usageType) {
        m_outgoingVC = a_record.m_duration;
    }
    else if("SMS-MT" == a_record.m_usageType) {
        m_incomingSms = 1;
    }
    else if("SMS-MO" == a_record.m_usageType) {
        m_outgoingSms = 1;
    }
}

} // data