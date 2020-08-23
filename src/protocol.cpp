#include "protocol.hpp"
#include "exceptions.hpp"
using namespace std;
using namespace exceptions;

#include <iostream>

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

static void setStrToBuffer(const std::string& a_value, char* a_buffer, size_t& a_position) {
    size_t valSize = strlen(a_value.c_str());
    a_buffer[++a_position] = valSize;
    a_buffer[a_position + 1] = '\0';
    strncat(a_buffer, a_value.c_str(), valSize);
    a_position += valSize;
}

static void setImsiToBuffer(const kokfikoCDR::Imsi& a_imsi, char* a_buffer, size_t& a_position) {
    string imsi(a_imsi.m_mcc);
    imsi += a_imsi.m_mnc;
    imsi += a_imsi.m_msin;
    size_t valSize = strlen(imsi.c_str());
    a_buffer[++a_position] = valSize;
    a_buffer[a_position + 1] = '\0';
    strncat(a_buffer, imsi.c_str(), valSize);
    a_position += valSize;
}

void Protocol::PackMessage(const Protocol::Record& a_record, char* a_buffer, size_t a_bufferSize) {
    if(a_bufferSize < (a_record.m_recordSize + Protocol::NUM_OF_RECORDS)) {
        throw ExcBufferSizeTooSmall();
    }
    size_t position = 0;
    a_buffer[position] = a_record.m_recordSize + Protocol::NUM_OF_RECORDS;

    setNumberAsStrToBuffer(a_record.m_sequenceNum, a_buffer, position);
    setImsiToBuffer(a_record.m_imsi, a_buffer, position);
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

static size_t setStrToNumberFromBuffer(const char* a_msg, size_t& a_position, size_t a_size) {
    size_t result;
    istringstream(string(a_msg, ++a_position, a_size)) >> result;
    a_position += a_size;
    return result;
}

static string setStrFromBuffer(const char* a_msg, size_t& a_position, size_t a_size) {
    string result(a_msg, ++a_position, a_size);
    a_position += a_size;
    return result;
}

static kokfikoCDR::Imsi setStrToImsiFromBuffer(const char* a_msg, size_t& a_position, size_t a_size) {
    kokfikoCDR::Imsi imsi;
    imsi.m_mcc = std::string(a_msg[0], 3);
    imsi.m_mnc = string(a_msg[3], 2);
    imsi.m_msin = string(a_msg[5], 10);
    return imsi;
}

Protocol::Record Protocol::UnPackMessage(const char* a_msg) {
    Record record;
    size_t position = 1;

    record.m_recordSize += a_msg[position];
    record.m_sequenceNum = setStrToNumberFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_imsi = setStrToImsiFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_imei = setStrFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_usageType = setStrFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_msisdn = setStrToNumberFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_callDate = setStrFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_callTime = setStrFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_duration = setStrToNumberFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_byteRecieved = setStrToNumberFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_byteTransmitted = setStrToNumberFromBuffer(a_msg, position, a_msg[position]);
    record.m_recordSize += a_msg[position];
    record.m_secondPartyMsisdn = setStrToNumberFromBuffer(a_msg, position, a_msg[position]);

    return record;
}

} // tcp