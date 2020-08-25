#include "customerBilling.hpp"
#include "customerBilling.hpp"
#include "operatorBilling.hpp"
#include "testFunc.hpp"
using namespace data;
using namespace kofiko;

void FillCustomerResult(Customer& a_customer) {
    map<experis::MSISDN, SecondParty> secondP;
    SecondParty sP;
    sP.m_totalVC = 2152;
    sP.m_totalSms = 0;
    secondP["61523827346"] = sP;
    a_customer.m_outgoingVC = 2152;
    a_customer.m_secondParties = secondP;
}

static void FillOperatorResult(Operator& a_operator) {
    a_operator.m_outgoingVC = 2152;
}

static bool CompareSParty(const pair<experis::MSISDN, SecondParty>& a_laft, const pair<experis::MSISDN, SecondParty>& a_right) {
    return a_laft.second == a_right.second;
}

bool CheckCustomerResult(const Customer& a_left, const Customer& a_right) {
    return (a_left.m_outgoingVC == a_right.m_outgoingVC) &&
            (a_left.m_incomingVC == a_right.m_incomingVC) &&
            (a_left.m_totalDataReceive == a_right.m_totalDataReceive) &&
            (a_left.m_totalDataTransf == a_right.m_totalDataTransf) &&
            (a_left.m_totalSmsReceive == a_right.m_totalSmsReceive) &&
            (a_left.m_totalSmsSent == a_right.m_totalSmsSent) &&
            (equal(a_left.m_secondParties.begin(), a_left.m_secondParties.end(), a_right.m_secondParties.begin(), CompareSParty));
}

bool CheckOperatorResult(const Operator& a_left, const Operator& a_right) {
    return (a_left.m_outgoingVC == a_right.m_outgoingVC) &&
            (a_left.m_incomingVC == a_right.m_incomingVC) &&
            (a_left.m_outgoingSms == a_right.m_outgoingSms) &&
            (a_left.m_incomingSms == a_right.m_incomingSms);
}

bool CheckResult(const Customer& a_customerR, const Operator& a_operatorR) {
    Customer customer;
    FillCustomerResult(customer);
    Operator mobileOp;
    FillOperatorResult(mobileOp);

    return CheckCustomerResult(a_customerR, customer) && CheckOperatorResult(a_operatorR, mobileOp);
}
