#include "operatorBilling.hpp"
#include <iostream>
using namespace kofiko;
using namespace std;
using namespace data;

static void FillValues(vector<string>& a_values, const string& a_usage, const string&a_secondParty)
{
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

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs)
{
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static bool CheckResult(const Operator& a_wantResult, const Operator& a_result)
{
    return (a_result.m_incomingVC == a_wantResult.m_incomingVC) &&
            (a_result.m_outgoingVC == a_wantResult.m_outgoingVC) &&
            (a_result.m_incomingSms == a_wantResult.m_incomingSms) &&
            (a_result.m_outgoingSms == a_wantResult.m_outgoingSms);
}

// tests:

static void TestOperatorBillingCreate()
{
    OperatorBilling operatorBilling(5);
    static int testNum = 0;
    Operator mobileOp;
    PrintResult("mobileOp billing create", (!operatorBilling.Query("42502", mobileOp)), testNum, ": \t");
}

static void OperatorBillingUpdate(OperatorBilling& a_oBilling, const string& a_usage, const string&a_sParty, Operator& a_oResult)
{
    vector<string> values;
    FillValues(values, a_usage, a_sParty);
    CdrRecord record(values);
    a_oBilling.Update(record);

    static int testNum = 0;
    Operator mobileOp;
    bool result = a_oBilling.Query("42502", mobileOp);
    PrintResult("operator billing update", (result && CheckResult(a_oResult, mobileOp)), testNum, ": \t");
}

static void TestOperatorBillingUpdate()
{
    OperatorBilling operatorBilling(5);
    Operator operatorResult;
    operatorResult.m_incomingVC = 0; operatorResult.m_outgoingVC = 2152;
    operatorResult.m_incomingSms = 0; operatorResult.m_outgoingSms = 0;

    OperatorBillingUpdate(operatorBilling, "MOC", "615238273", operatorResult);

    operatorResult.m_incomingVC += 2152;
    OperatorBillingUpdate(operatorBilling, "MTC", "615238273", operatorResult);

    operatorResult.m_outgoingSms += 1;
    OperatorBillingUpdate(operatorBilling, "SMS-MO", "496221540", operatorResult);
}

int main()
{
    TestOperatorBillingCreate();
    TestOperatorBillingUpdate();
    
    return 0;
}