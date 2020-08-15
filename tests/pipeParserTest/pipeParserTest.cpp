#include "pipeParser.hpp"
#include <iostream>

namespace kokfikoCDR {

static bool CompareRecord(CdrRecord a_left, CdrRecord a_right) {
    return (a_left.m_sequenceNum == a_right.m_sequenceNum) &&
            (a_left.m_imsi == a_right.m_imsi) &&
            (a_left.m_imei == a_right.m_imei) &&
            (a_left.m_msisdn == a_right.m_msisdn) &&
            (a_left.m_callDate == a_right.m_callDate) &&
            (a_left.m_callTime == a_right.m_callTime) &&
            (a_left.m_duration == a_right.m_duration) &&
            (a_left.m_byteRecieved == a_right.m_byteRecieved) &&
            (a_left.m_byteTransmitted == a_right.m_byteTransmitted) &&
            (a_left.m_secondPartyMsisdn == a_right.m_secondPartyMsisdn) &&
            (a_left.m_recordSize == a_right.m_recordSize);
}

static void TestParsing(std::string a_info, CdrRecord a_wantedResult) {
    static int testNum = 0;
    PipeParser pipeParser;
    CdrRecord result = pipeParser.Parsering(a_info);
    
    std::cout << "parsing, test number " <<  ++testNum << ": \t"
            << (CompareRecord(result, a_wantedResult) ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << std::endl;
}

} // kokfikoCDR

int main() {
    std::string buffer("123|425020528409010|35-209900-176148-1|MOC|​9720528409042|DD/MM/YYYY|HH:MM:SS|2152|64|32|61523827346");
    kokfikoCDR::CdrRecord::RecordInfo wantedResult;
    wantedResult.push_back("123");
    wantedResult.push_back("425020528409010");
    wantedResult.push_back("35-209900-176148-1");
    wantedResult.push_back("MOC");
    wantedResult.push_back("​9720528409042");
    wantedResult.push_back("DD/MM/YYYY");
    wantedResult.push_back("HH:MM:SS");
    wantedResult.push_back("2152");
    wantedResult.push_back("64");
    wantedResult.push_back("32");
    wantedResult.push_back("61523827346");
    
    kokfikoCDR::CdrRecord result(wantedResult);

    kokfikoCDR::TestParsing(buffer, result);
    buffer += '|';
    kokfikoCDR::TestParsing(buffer, result);

    return 0;
}