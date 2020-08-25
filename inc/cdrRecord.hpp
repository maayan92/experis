#ifndef CDR_RECORD_H
#define CDR_RECORD_H

#include "typedefIdentifiers.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

namespace kofiko {

struct Imsi {
    experis::MCC m_mcc;
    experis::MNC m_mnc;
    experis::MSIN m_msin;
    bool operator==(const Imsi& a_imsi) const;
};

inline bool Imsi::operator==(const Imsi& a_imsi) const {
    return (m_mcc == a_imsi.m_mcc) && (m_mnc == a_imsi.m_mnc) && (m_msin == a_imsi.m_msin);
}

struct CdrRecord {
    static const size_t NUM_OF_RECORD_FIELDS = 11;
    
    CdrRecord(const std::vector<std::string>& a_info);
    CdrRecord();
    //CdrRecord(const CdrRecord& a_cdrRecord) = default;
    //~CdrRecord() = default;
    //CdrRecord& operator=(const CdrRecord& a_cdrRecord) = default;

    enum {
        SEQUENCE_NUM,
        IMSI,
        IMEI,
        USAGE_TYPE,
        MSISDN,
        CALL_DATE,
        CALL_TIME,
        DURATION,
        BYTE_RECEIVED,
        BYTE_TRANSMITTED,
        SECOND_PARTY_MSISDN
    };

    experis::SEQUENCE_NUM m_sequenceNum;
    Imsi m_imsi;
    experis::IMEI m_imei;
    experis::USAGE_TYPE m_usageType;
    experis::MSISDN m_msisdn;
    experis::CALL_DATE m_callDate;
    experis::CALL_TIME m_callTime;
    experis::DURATION m_duration;
    experis::BYTE_RECEIVED m_byteRecieved;
    experis::BYTE_TRANSMITTED m_byteTransmitted;
    experis::SECOND_PARTY_MSISDN m_secondPartyMsisdn;

    size_t m_recordSize;

private:    
    void setValues(const std::vector<std::string>& a_info);
    void calculateRecordSize(const std::vector<std::string>& a_info);
    void setImsi(const std::string& a_strImsi);
};

} // kofiko

#endif