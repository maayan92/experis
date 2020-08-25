#ifndef CDR_SENDER_H
#define CDR_SENDER_H

#include "tcpClient.hpp"
#include "cdrRecord.hpp"
#include "uncopyable.hpp"

namespace kofiko {

class CdrSender : private experis::Uncopyable {
public:
    CdrSender(const char* a_ipAddress, size_t a_port);
    //~CdrSender() = default;

    void SendMessage(const CdrRecord& a_record) const;

private:
    TcpClient m_client;
};

} // kofiko

#endif