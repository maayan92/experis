#ifndef CDR_SENDER_H
#define CDR_SENDER_H

#include "tcpClient.hpp"
#include "cdrRecord.hpp"

namespace kokfikoCDR {

class CdrSender {
public:
    CdrSender();
    //CdrSender(const CdrSender& a_cdrSender) = default;
    //~CdrSender() = default;
    //CdrSender& operator=(const CdrSender& a_cdrSender) = default;

    void SendMessage(const CdrRecord& a_record) const;

private:
    TcpClient m_client;
};

} // kokfikoCDR

#endif