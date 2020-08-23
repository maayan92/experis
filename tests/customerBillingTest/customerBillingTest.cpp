#include "customerBilling.hpp"
#include <iostream>
using namespace kokfikoCDR;
using namespace std;
using namespace data;

static void FillValues(CdrRecord::RecordInfo& a_values, const string& a_usage, const string&a_secondParty) {
    a_values.push_back("123");
    a_values.push_back("425020528409010");
    a_values.push_back("35-209900-176148-1");
    a_values.push_back(a_usage);
    a_values.push_back("9720528409042");
    a_values.push_back("DD/MM/YYYY");
    a_values.push_back("HH:MM:SS");
    a_values.push_back("2152");
    a_values.push_back("64");
    a_values.push_back("32");
    a_values.push_back(a_secondParty);
}

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static bool CompareSParty(const pair<experis::MSISDN, SecondParty>& a_laft, const pair<experis::MSISDN, SecondParty>& a_right) {
    return a_laft.second == a_right.second;
}

static bool CheckResult(const Customer& a_wantResult, const Customer& a_result) {
    return (a_result.m_incomingVC == a_wantResult.m_incomingVC) &&
            (a_result.m_outgoingVC == a_wantResult.m_outgoingVC) &&
            (a_result.m_totalDataReceive == a_wantResult.m_totalDataReceive) &&
            (a_result.m_totalDataTransf == a_wantResult.m_totalDataTransf) &&
            (a_result.m_totalSmsReceive == a_wantResult.m_totalSmsReceive) &&
            (a_result.m_totalSmsSent == a_wantResult.m_totalSmsSent) &&
            (equal(a_result.m_secondParties.begin(), a_result.m_secondParties.end(), a_wantResult.m_secondParties.begin(), CompareSParty));
}

// tests:

static void TestCustomerBillingCreate() {
    CustomerBilling customerBilling(5);
    static int testNum = 0;
    Customer customer;
    PrintResult("customer billing create", (!customerBilling.Find(425020528409010, customer)), testNum, ": \t");
}

static void TestCustomerBillingUpdate(CustomerBilling& a_cBilling, const string& a_usage, const string&a_sParty, Customer& a_cResult) {
    CdrRecord::RecordInfo values;
    FillValues(values, a_usage, a_sParty);
    CdrRecord record(values);
    a_cBilling.Update(record);

    static int testNum = 0;
    Customer customer;
    bool result = a_cBilling.Find(425020528409010, customer);
    PrintResult("customer billing update", (result && CheckResult(a_cResult, customer)), testNum, ": \t");
}

int main() {
    TestCustomerBillingCreate();
    
    CustomerBilling customerBilling(5);
    Customer customerResult;
    customerResult.m_incomingVC = 0; customerResult.m_outgoingVC = 2152;
    customerResult.m_totalDataTransf = 0; customerResult.m_totalDataReceive = 0;
    customerResult.m_totalSmsReceive = 0; customerResult.m_totalSmsSent = 0;
    SecondParty sParty; sParty.m_totalVC = 2152; sParty.m_totalSms = 0;
    customerResult.m_secondParties[61523827346] += sParty;

    TestCustomerBillingUpdate(customerBilling, "MOC", "61523827346", customerResult);

    customerResult.m_incomingVC += 2152;
    sParty.m_totalVC = 2152; sParty.m_totalSms = 0;
    customerResult.m_secondParties[61523827346] += sParty;
    TestCustomerBillingUpdate(customerBilling, "MTC", "61523827346", customerResult);

    customerResult.m_totalSmsSent += 1;
    sParty.m_totalVC = 0; sParty.m_totalSms = 1;
    customerResult.m_secondParties[496221540] += sParty;
    TestCustomerBillingUpdate(customerBilling, "SMS-MO", "496221540", customerResult);

    

    return 0;
}