#include "pipeParser.hpp"
#include "exceptions.hpp"
#include <iostream>
using namespace std;

namespace kofiko {

const int PipeParser::LUT[] = {CdrRecord::SEQUENCE_NUM, CdrRecord::IMSI, CdrRecord::IMEI, CdrRecord::USAGE_TYPE, CdrRecord::MSISDN, \
                     CdrRecord::CALL_DATE, CdrRecord::CALL_TIME, CdrRecord::DURATION, CdrRecord::BYTE_RECEIVED, \
                     CdrRecord::BYTE_TRANSMITTED, CdrRecord::SECOND_PARTY_MSISDN };

CdrRecord PipeParser::Parsering(const string& a_buffer) {
    vector<string> info(CdrRecord::NUM_OF_RECORD_FIELDS);
    initializeInfo(info, a_buffer);
    return CdrRecord(info);
}

PipeParser::~PipeParser() {
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
    fillTheRest(a_info, a_buffer, fromPos, i);
    
    if(isNotValidationValue(a_info)) {
        throw exceptions::ExcInvalidRecordValue();
    }
}

bool PipeParser::isNotValidationValue(vector<string>& a_info)
{
    return ((a_info[CdrRecord::IMSI].size() > 15) ||
            (a_info[CdrRecord::MSISDN].size() > 15) ||
            (a_info[CdrRecord::SECOND_PARTY_MSISDN].size() > 15));
}

void PipeParser::fillTheRest(vector<string>& a_info, const string& a_buffer, size_t a_fromPos, size_t a_pos)
{
    if(a_fromPos < a_buffer.size()) {
        string token(a_buffer,a_fromPos , a_buffer.size() - a_fromPos);
        a_info[LUT[a_pos++]] = token;
    }
    while(a_pos < CdrRecord::NUM_OF_RECORD_FIELDS) {
        a_info[LUT[a_pos++]] = " ";
    }
}

} // kofiko