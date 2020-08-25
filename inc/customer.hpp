#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "typedefIdentifiers.hpp"
#include "cdrRecord.hpp"
#include <map>

namespace data {

struct SecondParty {
    size_t m_totalVC;
    size_t m_totalSms;

    SecondParty& operator+=(const SecondParty& a_secondParty);
    bool operator==(const SecondParty& a_secondParty) const;
};

inline SecondParty& SecondParty::operator+=(const SecondParty& a_secondParty) {
    m_totalVC += a_secondParty.m_totalVC;
    m_totalSms += a_secondParty.m_totalSms;
    return *this;
}

inline bool SecondParty::operator==(const SecondParty& a_secondParty) const {
    return (m_totalVC == a_secondParty.m_totalVC) &&
            (m_totalSms == a_secondParty.m_totalSms);
}

struct Customer {
    typedef std::map<experis::MSISDN, SecondParty> SecondParties;

    explicit Customer(const kofiko::CdrRecord& a_record);
    Customer();
    //~Customer() = default;

    Customer& operator+=(const Customer& a_customer);

    experis::OUT_GOING_VC m_outgoingVC;
    experis::INCOMING_VC m_incomingVC;
    experis::DATA_TRANSFERRED m_totalDataTransf;
    experis::DATA_RECEIVED m_totalDataReceive;
    experis::SMS_SENT m_totalSmsSent;
    experis::SMS_RECEIVED m_totalSmsReceive;
    SecondParties m_secondParties;

private:
    void initialization(const kofiko::CdrRecord& a_record);
    void setSecondParty(experis::MSISDN a_msisdn, size_t a_totalVC, size_t a_totalSms);
};

} // data

#endif