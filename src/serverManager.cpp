#include "serverManager.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

namespace kokfikoCDR {

ServerManager::ServerManager(ostream& a_outPutRecords) 
: m_server()
, m_clients()
, m_outPutRecords(a_outPutRecords)
{
}

void ServerManager::RunServer() { 
    while(true) {
        int activity = m_server.WaitForMessage();

        if(0 < activity) {
            setConnection(activity);
            runAllClientsRequests(activity);
        }
    }
}

// private functions:

void ServerManager::setConnection(int& a_activity) {
    int clientSocket = m_server.GetSocketConnection(a_activity);

    if(clientSocket > 0) {
        m_clients.push_back(clientSocket);
    }
}

void ServerManager::runAllClientsRequests(int& a_activity) {
    for_each(m_clients.begin(), m_clients.end(), Reciever(m_server, m_outPutRecords));
}

} // kokfikoCDR