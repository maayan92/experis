#include "serverManager.hpp"
#include "protocol.hpp"
#include "exceptions.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
using namespace tcp;

namespace kokfikoCDR {

static void PrintToFile(ofstream& a_file, CdrRecord& record) {
    a_file << record.m_sequenceNum  << '|';
    a_file << (string(record.m_imsi.m_mcc) += record.m_imsi.m_mnc += record.m_imsi.m_msin)  << '|';
    a_file << record.m_imei  << '|';
    a_file << record.m_usageType  << '|';
    a_file << record.m_msisdn  << '|';
    a_file << record.m_callDate  << '|';
    a_file << record.m_callTime  << '|';
    a_file << record.m_duration  << '|';
    a_file << record.m_byteRecieved  << '|';
    a_file << record.m_byteTransmitted  << '|';
    a_file << record.m_secondPartyMsisdn  << '|' << endl;
}


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
    ofstream file("result.txt");
    int count = 0; 

    while(true) {
        char message[DATA_SIZE];
        try {
            ++count;
            m_server.GetData(message, DATA_SIZE);

            stringstream str(string(message, 1));
            size_t sn;
            str >> sn;
            cout << sn << '\n';
            
            CdrRecord record = Protocol::UnPackMessage(message);
            m_dataAggregatorHandler.InsertNewRecord(record);
            PrintToFile(file, record);
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

} // kokfikoCDR