#ifndef CDR_RECORD_H
#define CDR_RECORD_H

#include <string>
#include <cstring>
#include <vector>
#include <sstream>

namespace kokfikoCDR {

struct Imsi {
    size_t m_mcc;
    size_t m_mnc;
    size_t m_msin;
    bool operator==(const Imsi& a_imsi) const;
};

inline bool Imsi::operator==(const Imsi& a_imsi) const {
    return (m_mcc == a_imsi.m_mcc) && (m_mnc == a_imsi.m_mnc) && (m_msin == a_imsi.m_msin);
}

struct CdrRecord {
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

inline CdrRecord::CdrRecord(const std::vector<std::string>& a_info)
: m_sequenceNum()
, m_imsi()
, m_imei(a_info[IMEI])
, m_usageType(a_info[USAGE_TYPE])
, m_msisdn()
, m_callDate(a_info[CALL_DATE])
, m_callTime(a_info[CALL_TIME])
, m_duration()
, m_byteRecieved()
, m_byteTransmitted()
, m_secondPartyMsisdn()
, m_recordSize() {
    setValues(a_info);
    calculateRecordSize(a_info);
}

inline CdrRecord::CdrRecord()
: m_sequenceNum()
, m_imsi()
, m_imei()
, m_usageType()
, m_msisdn()
, m_callDate()
, m_callTime()
, m_duration()
, m_byteRecieved()
, m_byteTransmitted()
, m_secondPartyMsisdn()
, m_recordSize() {
}

inline void CdrRecord::setValues(const std::vector<std::string>& a_info) {
    setImsi(a_info[IMSI]);
    std::istringstream(a_info[SEQUENCE_NUM]) >> m_sequenceNum;
    std::istringstream(a_info[MSISDN]) >> m_msisdn;
    std::istringstream(a_info[DURATION]) >> m_duration;
    std::istringstream(a_info[BYTE_RECEIVED]) >> m_byteRecieved;
    std::istringstream(a_info[BYTE_TRANSMITTED]) >> m_byteTransmitted;
    std::istringstream(a_info[SECOND_PARTY_MSISDN]) >> m_secondPartyMsisdn;
}

inline void CdrRecord::setImsi(const std::string& a_strImsi) {
    std::istringstream(a_strImsi.substr(0, 3)) >> m_imsi.m_mcc;
    std::istringstream(a_strImsi.substr(3, 2)) >> m_imsi.m_mcc;
    std::istringstream(a_strImsi.substr(5)) >> m_imsi.m_mcc;
}

inline void CdrRecord::calculateRecordSize(const std::vector<std::string>& a_info) {
    for(size_t position = 0 ; position < a_info.size() ; ++position) {
        m_recordSize += strlen(a_info[position].c_str());
    }
}

} // kokfikoCDR

#endif