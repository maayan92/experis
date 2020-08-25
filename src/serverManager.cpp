#include "serverManager.hpp"
#include "protocol.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
using namespace tcp;

namespace kofiko {

ServerManager::ServerManager(const char* a_ipAddress, size_t a_port, size_t a_numOfThreads) 
: m_server(a_ipAddress, a_port)
, m_customerBilling(a_numOfThreads)
, m_operatorBilling(a_numOfThreads)
, m_dataAggregatorHandler(&m_customerBilling, &m_operatorBilling)
, m_queryHandler(&m_customerBilling, &m_operatorBilling)
{
}

void ServerManager::RunServer() {
    m_server.SetSocketConnection();

    while(true) {
        char message[DATA_SIZE];
        try {
            m_server.GetData(message, DATA_SIZE);
            CdrRecord record = Protocol::UnPackMessage(message);
            m_dataAggregatorHandler.InsertNewRecord(record);
        }catch(const exceptions::ExcSocketIsClosed& exc) {
            return;
        }
        catch(const exception& exc) {
        }
    }
}

bool ServerManager::GetCustomerRecord(const experis::MSISDN& a_msisdn, data::Customer& a_customer)
{
    return m_queryHandler.GetCustomerQuery(a_msisdn, a_customer);
}

bool ServerManager::GetOperatorRecord(const experis::MCC_MNC& a_mccmnc, data::Operator& a_operator)
{
    return m_queryHandler.GetOperatorQuery(a_mccmnc, a_operator);
}

} // kofiko