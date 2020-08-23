#ifndef TYPEDEF_IDENTIFIERS_H
#define TYPEDEF_IDENTIFIERS_H

#include <iosfwd>

namespace experis {

typedef std::string MCC;
typedef std::string MNC;
typedef std::string MSIN;

typedef std::string MSISDN;
typedef std::string SEQUENCE_NUM;
typedef std::string IMEI;
typedef std::string USAGE_TYPE;
typedef std::string CALL_DATE;
typedef std::string CALL_TIME;
typedef size_t DURATION;
typedef size_t BYTE_RECEIVED;
typedef size_t BYTE_TRANSMITTED;
typedef std::string SECOND_PARTY_MSISDN;

typedef size_t OUT_GOING_VC;
typedef size_t INCOMING_VC;
typedef size_t DATA_TRANSFERRED;
typedef size_t DATA_RECEIVED;
typedef size_t SMS_SENT;
typedef size_t SMS_RECEIVED;

} // experis

#endif