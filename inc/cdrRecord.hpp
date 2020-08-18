#ifndef CDR_RECORD_H
#define CDR_RECORD_H

#include <string>
#include <cstring>
#include <vector>
#include <sstream>

namespace kokfikoCDR {

struct Imsi {
    std::string m_mcc;
    std::string m_mnc;
    std::string m_msin;
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

    size_t m_sequenceNum;
    Imsi m_imsi;
    std::string m_imei;
    std::string m_usageType;
    size_t m_msisdn;
    std::string m_callDate;
    std::string m_callTime;
    size_t m_duration;
    size_t m_byteRecieved;
    size_t m_byteTransmitted;
    size_t m_secondPartyMsisdn;

    size_t m_recordSize;

private:    
    void setValues(const std::vector<std::string>& a_info);
    void calculateRecordSize(const std::vector<std::string>& a_info);
    void setImsi(const std::string& a_strImsi);
};

} // kokfikoCDR

#endif