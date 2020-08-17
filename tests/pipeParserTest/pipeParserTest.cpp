#include "pipeParser.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

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

static bool CompareRecords(const CdrRecord& a_left, const CdrRecord& a_right) {
    return (a_left.m_sequenceNum == a_right.m_sequenceNum) &&
            (a_left.m_imsi == a_right.m_imsi) &&
            (a_left.m_imei == a_right.m_imei) &&
            (a_left.m_usageType == a_right.m_usageType) &&
            (a_left.m_msisdn == a_right.m_msisdn) &&
            (a_left.m_callDate == a_right.m_callDate) &&
            (a_left.m_callTime == a_right.m_callTime) &&
            (a_left.m_duration == a_right.m_duration) &&
            (a_left.m_byteRecieved == a_right.m_byteRecieved) &&
            (a_left.m_byteTransmitted == a_right.m_byteTransmitted) &&
            (a_left.m_secondPartyMsisdn == a_right.m_secondPartyMsisdn) &&
            (a_left.m_recordSize == a_right.m_recordSize);
}

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static void TestParsing(const std::string& a_info, const CdrRecord& a_values) {
    static int testNum = 0;
    PipeParser pipeParser;
    CdrRecord result = pipeParser.Parsering(a_info);
    
    PrintResult("parsing", CompareRecords(result, a_values), testNum, ": \t");
}

} // kokfikoCDR

int main() {
    std::string buffer("123|425020528409010|35-209900-176148-1|MOC|9720528409042|DD/MM/YYYY|HH:MM:SS|2152|64|32|61523827346");
    vector<string> a_values;
    kokfikoCDR::FillValues(a_values);
    
    kokfikoCDR::CdrRecord result(a_values);

    kokfikoCDR::TestParsing(buffer, result);
    buffer += '|';
    kokfikoCDR::TestParsing(buffer, result);

    return 0;
}