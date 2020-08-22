#ifndef OPERATOR_H
#define OPERATOR_H

#include "typedefIdentifiers.hpp"
#include "cdrRecord.hpp"

namespace data {

struct Operator {
    Operator();
    Operator(const kokfikoCDR::CdrRecord& a_record);

    experis::INCOMING_VC m_incomingVC;
    experis::OUT_GOING_VC m_outgoingVC;
    experis::SMS_RECEIVED m_incomingSms;
    experis::SMS_SENT m_outgoingSms;

    Operator& operator+=(const Operator& a_operator);

private:
    void initialization(const kokfikoCDR::CdrRecord& a_record);
};

} // data

#endif