#include "protocol.hpp"
#include "exceptions.hpp"
using namespace std;
using namespace exceptions;

namespace tcp {

static string fromNumToStr(size_t a_value) {
    stringstream numToStr;
    numToStr << a_value;
    return numToStr.str();
}

static void setNumberAsStrToBuffer(size_t a_value, char* a_buffer, size_t& a_position) {
    string numToStr = fromNumToStr(a_value);
    size_t valSize = strlen(numToStr.c_str());
    a_buffer[++a_position] = valSize;
    a_buffer[a_position + 1] = '\0';
    strncat(a_buffer, numToStr.c_str(), valSize);
    a_position += valSize;
}

static void setStrToBuffer(std::string a_value, char* a_buffer, size_t& a_position) {
    size_t valSize = strlen(a_value.c_str());
    a_buffer[++a_position] = valSize;
    a_buffer[a_position + 1] = '\0';
    strncat(a_buffer, a_value.c_str(), valSize);
    a_position += valSize;
}

void Protocol::PackMessage(const Protocol::Record& a_record, char* a_buffer, size_t a_bufferSize) {
    if(a_bufferSize < (a_record.m_recordSize + Protocol::NUM_OF_RECORDS)) {
        throw ExcBufferSizeTooSmall();
    }
    size_t position = 0;
    a_buffer[position] = a_record.m_recordSize + Protocol::NUM_OF_RECORDS;

    setNumberAsStrToBuffer(a_record.m_sequenceNum, a_buffer, position);
    setNumberAsStrToBuffer(a_record.m_imsi, a_buffer, position);
    setStrToBuffer(a_record.m_imei, a_buffer, position);
    setStrToBuffer(a_record.m_usageType, a_buffer, position);
    setNumberAsStrToBuffer(a_record.m_msisdn, a_buffer, position);
    setStrToBuffer(a_record.m_callDate, a_buffer, position);
    setStrToBuffer(a_record.m_callTime, a_buffer, position);
    setNumberAsStrToBuffer(a_record.m_duration, a_buffer, position);
    setNumberAsStrToBuffer(a_record.m_byteRecieved, a_buffer, position);
    setNumberAsStrToBuffer(a_record.m_byteTransmitted, a_buffer, position);
    setNumberAsStrToBuffer(a_record.m_secondPartyMsisdn, a_buffer, position);
}

} // tcp