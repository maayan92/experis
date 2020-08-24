#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "tcpServer.hpp"
#include "dataAggregatorHandler.hpp"
#include "queryHandler.hpp"
#include <iosfwd>

namespace kokfikoCDR {

class ServerManager : private experis::Uncopyable {
public:
    ServerManager(const char* a_ipAddress, size_t a_port, size_t a_numOfThreads = 2);
    //~ServerManager() = default;

    void RunServer();

    bool GetCustomerRecord(const experis::MSISDN& a_msisdn, data::Customer& a_customer);
    bool GetOperatorRecord(const experis::MCC_MNC& a_mccmnc, data::Operator& a_operator);

private:
    void setConnection(int& a_activity);

private:
    static const size_t DATA_SIZE = 200;

    TcpServer m_server;
    data::CustomerBilling m_customerBilling;
    data::OperatorBilling m_operatorBilling;
    data::DataAggregatorHandler m_dataAggregatorHandler;
    data::QueryHandler m_queryHandler; 
};

} // kokfikoCDR

#endif