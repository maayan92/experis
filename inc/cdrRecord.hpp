#ifndef CDR_RECORD_H
#define CDR_RECORD_H

#include <string>
#include <cstring>
#include <vector>
#include <sstream>

namespace kokfikoCDR {

struct CdrRecord {
    typedef std::string String;
    typedef std::vector<String> RecordInfo;

    CdrRecord(const RecordInfo& a_info);
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
    size_t m_imsi;
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
    inline void setValues(const RecordInfo& a_info);
    inline void calculateRecordSize(const RecordInfo& a_info);
};

inline CdrRecord::CdrRecord(const RecordInfo& a_info)
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

inline void CdrRecord::setValues(const RecordInfo& a_info) {
    std::istringstream(a_info[SEQUENCE_NUM]) >> m_sequenceNum;
    std::istringstream(a_info[IMSI]) >> m_imsi;
    std::istringstream(a_info[MSISDN]) >> m_msisdn;
    std::istringstream(a_info[DURATION]) >> m_duration;
    std::istringstream(a_info[BYTE_RECEIVED]) >> m_byteRecieved;
    std::istringstream(a_info[BYTE_TRANSMITTED]) >> m_byteTransmitted;
    std::istringstream(a_info[SECOND_PARTY_MSISDN]) >> m_secondPartyMsisdn;
}

inline void CdrRecord::calculateRecordSize(const RecordInfo& a_info) {
    for(size_t position = 0 ; position < a_info.size() ; ++position) {
        m_recordSize += strlen(a_info[position].c_str());
    }
}

} // kokfikoCDR

#endif