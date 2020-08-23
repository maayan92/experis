#include "customerBilling.hpp"
#include "operatorBilling.hpp"
#include <iostream>
#include <pthread.h>
using namespace std;
using namespace data;
using namespace kokfikoCDR;

#define NUM_OT_THREADS 3

struct Billing {
    Billing() : m_customerBilling(NUM_OT_THREADS), m_operatorBilling(NUM_OT_THREADS) {}
    CustomerBilling m_customerBilling;
    OperatorBilling m_operatorBilling;
};

static void FillValues(vector<string>& a_values, const string& a_msisdn, const string& a_usage, const string&a_secondParty) {
    a_values.push_back("123");
    a_values.push_back("425020162782277");
    a_values.push_back("35-209900-176148-1");
    a_values.push_back(a_usage);
    a_values.push_back(a_msisdn);
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

static void UpdateWithNewRecord(void* a_billing, const string& a_customer, const string& a_usage, const string&a_sParty) {
    vector<string> values;
    FillValues(values, a_customer, a_usage, a_sParty);
    CdrRecord record(values);

    static_cast<Billing*>(a_billing)->m_customerBilling.Update(record);
    static_cast<Billing*>(a_billing)->m_operatorBilling.Update(record);
}

// threads

static void* TestThreadsUpsertFirst(void* a_billing)
{
    for (size_t i = 0 ; i < 10 ; ++i) {
        UpdateWithNewRecord(a_billing, "4250162782277", "MOC", "615238273");
        UpdateWithNewRecord(a_billing, "4250162782277", "X", "496221540");
        UpdateWithNewRecord(a_billing, "9720528409042", "MTC", "615238273");
        UpdateWithNewRecord(a_billing, "9720528409042", "SMS-MO", "615238273");
    }
    
    pthread_exit(NULL);
    return 0;
}

static void* TestThreadsUpsertSecond(void* a_billing)
{
    for (size_t i = 0 ; i < 10 ; ++i) {
        UpdateWithNewRecord(a_billing, "4250162782277", "MTC", "615238273");
        UpdateWithNewRecord(a_billing, "9720528409042", "MOC", "496221540");
        UpdateWithNewRecord(a_billing, "9720528409042", "U", "496221540");
    }
    
    pthread_exit(NULL);
    return 0;
}

static void* TestThreadsUpsertTheard(void* a_billing)
{
    for (size_t i = 0 ; i < 10 ; ++i) {
        UpdateWithNewRecord(a_billing, "4250162782277", "SMS-MT", "615238273");
        UpdateWithNewRecord(a_billing, "4250162782277", "D", "496221540");
        UpdateWithNewRecord(a_billing, "9720528409042", "SMS-MT", "615238273");
    }
    
    pthread_exit(NULL);
    return 0;
}

// check result

static bool CompareSParty(const pair<experis::MSISDN, SecondParty>& a_laft, const pair<experis::MSISDN, SecondParty>& a_right) {
    return a_laft.second == a_right.second;
}

static bool CheckResultCustomer(const Customer& a_wantResult, Customer& a_result) {
    return (a_result.m_incomingVC == a_wantResult.m_incomingVC) &&
            (a_result.m_outgoingVC == a_wantResult.m_outgoingVC) &&
            (a_result.m_totalDataReceive == a_wantResult.m_totalDataReceive) &&
            (a_result.m_totalDataTransf == a_wantResult.m_totalDataTransf) &&
            (a_result.m_totalSmsReceive == a_wantResult.m_totalSmsReceive) &&
            (a_result.m_totalSmsSent == a_wantResult.m_totalSmsSent) &&
            (equal(a_result.m_secondParties.begin(), a_result.m_secondParties.end(), a_wantResult.m_secondParties.begin(), CompareSParty));
}

static bool CheckResultCustomer(const Billing& a_billing) {
    Customer customerResult;
    customerResult.m_incomingVC = 21520; customerResult.m_outgoingVC = 21520;
    customerResult.m_totalDataTransf = 320; customerResult.m_totalDataReceive = 640;
    customerResult.m_totalSmsReceive = 10; customerResult.m_totalSmsSent = 0;
    SecondParty sParty; sParty.m_totalVC = 43040; sParty.m_totalSms = 10;
    customerResult.m_secondParties["615238273"] += sParty;
    sParty.m_totalVC = 0; sParty.m_totalSms = 0;
    customerResult.m_secondParties["496221540"] += sParty;

    Customer customer;
    a_billing.m_customerBilling.Query("4250162782277", customer);
    return CheckResultCustomer(customerResult, customer);
}

static bool CheckResultOperator(const Operator& a_wantResult, const Operator& a_result) {
    return (a_result.m_incomingVC == a_wantResult.m_incomingVC) &&
            (a_result.m_outgoingVC == a_wantResult.m_outgoingVC) &&
            (a_result.m_incomingSms == a_wantResult.m_incomingSms) &&
            (a_result.m_outgoingSms == a_wantResult.m_outgoingSms);
}

static bool CheckResultOperator(const Billing& a_billing) {
    Operator operatorResult;
    operatorResult.m_incomingVC = 43040; operatorResult.m_outgoingVC = 43040;
    operatorResult.m_incomingSms = 20; operatorResult.m_outgoingSms = 10;

    Operator mobileOp;
    a_billing.m_operatorBilling.Query("42502", mobileOp);
    return CheckResultOperator(operatorResult, mobileOp);
}

int main()
{
    vector<string> usage;
    usage.push_back("MOC"); usage.push_back("MTC"); usage.push_back("SMS-MO");
    usage.push_back("SMS-MT"); usage.push_back("D"); usage.push_back("U");
    Billing billing;

    pthread_t threadsUpsert[NUM_OT_THREADS];
    if(0 < pthread_create(&threadsUpsert[0], NULL, TestThreadsUpsertFirst, (void*)&billing)) {
        cout << "thread create failed!!" << '\n';
        return 1;
    }
    if(0 < pthread_create(&threadsUpsert[1], NULL, TestThreadsUpsertSecond, (void*)&billing)) {
        cout << "thread create failed!!" << '\n';
        return 1;
    }
    if(0 < pthread_create(&threadsUpsert[2], NULL, TestThreadsUpsertTheard, (void*)&billing)) {
        cout << "thread create failed!!" << '\n';
        return 1;
    }

    for (size_t i = 0 ; i < NUM_OT_THREADS ; ++i) {
        if(0 > pthread_join(threadsUpsert[i], NULL)) {
            cout << "thread join failed!!" << '\n';
            return 1;
        }
    }

    int testNum = 0;
    PrintResult("customer billing", CheckResultCustomer(billing), testNum, ": \t");
    PrintResult("operator billing", CheckResultOperator(billing), --testNum, ": \t");

    return 0;
}