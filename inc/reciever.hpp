#ifndef RECIEVER_H
#define RECIEVER_H

#include "tcpServer.hpp"
#include "cdrRecord.hpp"
#include "protocol.hpp"

namespace kokfikoCDR {

class Reciever {
public:
    Reciever(TcpServer& a_server, std::ostream& a_outPutRecords);
    //Reciever(const Reciever& a_reciever) = default;
    //~Reciever() = default;
    //Reciever& operator=(const Reciever& a_reciever) = default;

    inline void operator()(int a_clientSocket);

private:
    inline void printToFile(CdrRecord& record);

private:
    static const size_t DATA_SIZE = 200;

    TcpServer& m_server;
    std::ostream& m_outPutRecords;
};


inline Reciever::Reciever(TcpServer& a_server, std::ostream& a_outPutRecords) 
: m_server(a_server)
, m_outPutRecords(a_outPutRecords)
{
}

inline void Reciever::operator()(int a_clientSocket) {
    char message[DATA_SIZE];
    m_server.GetData(message, DATA_SIZE, a_clientSocket);
    CdrRecord record = tcp::Protocol::UnPackMessage(message);

    printToFile(record);
}

inline void Reciever::printToFile(CdrRecord& record) {
    m_outPutRecords << record.m_sequenceNum  << '|';
    m_outPutRecords << record.m_imsi  << '|';
    m_outPutRecords << record.m_imei  << '|';
    m_outPutRecords << record.m_usageType  << '|';
    m_outPutRecords << record.m_msisdn  << '|';
    m_outPutRecords << record.m_callDate  << '|';
    m_outPutRecords << record.m_callTime  << '|';
    m_outPutRecords << record.m_duration  << '|';
    m_outPutRecords << record.m_byteRecieved  << '|';
    m_outPutRecords << record.m_byteTransmitted  << '|';
    m_outPutRecords << record.m_secondPartyMsisdn  << '|' << std::endl;
}


} //kokfikoCDR

#endif