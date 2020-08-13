#ifndef CDR_RECORD_H
#define CDR_RECORD_H

#include <string>
#include <vector>
#include <sstream>

namespace kokfikoCDR {

struct CdrRecord {
    typedef std::string String;
    typedef std::vector<String> RecordInfo;

    CdrRecord(RecordInfo a_info);
    //CdrRecord(const CdrRecord& a_cdrRecord) = default;
    //~CdrRecord() = default;
    //CdrRecord& operator=(const CdrRecord& a_cdrRecord) = default;

    enum {
        SEQUENCE_NUM,
        IMSI,
        IMEI,
        USAGE_TYPE,
        MSISN,
        CALL_DATE,
        CALL_TIME,
        DURATION,
        BYTE_RECEIVED,
        BYTE_TRANSMITTED,
        SECOND_PARTY_MSISN
    };

    void setValues(RecordInfo a_info);

    size_t m_sequenceNum;
    size_t m_imsi;
    std::string m_imei;
    std::string m_usageType;
    size_t m_msisn;
    std::string m_callDate;
    std::string m_callTime;
    size_t m_duration;
    size_t m_byteRecieved;
    size_t m_byteTransmitted;
    size_t m_secondPartyMsisn;
};

inline CdrRecord::CdrRecord(RecordInfo a_info)
: m_sequenceNum()
, m_imsi()
, m_imei(a_info[IMEI])
, m_usageType(a_info[USAGE_TYPE])
, m_msisn()
, m_callDate(a_info[CALL_DATE])
, m_callTime(a_info[CALL_TIME])
, m_duration()
, m_byteRecieved()
, m_byteTransmitted()
, m_secondPartyMsisn() {

    setValues(a_info);
}

inline void CdrRecord::setValues(RecordInfo a_info) {
    std::istringstream setStrToNum(a_info[SEQUENCE_NUM]);
    std::istringstream(a_info[SEQUENCE_NUM]) >> m_sequenceNum;
    setStrToNum.str(a_info[IMSI]);
    setStrToNum >> m_imsi;
    
    setStrToNum.str(a_info[MSISN]);
    setStrToNum >> m_msisn;

    setStrToNum.str(a_info[DURATION]);
    setStrToNum >> m_duration;
    
    setStrToNum.str(a_info[BYTE_RECEIVED]);
    setStrToNum >> m_byteRecieved;
    
    setStrToNum.str(a_info[BYTE_TRANSMITTED]);
    setStrToNum >> m_byteTransmitted;
    
    setStrToNum.str(a_info[SECOND_PARTY_MSISN]);
    setStrToNum >> m_secondPartyMsisn;
}

} // kokfikoCDR

#endif