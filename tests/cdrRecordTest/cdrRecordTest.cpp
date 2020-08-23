#include "cdrRecord.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace kokfikoCDR;
using namespace std;

static void FillValues(vector<string>& a_values) {
    a_values.push_back("123");
    a_values.push_back("425020528409010");
    a_values.push_back("35-209900-176148-1");
    a_values.push_back("MOC");
    a_values.push_back("9720528409042");
    a_values.push_back("DD/MM/YYYY");
    a_values.push_back("HH:MM:SS");
    a_values.push_back("2152");
    a_values.push_back("64");
    a_values.push_back("32");
    a_values.push_back("61523827346");
}

static string fromNumToStr(size_t a_value) {
    stringstream numToStr;
    numToStr << a_value;
    return numToStr.str();
}

static string getNumFromImsi(const Imsi& a_imsi) {
    stringstream numToStr;
    numToStr << a_imsi.m_mcc << a_imsi.m_mnc << a_imsi.m_msin;
    return numToStr.str();
}

static bool CheckRecord(const CdrRecord& a_record, const vector<string>& a_values) {
    int position = 0;
    return (fromNumToStr(a_record.m_sequenceNum) == a_values[position]) &&
            (getNumFromImsi(a_record.m_imsi) == a_values[++position].c_str()) &&
            (a_record.m_imei == a_values[++position].c_str()) &&
            (a_record.m_usageType == a_values[++position].c_str()) &&
            (fromNumToStr(a_record.m_msisdn) == a_values[++position].c_str()) &&
            (a_record.m_callDate == a_values[++position].c_str()) &&
            (a_record.m_callTime == a_values[++position].c_str()) &&
            (fromNumToStr(a_record.m_duration) == a_values[++position].c_str()) &&
            (fromNumToStr(a_record.m_byteRecieved) == a_values[++position].c_str()) &&
            (fromNumToStr(a_record.m_byteTransmitted) == a_values[++position].c_str()) &&
            (fromNumToStr(a_record.m_secondPartyMsisdn) == a_values[++position].c_str());
}

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static void TestRecord(vector<string>& a_values) {
    kokfikoCDR::CdrRecord record(a_values);
    static int testNum = 0;
    PrintResult("record create", CheckRecord(record, a_values), testNum, ": \t");
}

int main() {
    vector<string> values;
    FillValues(values);
    TestRecord(values);

    return 0;
}