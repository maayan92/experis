#include "operatorBilling.hpp"
#include <iostream>
using namespace kokfikoCDR;
using namespace std;
using namespace data;

static void FillValues(CdrRecord::RecordInfo& a_values, const string& a_usage, const string&a_secondParty) {
    a_values.push_back("123");
    a_values.push_back("425020528409010");
    a_values.push_back("35-209900-176148-1");
    a_values.push_back(a_usage);
    a_values.push_back(a_secondParty);
    a_values.push_back("DD/MM/YYYY");
    a_values.push_back("HH:MM:SS");
    a_values.push_back("2152");
    a_values.push_back("64");
    a_values.push_back("32");
    a_values.push_back("61523827346");
}

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static bool CheckResult(const Operator& a_wantResult, const Operator& a_result) {
    return (a_result.m_incomingVC == a_wantResult.m_incomingVC) &&
            (a_result.m_outgoingVC == a_wantResult.m_outgoingVC) &&
            (a_result.m_incomingSms == a_wantResult.m_incomingSms) &&
            (a_result.m_outgoingSms == a_wantResult.m_outgoingSms);
}

// tests:

static void TestOperatorBillingCreate() {
    OperatorBilling operatorBilling(5);
    static int testNum = 0;
    Operator mobileOp;
    PrintResult("mobileOp billing create", (!operatorBilling.Find(425020528409010, mobileOp)), testNum, ": \t");
}

static void TestOperatorBillingUpdate(OperatorBilling& a_oBilling, const string& a_usage, const string&a_sParty, Operator& a_oResult) {
    CdrRecord::RecordInfo values;
    FillValues(values, a_usage, a_sParty);
    CdrRecord record(values);
    a_oBilling.Update(record);

    static int testNum = 0;
    Operator mobileOp;
    bool result = a_oBilling.Find(425020528409010, mobileOp);
    PrintResult("operator billing update", (result && CheckResult(a_oResult, mobileOp)), testNum, ": \t");
}


int main()
{
    TestOperatorBillingCreate();
    
    OperatorBilling operatorBilling(5);
    Operator operatorResult;
    operatorResult.m_incomingVC = 0; operatorResult.m_outgoingVC = 2152;
    operatorResult.m_incomingSms = 0; operatorResult.m_outgoingSms = 0;

    TestOperatorBillingUpdate(operatorBilling, "MOC", "9720528409042", operatorResult);

    operatorResult.m_incomingVC += 2152;
    TestOperatorBillingUpdate(operatorBilling, "MTC", "9720528409042", operatorResult);

    operatorResult.m_outgoingSms += 1;
    TestOperatorBillingUpdate(operatorBilling, "SMS-MO", "4320528409088", operatorResult);
    return 0;
}