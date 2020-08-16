#include "cdrRecord.hpp"
#include "testFunc.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

typedef kokfikoCDR::CdrRecord::RecordInfo RecordInfo;

namespace kokfikoCDR {

static string fromNumToStr(size_t a_value) {
    stringstream numToStr;
    numToStr << a_value;
    return numToStr.str();
}

static bool CheckRecord(CdrRecord a_record, RecordInfo& a_values) {
    int position = 0;
    return (fromNumToStr(a_record.m_sequenceNum) == a_values[position]) &&
            (fromNumToStr(a_record.m_imsi) == a_values[++position].c_str()) &&
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

static void TestRecord(RecordInfo& a_values) {
    kokfikoCDR::CdrRecord record(a_values);
    static int testNum = 0;
    PrintResult("record create", CheckRecord(record, a_values), testNum);
}

} // kokfikoCDR

int main() {
    kokfikoCDR::CdrRecord::RecordInfo values;
    kokfikoCDR::FillValues(values);
    kokfikoCDR::TestRecord(values);

    return 0;
}