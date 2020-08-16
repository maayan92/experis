#include "pipeParser.hpp"
#include "testFunc.hpp"
#include <iostream>

typedef kokfikoCDR::CdrRecord::RecordInfo RecordInfo;

namespace kokfikoCDR {

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

static void TestParsing(const std::string& a_info, const CdrRecord& a_values) {
    static int testNum = 0;
    PipeParser pipeParser;
    CdrRecord result = pipeParser.Parsering(a_info);
    
    PrintResult("parsing", CompareRecords(result, a_values), testNum);
}

} // kokfikoCDR

int main() {
    std::string buffer("123|425020528409010|35-209900-176148-1|MOC|9720528409042|DD/MM/YYYY|HH:MM:SS|2152|64|32|61523827346");
    RecordInfo a_values;
    kokfikoCDR::FillValues(a_values);
    
    kokfikoCDR::CdrRecord result(a_values);

    kokfikoCDR::TestParsing(buffer, result);
    buffer += '|';
    kokfikoCDR::TestParsing(buffer, result);

    return 0;
}