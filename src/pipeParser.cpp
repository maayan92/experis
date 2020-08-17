#include "pipeParser.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

const int PipeParser::LUT[] = {CdrRecord::SEQUENCE_NUM, CdrRecord::IMSI, CdrRecord::IMEI, CdrRecord::USAGE_TYPE, CdrRecord::MSISDN, \
                     CdrRecord::CALL_DATE, CdrRecord::CALL_TIME, CdrRecord::DURATION, CdrRecord::BYTE_RECEIVED, \
                     CdrRecord::BYTE_TRANSMITTED, CdrRecord::SECOND_PARTY_MSISDN };

CdrRecord PipeParser::Parsering(const string& a_buffer) {
    vector<string> info(NUM_OF_RECORD_FIELDS);
    initializeInfo(info, a_buffer);
    return CdrRecord(info);
}

void PipeParser::initializeInfo(vector<string>& a_info, const string& a_buffer) {
    size_t fromPos = 0;
    size_t toPos = a_buffer.find(delimiter);
    size_t i = 0;

    while(toPos != string::npos) {
        string token(a_buffer,fromPos , toPos - fromPos);
        if(token.size() > 0) {
            a_info[LUT[i++]] = token;
        }

        fromPos = toPos + 1;
        toPos = a_buffer.find(delimiter, fromPos);
    }

    if(fromPos < a_buffer.size()) {
        string token(a_buffer,fromPos , a_buffer.size() - fromPos);
        a_info[LUT[i]] = token;
    }
}

} // kokfikoCDR