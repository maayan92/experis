#include "customer.hpp"
#include <algorithm>

namespace data {

struct CombineSecondParties {
    CombineSecondParties(Customer::SecondParties& a_secondParties);
    //~CombineSecondParties() = default;

    void operator()(std::pair<experis::MSISDN, struct SecondParty> a_secondParty);

private:
    Customer::SecondParties& m_secondParties;
};

inline CombineSecondParties::CombineSecondParties(Customer::SecondParties& a_secondParties)
: m_secondParties(a_secondParties)
{
}

inline void CombineSecondParties::operator()(std::pair<experis::MSISDN, SecondParty> a_secondParty)
{
    m_secondParties[a_secondParty.first] += a_secondParty.second;
}

Customer::Customer()
: m_outgoingVC(0)
, m_incomingVC(0)
, m_totalDataTransf(0)
, m_totalDataReceive(0)
, m_totalSmsSent(0)
, m_totalSmsReceive(0)
, m_secondParties()
{
}

Customer::Customer(const kofiko::CdrRecord& a_record) 
: m_outgoingVC(0)
, m_incomingVC(0)
, m_totalDataTransf(0)
, m_totalDataReceive(0)
, m_totalSmsSent(0)
, m_totalSmsReceive(0)
, m_secondParties()
{
    initialization(a_record);
}

Customer& Customer::operator+=(const Customer& a_customer) {
    m_outgoingVC += a_customer.m_outgoingVC;
    m_incomingVC += a_customer.m_incomingVC;
    m_totalDataTransf += a_customer.m_totalDataTransf;
    m_totalDataReceive += a_customer.m_totalDataReceive;
    m_totalSmsSent += a_customer.m_totalSmsSent;
    m_totalSmsReceive += a_customer.m_totalSmsReceive;

    std::for_each(a_customer.m_secondParties.begin(), a_customer.m_secondParties.end(), CombineSecondParties(m_secondParties));
    return *this;
}

// private functions:

void Customer::initialization(const kofiko::CdrRecord& a_record) {
    if("MOC" == a_record.m_usageType) {
        m_outgoingVC = a_record.m_duration;
        setSecondParty(a_record.m_secondPartyMsisdn, m_outgoingVC, 0);
    }
    else if("MTC" == a_record.m_usageType) {
        m_incomingVC = a_record.m_duration;
        setSecondParty(a_record.m_secondPartyMsisdn, m_incomingVC, 0);
    }
    else if("SMS-MO" == a_record.m_usageType) {
        m_totalSmsSent = 1;
        setSecondParty(a_record.m_secondPartyMsisdn, 0, m_totalSmsSent);
    }
    else if("SMS-MT" == a_record.m_usageType) {
        m_totalSmsReceive = 1;
        setSecondParty(a_record.m_secondPartyMsisdn, 0, m_totalSmsReceive);
    }
    else if("D" == a_record.m_usageType) {
        m_totalDataTransf = a_record.m_byteTransmitted;
        m_totalDataReceive = a_record.m_byteRecieved;
    }
    else {
        setSecondParty(a_record.m_secondPartyMsisdn, 0, 0);
    }
}

void Customer::setSecondParty(experis::MSISDN a_msisdn, size_t a_totalVC, size_t a_totalSms) {
    SecondParty secondParty;
    secondParty.m_totalVC = a_totalVC;
    secondParty.m_totalSms = a_totalSms;
    m_secondParties.insert(std::make_pair(a_msisdn, secondParty));
}

} // data