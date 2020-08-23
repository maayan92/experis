#include "cdrRecord.hpp"

namespace kokfikoCDR {

CdrRecord::CdrRecord(const std::vector<std::string>& a_info)
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

CdrRecord::CdrRecord()
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

void CdrRecord::setValues(const std::vector<std::string>& a_info) {
    setImsi(a_info[IMSI]);
    std::istringstream(a_info[SEQUENCE_NUM]) >> m_sequenceNum;
    std::istringstream(a_info[MSISDN]) >> m_msisdn;
    std::istringstream(a_info[DURATION]) >> m_duration;
    std::istringstream(a_info[BYTE_RECEIVED]) >> m_byteRecieved;
    std::istringstream(a_info[BYTE_TRANSMITTED]) >> m_byteTransmitted;
    std::istringstream(a_info[SECOND_PARTY_MSISDN]) >> m_secondPartyMsisdn;
}

void CdrRecord::setImsi(const std::string& a_strImsi) {
    m_imsi.m_mcc = std::string(a_strImsi.substr(0, 3));
    m_imsi.m_mnc = std::string(a_strImsi.substr(3, 2));
    m_imsi.m_msin = std::string(a_strImsi.substr(5));
}

void CdrRecord::calculateRecordSize(const std::vector<std::string>& a_info) {
    for(size_t position = 0 ; position < a_info.size() ; ++position) {
        m_recordSize += strlen(a_info[position].c_str());
    }
}

} // kokfikoCDR