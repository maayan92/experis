#include "cdrSender.hpp"
#include "protocol.hpp"
using namespace tcp;

namespace kokfikoCDR {

CdrSender::CdrSender(const char* a_ipAddress, size_t a_port)
: m_client(a_ipAddress, a_port) {
    m_client.ConnectToServer();
}

void CdrSender::SendMessage(const CdrRecord& a_record) const {
    size_t bufferSize = a_record.m_recordSize + Protocol::NUM_OF_RECORDS;
    char* packedMsg = new char[bufferSize + 1];
    Protocol::PackMessage(a_record, packedMsg, bufferSize + 1);
    m_client.SendMessage(packedMsg);
    delete packedMsg;
}

} // kokfikoCDR